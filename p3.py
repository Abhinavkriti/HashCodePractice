import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('p3.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

class Interval:

    def __init__(self, start: int, end:int, ide: int):
        self.start = start
        self.end = end
        self.ide = ide

for t in range(int(input())):
    activity_list = []
    num_activities = int(input())
    new_dict = ["X"] * num_activities
    c_end = -1
    j_end = -1
    impossible = False
    for activity_id in range(num_activities):
        activity_interval = list(map(int, input().split()))
        activity_list.append(Interval(activity_interval[0], activity_interval[1],activity_id))
    for activity in sorted(activity_list, key = lambda x: x.start, reverse = True):
        if(activity.start >= c_end):
            new_dict[activity.ide] = "C"
            c_end = activity.end
        elif(activity.start >= j_end):
            new_dict[activity.ide] = "J"
            j_end = activity.end
        else:
            impossible = True
            break
    resStr = ""
    
    if(impossible or num_activities <= 1):
        resStr = "IMPOSSIBLE"
    else:
        for i in new_dict:
            resStr += i
        
    print("Case #" + str(t + 1) + ": " + resStr)
