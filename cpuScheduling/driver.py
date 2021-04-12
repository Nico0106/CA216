# driver.py
# Author: Nicolas Oyeleye

# importing all tools needed
import sys

# Function: driver
# @params: nothing
# Returns: dictionary
# Description: Readlines in the contents of the given file and returns the dictio of the content

def drive():
    filename = sys.argv[1]
    # Opening file
    with open(filename, "r") as file:
        # Read file contents in
        data  = file.readlines()
        d = {} # dictionary
        for lines in data:
            line = lines.strip().split()
            # Removing commas and adding to d (dictionary)
            d[line[0].split(",")[0]] = (int(line[1].split(",")[0]), int(line[2]))

        a = d.items()
    return a
