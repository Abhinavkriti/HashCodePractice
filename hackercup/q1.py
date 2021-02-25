import sys

input = sys.stdin.readline
from functools import reduce

import numpy as np
import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('q1.txt', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)


plans = int(input())
for plan in range(1, plans+1):
    print(f"\nCase #{plan}\n")
    land = {}

    N, K, W = map(int, input().strip().split())
    L = list(map(int, input().strip().split()))
    A_L, B_L, C_L, D_L = map(int, input().strip().split())
    H = list(map(int, input().strip().split()))
    A_H, B_H, C_H, D_H = map(int, input().strip().split())

    #Initial Perimeter
    Pprod = 2 * (W + H[0])
    P = 2 * (W + H[0])
    # Smallest x
    xmin = L[0]
    # Current largest x
    xmax = L[0] + W
    # Current largest y
    ymax = H[0]

    # Stores perimeters for debug use
    Parr = [P]
    # Separate 'groups' of rectangle-polygons and record the last perimeter at the separation
    # List has form (New Smallest x, Last perimeter)
    groups = [(xmin, 0)]

    for i in range(1, N):
        # Problem-defined way to get L and H
        if i >= K:
            Li = ((A_L * L[i-2] + B_L * L[i - 1] + C_L) % D_L) + 1
            L.append(Li)
            Hi = ((A_H * H[i-2] + B_H * H[i - 1] + C_H) % D_H) + 1
            H.append(Hi)
        else:
            Li = L[i]
            Hi = H[i]
        
        # For a new group
        P_i = 0
        if Li > xmax:
            # The new group is distinct from the other rectangles, so the new perimeter is just rectangle perimeter
            # + old perimeter
            P_i = P + 2 * (W + Hi)
            groups.append((Li,P))
            xmax = Li + W
            ymax = Hi
        else:
            if Li in land:
                if land[Li] < Hi:
                    P_i = 2 * (Hi - land[Li])
            xmax = max(xmax, Li + W)
            ymax = max(ymax, Hi)
            # Perimeter of overlapping rectangles can be found using (Last perimeter) + 2 * (group width + height) 
            P_i += groups[-1][-1] + 2 * (xmax - groups[-1][0] + ymax)
        
        for delta in range(W+1):
            if Li + delta in land:
                land[Li + delta] = max(land[Li + delta], Hi)
            else:
                land[Li + delta] = Hi

        Parr.append(P_i)
        Pprod *= P_i
        P = P_i
    print(f"groups: {groups}")
    print(f"ymax: {ymax}")
    print(f"xmax: {xmax}")
    print(f"W: {W}")
    print(f"L: {L}")
    print(f"H: {H}")
    Pprod %= 1000000007
    print(f"Parr: {Parr}")
    print(f"Pprod: {Pprod}")
    # file i/o stuff