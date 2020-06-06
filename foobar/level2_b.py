import math
                                                                                                                                                                                      
def solution(total_lambs):                                                                                                                                                                                         
    if(total_lambs == 1):
        return 0                                                                                                           
    if(total_lambs == 2):                                                                               
        return 1                                                                                                                                                                                                      
    if(total_lambs == 4):
        return 1
    generous_case = int(math.log(total_lambs, 2))                                                                                                                                                             
    gen_verify = (2**generous_case) - 1                                                                        
    if((total_lambs - gen_verify) >= (2**(generous_case - 1) + 2**(generous_case - 2)) and (total_lambs - gen_verify) <= (2**generous_case)):                                                                               
        generous_case += 1                                     
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
    return len(fibBuffer) - generous_case  

for i in range(1, 10):
    print("i: " + str(i))
    print(solution(i))
print("Solution for 143")
print(solution(143))
print("Solution for 10")
print(solution(10))
print("Solution for 10**9")
print(solution(10**9))
