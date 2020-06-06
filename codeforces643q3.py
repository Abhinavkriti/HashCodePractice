import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('codeforces643q3.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

testcases = int(input())
for case in range(testcases):
    n = int(input())
    nd2 = int(n/2)
    sumA = int((nd2/2)*(1 + nd2))
    x = 1
    y = 1
    for i in range(nd2):
        sumA += x*y
        x += 2
        y += 1
    print(4*sumA)