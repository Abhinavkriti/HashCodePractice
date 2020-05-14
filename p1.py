import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('p1.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

cases = int(input())

for case in range(1, cases + 1):
    rows = int(input())
    grid = []
    for row in range(rows):
        grid.append(list(map(int, input().strip().split())))
    trace = sum([grid[i][i] for i in range(rows)])
    rep_rows = 0
    rep_cols = 0
    for row in range(rows):
        if len(set(grid[row])) != rows:
            rep_rows += 1
    
    for col in range(rows):
        # print([grid[col][i] for i in range(rows)])
        if len(set([grid[i][col] for i in range(rows)])) != rows:
            rep_cols += 1
    print("Case #{}: {} {} {}".format(case, trace, rep_rows, rep_cols))
    # print(trace)