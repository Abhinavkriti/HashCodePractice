import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('codejam1b1.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

def abssum(x, y):
    return abs(x) + abs(y)

def divideBytwo(x, y):
    x = x/2
    y = y/2
    return [x,y]

def isGood(arr):
    if((arr[0] + arr[1])%2 == 0):
        return False
    else:
        return True

testcases = int(input())

for case in range(testcases):
    x,y = map(int, input().split())
    case = ""
    if((abs(x) + abs(y))%2 == 0):
        print("Case #{}: {}".format(case+1, "IMPOSSIBLE"))
        continue
    else:
        while(abssum(x,y) != 1):
            if(x%2 == 1):
                temp_x = x - 1
                if(isGood(divideBytwo(temp_x, y))):
                    x = temp_x/2
                    y = y/2
                    case += "W"
                else:
                    temp_x = x + 1
                    if(isGood(divideBytwo(temp_x, y))):
                        x = temp_x/2
                        y = y/2
                        case += "E"
                    else:
                        case = "IMPOSSIBLE"
                        break
            else:
                temp_y = y - 1
                if(isGood(divideBytwo(x, temp_y))):
                    x = x/2
                    y = temp_y/2
                    case += "S"
                else:
                    temp_y = y + 1
                    if(isGood(divideBytwo(x, temp_y))):
                        x = x/2
                        y = temp_y/2
                        case += "N"
                    else:
                        case = "IMPOSSIBLE"
                        break
        if(x == 1)