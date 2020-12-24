def main():
    while True:
        height = int(input("Height: "))
        if height > 0 and height <= 8:
            break

    for i in range(height):
        for j in range(height-i):
            print(" ", end="")
        for j in range(i+1):
            print("#", end="")

        print("  ", end="")

        for j in range(i+1):
            print("#", end="")
        print("")

if __name__ == "__main__":
    main()
