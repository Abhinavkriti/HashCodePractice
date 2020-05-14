import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('hilbertshotel.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

testcases = int(input())
for i in range(testcases):
    no = False
    n = int(input())
    tenants = map(int, input().split())
    rooms = {}
    for it, t in enumerate(tenants):
        newt = it + (t+1)%n
        if(newt in rooms):
            print("NO")
            no = True
            break
        else:
            rooms[newt] = 1
    if(no is False):
        print("YES")