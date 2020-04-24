import sys
from cs50 import SQL
import csv

#check command-line arguments
if len(sys.argv) != 2:
    print("incorrect usage error")
    exit(1)

db = SQL("sqlite:///students.db")

#open csv file
with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)

    #iterates over names in csv file
    for row in reader:
        name = row["name"]
        house = row["house"]
        birth = row["birth"]

        #check len of name
        n = name.split()
        if len(n) == 3:
            fir = n[0]
            mid = n[1]
            las = n[2]

        else:
            fir = n[0]
            mid = None
            las = n[1]

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)", fir, mid, las, house, birth)


