import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('p2.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

testcases = int(input())
for t in range(testcases):
    bracket_stack = 0
    numList = input()
    resStr = ""
    for i in numList:
        if(int(i) == bracket_stack):
            resStr += str(i)
        elif(int(i) > bracket_stack):
            for j in range(int(i) - bracket_stack):
                bracket_stack += 1
                resStr += "("
            resStr += i
        else:
            for j in range(bracket_stack - int(i)):
                bracket_stack -= 1
                resStr += ")"
            resStr += i
    while(bracket_stack > 0):
        bracket_stack -= 1
        resStr += ")"
    
    print("Case #" + str(t + 1) + ": " + resStr)