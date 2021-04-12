# schedule_sjf.py
# Author: Nicolas Oyeleye

# importing all tools needed
import sys
from driver import drive

# Function: main
# Description: Prints the schedule in shortest job first order
def main():
    print("Shorest Job First...")
    # Sorting the dictionary in terms of each jobs length
    # drive function reads in input from file and turns it into dictionary
    for v in sorted(drive(), key=lambda x:x[1][1]):
        print("Running task = {} {} {} for {} units.\n".format(v[0], v[1][0], v[1][1], v[1][1]))

if __name__ == '__main__':
    main()
