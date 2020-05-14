import sys

input = sys.stdin.readline

dict_row = {0,1, 2,3,4, 5, 6, 7}
row = 0
for i in range(8):
    row1 = input()
    rook = False
    for j in range(len(row1)):
        if(row1[j] == "R"):
            rook = True
            if(j in dict_row):
                dict_row.remove(j)
    if(rook == False):
        row += 1
print(row*len(dict_row))
