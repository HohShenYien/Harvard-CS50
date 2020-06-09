from sys import argv
# standard library for sqlite3, so I use it instead of cs50's
import sqlite3
import csv


def main():
    # throw an error if incorrect argument
    if len(argv) != 2:
        print("Usage: import.py data.csv")
        return
    # Opening my db file
    db = sqlite3.connect("./students.db")
    # Opening csv file
    with open(argv[1]) as file:
        reader = csv.DictReader(file)

        for rows in reader:
            # Declaring variables and cleaning up name
            name = rows["name"].split()
            house = rows["house"]
            birth = rows["birth"]
            # Deciding whether the person has middle name or not
            if len(name) == 2:
                values = [name[0], name[1], house, birth]
                db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", values)
            elif len(name) == 3:
                values = [name[0], name[1], name[2], house, birth]
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", values)
    # Save the changes
    db.commit()
    # Close the file
    db.close()


main()
