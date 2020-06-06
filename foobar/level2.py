def solution(s):
    right_counter = 0
    salutes = 0
    for i in s:
        if(i == ">"):
            right_counter += 1
        elif(i == "-"):
            continue
        else:
            salutes += 2*right_counter
    return salutes

print(solution(">---<"))
print(solution("<<>><"))
print(solution("<<<>>>"))
print(solution(">-->--<<<<<<<<<"))
