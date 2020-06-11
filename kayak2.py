def solution(o, d):
    sub = [0] * len(d)
    count = 0
    for i in range(len(d)):
        o[i] -= 1
        d[i] -= 1
        sub[d[i]] = i

    for i in range(len(o)):
        o[i] = sub[o[i]]

    for i in range(1, len(o)):
        if(o[i-1] + 1 != o[i]):
            count += 1

    return count + 1

print(solution([1,4,3,2], [1,2,4,3]))
