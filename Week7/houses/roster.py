import sqlite3
from sys import argv


def main():
    # Cheking if argument is valid
    if len(argv) != 2:
        print("Usage: roster.py house")
        return
    
    # Opening db file
    db = sqlite3.connect("./students.db")
    
    # Querying for the data of students in selected house
    for row in db.execute(f"SELECT first,middle,last,birth FROM students WHERE house = '{argv[1]}' ORDER BY last;"):
        # If don't have middle name
        if row[1] == None:
            name = row[0] + " " + row[2]
        else:
            name = " ".join(row[0:3])
        print(f"{name}, born {row[3]}")


main()

