from sys import argv
import csv
import re


def main():
    # Error found when length of arguments not 3
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        # Breaking out of the function
        return
    # A dictionary of dna sequence(in string form) : name
    dna_name = {}
    with open(argv[1]) as csv_file:
        # Opening the csv file
        data_file = csv.reader(csv_file)
        # each row is placed into data temporarily
        data = []
        # Example: for small, AGATC, AATG, TATC
        dna_name = {}
        for rows in data_file:
            data.append(rows)
        # Storing the sequences to be found
        sequences = data[0][1:]
        # Storing the  person's dna as key and name as value
        for i in data[1:]:
            string = ",".join(i[1:])
            dna_name[string] = i[0]
    # Opening the sequence file
    seq_file = open(argv[2], "r")
    seq = ""
    # Getting the sequence as a string
    for row in seq_file:
        seq += row
    match = []
    for i in sequences:
        store = []
        # Finditer gives me the indices of the positions of the match
        for m in re.finditer(rf"({i})+", seq):
            # I then store the length of the subtring with 1 or more 
            # occurence of the sequence
            store.append(m.end(0) - m.start(0))
        # If doesn't match at all break out
        if len(store) == 0:
            print("No match")
            return
        # Converting the length into numbers of repetition
        match.append(str(int(max(store)/len(i))))
    # Converting the array into string    
    match = ",".join(match)
    if match in dna_name:
        print(dna_name[match])
    else:
        print("No match")


main()
