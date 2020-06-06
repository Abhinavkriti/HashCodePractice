import math

def mod(num, length):
    return num % length

def arrayjumping(arr):
    ind = -1
    maxN = -1
    jumps = {}
    le = len(arr)
    for i, num in enumerate(arr):
        jumps[i] = [mod(i+num, le), mod(i - num, le)]
        if(num > maxN):
            maxN = num
            ind = i        
    #bfs should give us the min number of jumps
    queue = []
    visited = set()
    minJumps = 0
    queue.append([maxN, ind])
    found = False
    while(len(queue) > 0):
        [num, ind1] = queue.pop(0)
        if(ind1 not in visited):
            visited.add(ind1)
        else:
            if(num == maxN):
                found = True
                break
            else:
                continue
        temp_arr = jumps[ind1]
        minJumps += 1
        queue.append([arr[temp_arr[0]], temp_arr[0]])
        queue.append([arr[temp_arr[1]], temp_arr[1]])
    if(found == False):
        return -1
    else:
        return int(math.ceil(math.log(minJumps, 2)))

#test
print(arrayjumping([1,7,1,1,1,1]))