from cs50 import get_string

number = get_string('Number:')

if int(number[0]) not in range(3, 6) or len(number) not in range(13, 17):
    print('INVALID')
    exit(1)

sum = 0
for i in range(len(number) - 2, -1, -2):
    double = str(2 * int(number[i]))
    if int(double) > 9:
        sum += int(double[0]) + int(double[1])
    else:
        sum += int(double[0])

for i in range(len(number) - 1, -1, -2):
    sum += int(number[i])

if sum % 10 != 0:
    print('INVALID')
    exit(2)

if int(number[0]) == 3 and int(number[1]) in [4, 7] and len(number) == 15:
    print('AMEX')
    exit(0)
elif int(number[0]) == 4 and len(number) in range(13, 17):
    print('VISA')
    exit(0)
elif int(number[0]) == 5 and int(number[1]) in range(1, 6) and len(number) == 16:
    print('MASTERCARD')
    exit(0)
else:
    print('INVALID')
    exit(3)