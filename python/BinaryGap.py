#https://codility.com/demo/results/trainingXZ9RGF-H3P/
def solutionBinaryGap(N):
    i = 1 << (32 - 2)
    maxLen, cnt, flag = 0, 0, 0
    while i:
        if N & i:
            if 0 == flag:
                flag = 1
            else:
                maxLen = max(maxLen, cnt)
                cnt = 0
        elif 1 == flag:
            cnt += 1
        i >>= 1
    return maxLen
