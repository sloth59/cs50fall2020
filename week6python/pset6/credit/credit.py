# Luhn's algorithm Hans peter luhn of IBM

def main():
    # get/validate the input card number
    while True:
        cardnum = int(input("Number: "))
        if cardnum > 0:
            break

    length = len(str(cardnum))
    # get first two digits of the card number
    firsttwo = gettwo(cardnum)

    # run luhns algorithm on the card number
    if luhncheck(cardnum):
        # run the vendor check for known vendor as per provided information
        vendorcheck(length, firsttwo)
    else:
        print("INVALID")


def luhncheck(num):
    count = 0
    evensum = 0
    oddsum = 0
    while num != 0:
        lastn = num % 10
        num = num // 10

        if count % 2 == 0:
            evensum += lastn

        else:
            lastn *= 2
            if lastn > 9:
                lastn = lastn//10 + lastn % 10
            oddsum += lastn
        count += 1

    finalsum = evensum + oddsum

    if finalsum % 10 == 0:
        return True
    else:
        return False


def gettwo(num):
    while True:
        num = num // 10
        if num < 99:
            break
    return num


def vendorcheck(length, firsttwo):
    if length == 16:
        if firsttwo >= 51 and firsttwo <= 55:
            print("MASTERCARD")
        elif firsttwo >= 40 and firsttwo <= 49:
            print("VISA")
        else:
            print("INVALID")

    elif length == 15 and (firsttwo == 34 or firsttwo == 37):
        print("AMEX")

    elif length == 13:
        if firsttwo >= 40 and firsttwo <= 49:
            print("VISA")
        else:
            print("INVALID")

    else:
        print("INVALID")


if __name__ == "__main__":
    main()
