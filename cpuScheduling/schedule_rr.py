# schedule_rr.py
# Author: Nicolas Oyeleye

# importing all tools needed
import sys
from driver import drive

# Function: sum
# Description: Adds the numbers in the list together and returns the sum
def sum(list):
    sum = 0
    #iterating through list
    for i in list:
        #adds each i to the sum
        sum += i
    return sum

# Function: robin
# Description: Prints each task for 10 slice unless it is less than 10
# If the job length is more than 10 it prints the task for then and moves on
# to the next task amd returns to that task when it has finished all the others
def robin(a, dictionary, num):
    j = 0 # iterator
    while sum(a) != 0 and j < len(a):
        # if current task has been finished running skip it
        if a[j] == 0:
            pass
        # if the current tasks time is less than 10 allow the task to run
        elif a[j] < 10:
            print("Running task = {} {} {} for {} units.\n".format(dictionary[j][0], dictionary[j][1][0], a[j], a[j]))
            a[j] = 0
        # if the current tasks time is greater than 10 and this is the first time
        #print its original time and remove 10 from the time
        elif a[j] >= 10 and num == 0:
            print("Running task = {} {} {} for 10 units.\n".format(dictionary[j][0], dictionary[j][1][0], a[j]))
            a[j] = a[j] - 10
        # if the current tasks time is greater than 1o and this isnt its first time
        # find its time in the list remove ten from it and print it
        elif a[j] >= 10 and num == 1:
            print("Running task = {} {} {} for 10 units.\n".format(dictionary[j][0], dictionary[j][1][0], a[j]))
            a[j] = a[j] - 10
        j += 1

# Function: main
# Description: sorts dictionary in priority schedule and passes it to the robin function
def main():
    print("Scheduling priority round robin...\n")
    a = [] # slice list
    for v in sorted(drive(), key=lambda x:x[1][0]):
        slice = v[1][1]
        a.append(slice) # add time to list
        #sort dic dictionary by priority
    dic = sorted(drive(), key=lambda x:x[1][0])

    # pass list, dictionary and indicator to robin function
    # indicator tells the function if it is its first time being passed into the
    #robin function
    # 0 indicates its first time
    robin(a, dic, 0)
    while sum(a) != 0:
        # 1 indicates its not thie first time its been passed to robin
        robin(a, dic, 1)

if __name__ == '__main__':
    main()
