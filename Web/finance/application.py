import os
import sys

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    cur_user = session["user_id"]
    rows = db.execute("SELECT * FROM user_stock WHERE customer_id=:id", id=cur_user)
    total = float(db.execute("SELECT cash FROM users WHERE id=:id", id=cur_user)[0]["cash"])
    cash = usd(total)
    for row in rows:
        stock = lookup(row["symbol"])
        row["name"] = stock["name"]
        row["price"] = usd(stock["price"])
        row["total"] = usd(float(row["shares"]) * stock["price"])
        total += float(row["shares"]) * stock["price"]
    total = usd(total)
    return render_template("index.html", table = rows, total = total, cash = cash)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # Getting information from api
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Symbol Unknown")
        # Getting current user id
        cur_user = session["user_id"]
        # Check the amount of cash
        cash = db.execute("SELECT * FROM users WHERE id=:userId", userId=cur_user)[0]["cash"]
        shares = int(request.form.get("shares"))
        if shares <= 0:
            # 0 or negative shares
            return apology("You should input a positive number!")
        if stock["price"] * shares > cash:
            # Cost more than cash possessed
            return apology("You don't have suffiecient cash")
        cash -= stock["price"] * shares
        time = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
        # Update cash possessed and insert into history
        db.execute("UPDATE 'users' SET 'cash'=:cash WHERE id=:id", cash=cash, id=cur_user)
        db.execute("INSERT INTO 'history' (customer_id, stock_name, symbol, price, shares, date) VALUES (:id, :name, :symbol,\
                    :price, :shares, :date)",\
                    id=cur_user, name=stock["name"], symbol=stock["symbol"], shares=shares, date=time, price=stock["price"] )
        # Check if the stock is already bought
        if len(db.execute("SELECT * FROM user_stock WHERE customer_id=:id AND symbol=:symbol", id=cur_user, symbol = stock["symbol"])) == 0:
            db.execute("INSERT INTO user_stock (customer_id, symbol, shares) VALUES (:id, :symbol, :shares)", id = cur_user, symbol = \
                        stock["symbol"], shares = shares)
        else:
            new_share = db.execute("SELECT * FROM user_stock WHERE customer_id=:id AND symbol=:symbol", id=cur_user, symbol = \
                                    stock["symbol"])[0]["shares"] + shares
            db.execute("UPDATE user_stock SET shares=:shares WHERE customer_id=:id AND symbol =:symbol", shares = new_share, \
                        id = cur_user, symbol = stock["symbol"])
        info = f"{shares} shares of {stock['name']}({stock['symbol']}) are bought."
        flash(info)
        return redirect("/")

    elif request.method == "GET":
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    history = db.execute("SELECT * FROM history WHERE customer_id=:id ORDER BY date DESC", id = session["user_id"])
    for i in history:
        i["price"] = usd(i["price"])
    return render_template("history.html", history = history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # Open quote.html
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        # Get the jsonObject
        obj = lookup(request.form.get("symbol"))
        # Can't find the symbol
        if not obj:
            return apology("Unknown symbol")
        name = obj["name"]
        price = usd(obj["price"])
        symbol = obj["symbol"]
        # Send the values and open quoted.html
        return render_template("quoted.html", name = name, price = price, symbol = symbol)

@app.route("/recharge", methods=["GET", "POST"])
@login_required
def recharge():
    if request.method == "GET":
        return render_template("recharge.html")
    elif request.method == "POST":
        amount = int(request.form.get("amount"))
        if amount <= 0:
            return apology("You must input a positive number!")
        cur_cash = db.execute("SELECT * FROM users WHERE id=:id", id = session["user_id"])[0]["cash"]
        cur_cash += amount
        db.execute("UPDATE users SET cash=:cash WHERE id=:id",cash = cur_cash, id = session["user_id"])
        flash(f"${amount} has been added to your account!")
        return redirect("/")

@app.route("/register", methods=["GET", "POST"])
def register():
    # Open register.html
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")
        # Check filled values with correct password confirmation
        if not username:
            return apology("Username cannot be empty!")
        if not password or not confirm_password:
            return apology("Cannot have empty password or empty password confirmation")
        if password != confirm_password:
            return apology("Password confirmation does not match password")
        else:
            # Check if there is repeated username
            rows = db.execute("SELECT * FROM users WHERE username=?", username)
            if rows != 0:
                return apology("Username " + username + " has been used, please use a different username")
            # If not, insert into database and redirects to index.html
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username = username, password = generate_password_hash(password))
            return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        stocks = []
        # Get all the stocks available
        rows = db.execute("SELECT * FROM user_stock WHERE customer_id=:id", id = session["user_id"])
        for i in rows:
            stocks.append(i["symbol"])
        return render_template("sell.html", stocks=stocks)
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        print("\nsymbol is ", symbol, "\n", file=sys.stdout)
        # if the symbol is default:
        if symbol == "Symbol":
            return apology("Please select a stock")
        stock = lookup(symbol)
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Please input a positive integer!")
        user_share = db.execute("SELECT * FROM user_stock WHERE customer_id=:id AND symbol=:symbol", id = session["user_id"],\
                                symbol = symbol)[0]["shares"]
        if shares > user_share:
            return apology("You don't have suffiecient shares")

        # if the user sells all the shares then delete entire row
        elif shares == user_share:
            db.execute("DELETE FROM user_stock WHERE customer_id=:id AND symbol=:symbol", id = session["user_id"], symbol = symbol)

        else:
            user_share -= shares
            db.execute("UPDATE user_stock SET shares=:new_share WHERE customer_id=:id AND symbol=:symbol", id = session["user_id"],\
                                    symbol = symbol, new_share = user_share)
        # updating user cash and history
        time = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
        db.execute("INSERT INTO history (customer_id, stock_name, symbol, price, shares, date) VALUES (\
                    :id, :name, :symbol, :price, :shares, :date)",id = session['user_id'], name = stock["name"], \
                    symbol = stock['symbol'], price = stock["price"], shares = -shares, date = time)
        cash = float(db.execute('SELECT * FROM users WHERE id=:id', id = session["user_id"])[0]["cash"]) + shares * stock["price"]
        db.execute("UPDATE 'users' SET 'cash'=:cash WHERE id=:id", cash=cash, id=session["user_id"])
        info = f"{ shares } shares of {stock['name']}({stock['symbol']}) are sold."
        #"sold.html", shares=shares, name = stock["name"], symbol= stock["symbol"]
        flash(info)
        return redirect("/")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
