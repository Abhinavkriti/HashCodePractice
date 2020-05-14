import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('kickstart_5.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

testcases = int(input())
for i in range(testcases):
    N, D = list(map(int, input().strip().split()))
    days = list(map(int, input().strip().split()))
    current_day = D
    for j in range(len(days) - 1, -1, -1):
        #print(current_day)
        current_day = current_day//days[j] * days[j]
    print("Case #{}: {}".format(i+1, current_day))    