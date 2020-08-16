import sys
from collections import deque

input = sys.stdin.readline

import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('travel_restrictions_input.txt', 'r') as f:
    read = f.read().strip().split('\n')
dataiter = iter(read)
def input():
    return next(dataiter)

cases = int(input())

def gen_friends(countries, country, i_list, o_list, visited, P):
    friends = []
    if o_list[country] == "Y": # Outgoing flights are allowed
        if country - 1>= 0 and i_list[country - 1] == "Y" and country - 1 not in visited:
            P[country] = ["Y" if P[country-1][c] == "Y" else P[country][c] for c in range(countries)]
        if country + 1 < countries and i_list[country + 1] == "Y" and country + 1 not in visited:
            friends.append(country + 1)
    return friends

open('output.txt', 'w').close()

for case in range(cases):
    countries = int(input())
    i_list = list(input())
    o_list = list(input())
    completed = set()
    P = [["Y" if j == i else "N" for j in range(countries)] for i in range(countries)]

    for country in range(countries):
        queue = deque([country])
        visited = set([country])
        while queue:
            current = queue.popleft()
            visited.add(current)
            # ONLY WORKS IF WE PASS BY REF <3 PYTHON
            friends = gen_friends(countries, current, i_list, o_list, visited, P)
            for friend in friends:
                P[country][friend] = "Y"
                queue.append(friend)
                visited.add(friend)
        completed.add(country)

    with open('output.txt', 'a') as f:
        f.write(f"Case #{case + 1}: \n")
        for line in P:
            f.write(''.join(line))
            f.write('\n')
