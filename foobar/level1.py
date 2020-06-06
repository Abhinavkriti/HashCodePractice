import math
def solution(area):
    area_list = []
    while(area >= 4):
        low_sq = int(math.sqrt(area))
        area_list.append(low_sq**2)
        area -= low_sq**2
    for i in range(area):
        area_list.append(1)
    return area_list

print(solution(12))
print(solution(15324))
