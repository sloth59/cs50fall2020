import cs50
import sys


# check numbe of command line arguments
if len(sys.argv) != 2:
    print("Usage: python roster.py houseName")
    sys.exit(1)

# open database
db = cs50.SQL("sqlite:///students.db")

data = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])

# iterate over the list of dictonaries
for row in data:
    fname = row["first"]
    mname = row["middle"]
    lname = row['last']
    birth = row["birth"]

    # print the current dictonary in required format
    if row["middle"] != None:
        print(f"{fname} {mname} {lname}, born {birth}")
    else:
        print(f"{fname} {lname}, born {birth}")