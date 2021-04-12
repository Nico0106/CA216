# schedule_fcfs.py
# Author: Nicolas Oyeleye

# importing all tools needed
import sys
from driver import drive

# Function: main
# Description: prints each task in order it receives them
def main():
    print("First Come First Served...")
    # calling drive function to read the input and turn it into a dictionary 
    for v in drive():
        print("Running task = {} {} {} for {} units\n".format(v[0], v[1][0], v[1][1], v[1][1]))

if __name__ == '__main__':
    main()
