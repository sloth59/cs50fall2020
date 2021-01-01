import sys
import csv


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # open the csv file with data
    with open(sys.argv[1], "r") as csvfile:
        reader = csv.reader(csvfile)
        i = 0  # counter to get position of each row to insert in sample list
        sample = []  # initialize a list called sample

        # sample list where each element is itself a list of contents in one row
        for row in reader:
            sample.append(row)
            i += 1

        # open the text file with the sequence
        with open(sys.argv[2], "r") as sequence:
            data = sequence.read()
            STR = [0, ]  # initialize STR list where the found highest no.of consecutive sequence will be recorded

            for feature in range(1, len(sample[0])):
                count = 1
                while True:
                    pattern = sample[0][feature] * count
                    no = data.count(pattern)
                    if no > 0:
                        count += 1
                    else:
                        break
                STR.append(count - 1)  # count is decreased by 1 cause we set it to 1 initialliy

            # iterate over each row of
            for row in sample:
                match = 0
                for number in range(1, len(row)):
                    if row[number] == str(STR[number]):
                        match += 1
                # the below condition states that all the traits were mached
                if match == len(row) - 1:
                    print(f"{row[0]}")
                    return
            print("No match")


if __name__ == "__main__":
    main()