import math
                                                                                                                                                                                      
def solution(total_lambs):                                                                                                                                                                                         
    dBuffer = []
    dIter = 0
    dprefix = 0
    while(dIter < total_lambs):
        currValue = 2**dIter
        dBuffer.append(currValue)
        dprefix += currValue
        if(dprefix > total_lambs):
            break
        dIter += 1
    # print("gen case: " + str(generous_case))
    fibBuffer = [1,1]
    fibprefix = 2
    fibIter = 2
    while(fibIter <= total_lambs):
        value = fibBuffer[fibIter - 2] + fibBuffer[fibIter - 1]
        fibBuffer.append(value)
        fibprefix += int(fibBuffer[fibIter])
        if(fibprefix > total_lambs):
            break
        fibIter += 1
    return len(fibBuffer) - len(dBuffer)  

for i in range(1, 10):
    print("i: " + str(i))
    print(solution(i))
print("Solution for 143")
print(solution(143))
print("Solution for 10")
print(solution(10))
print("Solution for 10**9")
print(solution(10**9))
