from sys import exit
from cs50 import get_int

while True:
    h = get_int("height: ")
    if (h < 9 and h > 0):
        break

count = 1
for x in range(h):
    print(" " * (h-count), end = "")
    print("#" * count, end = "")
    print("  ", end = "")
    print("#" * count, end = "")
    print(" " * (h-count))
    count += 1
