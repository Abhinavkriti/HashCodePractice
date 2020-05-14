import sys

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('kickstart_6.in', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

move_dictionary = {"N": [0,-1], "S": [0, 1], "E": [1, 0], "W": [-1, 0], ")": [0,0]}

class recursive_tape:

    def __init__(self, tape):
        self.tape = tape
        self.x_pos = 1
        self.y_pos = 1
        self.iterant = 0

    def roll(self):
        while(self.iterant < len(self.tape)):
            if(self.tape[self.iterant].isdigit()):
                temp_x, temp_y = self.recurse(int(self.tape[self.iterant]))
                self.x_pos = (self.x_pos + temp_x) % 1000000000
                self.y_pos = (self.y_pos + temp_y) % 1000000000
            elif(self.tape[self.iterant].isalpha()):
                move = move_dictionary[self.tape[self.iterant]]
                self.x_pos = (self.x_pos + move[0]) % 1000000000
                self.y_pos = (self.y_pos + move[1]) % 1000000000
                self.iterant += 1
            else:
                if(self.tape[self.iterant] == ")"):
                    self.iterant += 1

    def recurse(self, X):
        print("recursion: " + str(X))
        self.iterant += 2
        temp_x = 0
        temp_y = 0
        while(self.iterant < len(self.tape) and self.tape[self.iterant] != ")"):
            while(self.iterant < len(self.tape) and self.tape[self.iterant].isdigit()):
                temper_x, temper_y = self.recurse(int(self.tape[self.iterant]))
                temp_x += temper_x
                temp_y += temper_y
            if(self.iterant >= len(self.tape)):
                break
            if(self.tape[self.iterant] == ")"):
                self.iterant += 1
                if(self.iterant >= len(self.tape)):
                    break
            move = move_dictionary[self.tape[self.iterant]]
            temp_x = (temp_x + move[0]) % 1000000000
            print("before " + str(temp_y))
            temp_y = (temp_y + move[1]) % 1000000000
            print("after " + str(temp_y))
            self.iterant += 1
        self.iterant += 1 # for the ")"
        print("temp_y " + str(temp_y))
        print("temp_x " + str(temp_x))
        return temp_x * X, temp_y * X

    def getPos(self):
        return self.x_pos, self.y_pos

    def clear(self):
        self.tape = None
        self.x_pos = 1
        self.y_pos = 1
        self.iterant = 0


testcases = int(input())
for i in range(testcases):
    tape = input()
    rover_msg = recursive_tape(tape)
    rover_msg.roll()
    x_pos, y_pos = rover_msg.getPos()
    if(x_pos == 0):
        x_pos = 10e9
    if(y_pos == 0):
        y_pos = 10e9
    rover_msg.clear()
    print("Case #{}: {} {}".format(i+1, int(x_pos), int(y_pos)))    