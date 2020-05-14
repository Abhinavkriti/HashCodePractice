import numpy as np

testcases = int(input())
for i in range(testcases):
    N, K = map(int, input().split())
    session_min = np.array(list(map(int, input().split())))
    current_diff = None
    while(K > 0):
        current_diff = np.asarray([t - s for s, t in zip(session_min, session_min[1:])])
        max_curr_diff = np.max(current_diff)
        max_index = np.argmax(current_diff)
        session_min = np.insert(session_min, max_index + 1, (session_min[max_index] + session_min[max_index + 1])/2)
        K -= 1
    current_diff = np.asarray([t - s for s, t in zip(session_min, session_min[1:])])
    print("Case #" + str(i + 1) + ": " + str(np.max(current_diff)))
