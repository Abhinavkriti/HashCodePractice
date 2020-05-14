import sys
import queue

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('k.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

n = int(input())
graph = []
visited = []
zone_visited = []
bfsqueue = queue.Queue()  
ini_position = None
soul_stone = None
for i in range(n):
    graph.append(input())
    visited.append([0] * len(graph[-1]))
    zone_visited.append([0] * len(graph[-1]))
    for ch in range(len(graph[-1])):
        if(graph[-1][ch] == "@"):
            ini_position = [i, ch]
        elif(graph[-1][ch] == "$"):
            soul_stone = [i, ch]
bfsqueue.put(ini_position)

def getneighbour(pos, visited):
    neigh = []
    if((pos[0] - 1) >= 0 and visited[pos[0]-1][pos[1]] == 0):
        neigh.append([pos[0]-1, pos[1]])
    if((pos[0] + 1) < n and visited[pos[0]+1][pos[1]] == 0):
        neigh.append([pos[0]+1, pos[1]])
    if((pos[1] - 1) >= 0 and visited[pos[0]][pos[1]-1] == 0):
        neigh.append([pos[0], pos[1]-1])
    if((pos[1] + 1) < n and visited[pos[0]][pos[1] + 1] == 0):
        neigh.append([pos[0], pos[1]+1])
    return neigh

gates_on_path = []
keys_needed = {}

while(not bfsqueue.empty()):
    pos = bfsqueue.get()
    visited[pos[0]][pos[1]] = 1
    neighbours = getneighbour(pos, visited)
    for nei in neighbours:
        bfsqueue.put(nei)
    if(graph[pos[0]][pos[1]] == "#"):
        continue
    if(graph[pos[0]][pos[1]].isupper()):
        gates_on_path.append([graph[pos[0]][pos[1]], pos])
        keys_needed[graph[pos[0]][pos[1]].lower()] = True
    if(graph[pos[0]][pos[1]] == "$"):
        gates_on_path.append(["X",soul_stone])
        break

def manhattanDistance(curr, goal):
    xx = abs(goal[1] - curr[1])
    yy = abs(goal[0] - curr[0])
    return xx + yy

bfsqueue = queue.Queue()
count = 0
keys_collected = {}
impossible_case = False
for zone in gates_on_path:
    print(zone)
    bfsqueue.put(ini_position)
    keys_found = {}
    while(not bfsqueue.empty()):
        pos = bfsqueue.get()
        zone_visited[pos[0]][pos[1]] = 1
        neigh = getneighbour(pos, zone_visited)
        for nei in neigh:
            if(graph[nei[0]][nei[1]].isupper()):
                continue
            bfsqueue.put(nei)
        if(graph[pos[0]][pos[1]] == "#"):
            continue
        if(graph[pos[0]][pos[1]].islower()):
            if(graph[pos[0]][pos[1]] in keys_needed):
                keys_found[graph[pos[0]][pos[1]]] = pos
    key_list = sorted(list(keys_found.items()), key = lambda x: x[0])
    for key in key_list:
        count += manhattanDistance(ini_position, key_list[1][1])
        ini_position = key_list[1][1]
        keys_collected[key_list[0][0]] = True
    count += manhattanDistance(ini_position, zone[1])
    ini_position = zone[1]
    print(keys_collected)
    print(zone[0])
    if(not zone[0].lower() in keys_collected and zone[0] is not "X"):
        print("IMPOSSIBLE")
        impossible_case = True
        break

if(not impossible_case):
    print(count)


        
        


    
    
