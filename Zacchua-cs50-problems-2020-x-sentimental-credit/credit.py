from cs50 import get_int

credit = get_int("number:")
count = 0
sum = 0
num1 = 0
num2 = 0
while credit > 0:
    count += 1
    num2 = num1
    num1 = credit % 10
    if count % 2 != 0:
        sum += num1
    else:
        if (num1 *2) < 10:
            sum += num1 * 2
        else:
            sum += (num1 * 2) % 10 + 1
    credit //= 10

if sum % 10 == 0:
    if num1 == 3:
        if num2 == 4 or num2 == 7:
            print("AMEX")

    if num1 == 5:
        if num2 < 6 and num2 > 0:
            print("MASTER")

    if num1 == 4:
        print("VISA")
else:
    print("INVALID")