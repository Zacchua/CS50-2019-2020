import sys
from cs50 import SQL

#check the command line
if len(sys.argv) != 2:
    print("incorrect usage error")
    exit(1)

#checks if correct houses are used
houses = ["Gryffindor", "Slytherin", "Ravenclaw", "Hufflepuff"]
if sys.argv[1] not in houses:
    print("Incorrect input")
    exit(2)

# query database
db = SQL("sqlite:///students.db")
x = sys.argv[1]
i = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", x)

for row in i:
    birth = str(row["birth"])
    if row["middle"] == None:
        print(row["first"], row["last"] + ", born " + birth)
    else:
        print(row["first"], row["middle"], row["last"] + ", born " + birth)
