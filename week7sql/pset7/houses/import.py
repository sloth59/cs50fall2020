import cs50
import csv
import sys


# check numbe of command line arguments
if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    sys.exit(1)

# open database
db = cs50.SQL("sqlite:///students.db")

# Open CSV file
with open(sys.argv[1], "r") as file:
    # Create DictReader
    reader = csv.DictReader(file)

    # Iterate over CSV file
    for row in reader:

        # get value of each field
        house = row["house"]
        birth = row["birth"]
        name = row["name"].split(" ")
        if len(name) == 3:
            fname = name[0]
            mname = name[1]
            lname = name[2]
        else:
            fname = name[0]
            mname = None
            lname = name[1]

        # Insert into database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", fname, mname, lname, house, birth)