import csv
import sys


def main():

    # TODO: Check for command-line usage
    # Check if number of command-line arguments is correct, assuming that the filenames are correct
    if len(sys.argv) != 3:
        sys.exit('WRONG USAGE: python dna.py CSVdatabasefilename textDNAsequencefilename')

    # TODO: Read database file into a variable
    # Creating variable to store data
    data = []
    # Opening csv database file and using reader to read in 'list mode' because no need to know the names of sequences
    with open(sys.argv[1], 'r') as file:
        reader = csv.reader(file)
        # To list of data append new rows as small lists representing one person
        for row in reader:
            data.append(row)

    # TODO: Read DNA sequence file into a variable
    # Opening a text file with the DNA sequence and saving whole file in sequence variable
    with open(sys.argv[2], 'r') as files:
        sequence = files.read()

    # TODO: Find longest match of each STR in DNA sequence
    match = []
    for i in range(len(data[0]) - 1):
        match.append(longest_match(sequence, data[0][i + 1]))

    # TODO: Check database for matching profiles
    for i in range(len(data) - 1):
        name = True
        for j in range(len(data[0]) - 1):
            if match[j] != int(data[i + 1][j + 1]):
                name = False
        if name == True:
            print(data[i + 1][0])
            return

    print('No match')
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
