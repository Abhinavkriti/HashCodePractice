import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('kickstart_4.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

testcases = int(input())
for i in range(testcases):
    N = int(input())
    Peaks = list(map(int, input().strip().split()))
    num_peaks = 0
    for j in range(len(Peaks)):
        if(j == 0 or j == len(Peaks) - 1):
            continue
        else:
            if(Peaks[j] > Peaks[j+1] and Peaks[j] > Peaks[j-1]):
                num_peaks += 1
    print("Case #{}: {}".format(i+1, num_peaks))