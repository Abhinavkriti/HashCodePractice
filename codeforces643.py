import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('codeforces643.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

testcases = int(input())
for case in range(testcases):
    n,m = map(int, input().split())
    if(n == 1):
        print(0)
    elif(n == 2):
        print(m)
    else:
        print(2*m)

