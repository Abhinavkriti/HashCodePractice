import sys

import operator as op
from functools import reduce

def comb(n, r):
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return int(numer / denom)

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('j.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

n, k = map(int, input().split())
graph = [[0 for x in range(n)] for y in range(n)] 
worldly_ppl = set()
degree_worldly_ppl = {}
for pairs in range(k):
    p1, p2 = map(int, input().split())
    graph[p1 - 1][p2 - 1] = 1
    graph[p2 - 1][p1 - 1] = 1
    worldly_ppl.add(p1-1)
    worldly_ppl.add(p2-1)

for ppl in worldly_ppl:
    for edges in range(len(graph[ppl])):
        if(edges == ppl):
            continue
        else:
            if(graph[ppl][edges] == 1):
                if(ppl not in degree_worldly_ppl.keys()):
                    degree_worldly_ppl[ppl] = 1
                else:
                     degree_worldly_ppl[ppl] = degree_worldly_ppl[ppl] + 1

# Number of vertices 
V = n
  
def DFS(graph, marked, n, vert, start, count): 
  
    # mark the vertex vert as visited 
    marked[vert] = True
   
    # if the path of length (n-1) is found 
    if n == 0:  
  
        # mark vert as un-visited to make 
        # it usable again. 
        marked[vert] = False
   
        # Check if vertex vert can end with 
        # vertex start 
        if graph[vert][start] == 1: 
            count = count + 1
            return count 
        else: 
            return count 
   
    # For searching every possible path of 
    # length (n-1) 
    for i in range(V): 
        if marked[i] == False and graph[vert][i] == 1: 
  
            # DFS for searching path by decreasing 
            # length by 1 
            count = DFS(graph, marked, n-1, i, start, count) 
   
    # marking vert as unvisited to make it 
    # usable again. 
    marked[vert] = False
    return count 
   
# Counts cycles of length 
# N in an undirected 
# and connected graph. 
def countCycles( graph, n): 
  
    # all vertex are marked un-visited initially. 
    marked = [False] * V  
   
    # Searching for cycle by using v-n+1 vertices 
    count = 0
    for i in range(V-(n-1)): 
        count = DFS(graph, marked, n-1, i, i, count) 
   
        # ith vertex is marked as visited and 
        # will not be visited again. 
        marked[i] = True
      
    return int(count/2) 

count = 0
num_cycles = countCycles(graph, 3)
count += num_cycles
count += comb(n-len(worldly_ppl), 3)

# intersection = max(3*num_cycles - len(worldly_ppl), 0)
# edgesinters = 2*comb(intersection, 2)
# total -= edgesinters
print(int(count))

