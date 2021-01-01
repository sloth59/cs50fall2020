# Ask the user how much change is owed and then print the minimum number of coins with which that change can be made.Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).
import cs50


def main():
    # get the total changes owned
    while True:
        dollars = cs50.get_float("Change owned: ")
        if dollars > 0:
            break

    # convert to dollars/int
    cents = dollars * 100
    coins = 0

    # calculations
    while cents > 0:
        if cents >= 25:
            cents -= 25
            coins += 1
        elif cents < 25 and cents >= 10:
            cents -= 10
            coins += 1
        elif cents < 10 and cents >= 5:
            cents -= 5
            coins += 1
        else:
            cents -= 1
            coins += 1

    # display output
    print(coins)


if __name__ == "__main__":
    main()
