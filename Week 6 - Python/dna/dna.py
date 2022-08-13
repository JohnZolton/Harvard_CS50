import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("error, invalid command line input")
        exit(1)
    # TODO: Read database file into a variable
    dna = []
    database = []
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        dna = reader.fieldnames[1:]
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    suspect_data = []
    f = open(sys.argv[2], 'r')
    suspect_data = f.read()

    # TODO: Find longest match of each STR in DNA sequence
    sample = []
    for i in range(len(dna)):
        x = longest_match(suspect_data, dna[i])
        sample.append(dna[i])
        sample[sample.index(dna[i])]=str(x)

    # TODO: Check database for matching profiles
        #need to call from database, name and str
            # check each person's DNA for a given STR
            # DNA will match exactly (given in problem statement)
    placeholder =[]
    for x in range(len(database)):
        for n in dna:
            # x is person, n is DNA
            # checks all DNA of one person
            #database[x][n]
            placeholder.append(database[x][n])
        if sample == placeholder:
            print(database[x]['name'])
            return
        placeholder = []
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
