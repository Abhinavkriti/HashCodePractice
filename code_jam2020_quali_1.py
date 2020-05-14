testcases = int(input())
for i in range(testcases):
    matrix = []
    row = 0
    col = 0
    trace = 0
    N = int(input())
    cols = [set() for i in range(N)]
    rows = [set() for i in range(N)]
    for j in range(N):
        numList = list(map(int, input().split()))
        matrix.append(numList)
        trace += matrix[-1][j]
        for id, k in enumerate(matrix[-1]):
            cols[id].add(k)
            rows[j].add(k)
    for t in cols:
        if(N - len(t) != 0):
            col += 1
    for t in rows:
        if(N - len(t) != 0):
            row += 1

    print("Case #" + str(i + 1) + ": " + str(trace) + " " + str(row) + " " + str(col))
