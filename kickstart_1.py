testcases = int(input())
for i in range(testcases):
    num_houses, budget = map(int, input().split())
    house_bucket = map(int, input().split())
    house_bucket = sorted(house_bucket)
    houses = 0
    for j in house_bucket:
        if(j <= budget):
            houses += 1
            budget -= j
        else:
            break
    print("Case #" + str(i) + ": " + str(houses))
