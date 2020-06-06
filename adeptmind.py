import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('adeptmind.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

class TransGraph:

    def __init__(self, strArr):
        self.matrix = []
        self.rowNum = len(strArr)
        for i in strArr:
            row = list(map(int, i[1:-1].split(',')))
            self.matrix.append(row)
        self.newMatrix = self.matrix.copy()
        
    def transitiveClosure(self): 
        reach =[i[:] for i in self.matrix] 
        for k in range(self.rowNum): 
            for i in range(self.rowNum): 
                for j in range(self.rowNum): 
                    reach[i][j] = reach[i][j] or (reach[i][k] and reach[k][j]) 
        return reach, self.matrix

def TransitiveRelation(strArr):
    x = TransGraph(strArr)
    newMat, original = x.transitiveClosure()
    transitive = True
    closure = []
    for i in range(x.rowNum):
        for j in range(x.rowNum):
            if(newMat[i][j] == original[i][j]):
                continue
            else:
                if(i == j):
                    continue
                closure.append([i,j])
                transitive = False
    if(transitive):
        print("Transitive")
    else:
        print(closure)
    
#test
strArr = ["(1,1,1)", "(1,0,0)", "(0,1,0)"]
TransitiveRelation(strArr)
