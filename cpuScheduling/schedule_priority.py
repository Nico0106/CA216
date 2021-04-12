# schedule_priority.py
# Author: Nicolas Oyeleye

# importing all tools needed
import sys
from driver import drive

# Function: main
# Description: sorts dictionary in priority schedule and prints schedule
def main():
    print("Scheduling priority...\n")
    for v in sorted(drive(), key=lambda x:x[1][0]):
        print("Running task = {} {} {} for {} units.\n".format(v[0], v[1][0], v[1][1], v[1][1]))

if __name__ == '__main__':
    main()
