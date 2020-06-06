import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('codeforces643q2.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

testcases = int(input())
for case in range(testcases):
    n,k = map(int, input().split())
    a = sorted(map(int, input().split()))
    sumA = sum(a)
    b = sorted(map(int, input().split()))
    i = 0
    while(k > 0 and i < len(a)):
        if(a[i] < b[-1-i]):
            k = k - 1
            sumA = sumA - a[i] + b[-1-i]
            i = i + 1
        else:
            break
    print(sumA)
    