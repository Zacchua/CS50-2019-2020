import sys
import csv

#checks for 3 command line arguments
if (len(sys.argv) != 3):
    print("Error, 2 arguments at command prompt required")
    sys.exit()

#open the dna database
with open(sys.argv[1], 'r') as csvfile:
    dnalist = csv.reader(csvfile)
    #load dna name into a list
    for row in dnalist:
        name = row
        name.pop(0)
        name = list(name)
        break

    #open the dna strand
    f = open(sys.argv[2], 'r')
    dnastrand = f.read()

    #get the number of each STR
    count = 0
    cur_count = 0
    final = {}
    for strname in name:
        strlen = len(strname)
        count = 0
        for i in range(len(dnastrand)):
            j = i
            cur_count = 0
            while dnastrand[j:j + strlen] == strname:
                cur_count += 1
                j += strlen
            if cur_count > count:
                count = cur_count
        final[strname] = count

with open(sys.argv[1], 'r') as csv_file:
    people = csv.DictReader(csv_file)
    for row in people:
        n = 0
        for key in final:
            if int(row[key]) == final[key]:
                n += 1
        if n == len(final):
            print(row['name'])
            sys.exit()


print("No match")