#https://codility.com/demo/results/training4R2GD2-96Z/
def solution(S, P, Q):
    ans = []
    candidate = None
    cntS = len(S)
    lookup = {'A': 0, 'C': 1, 'G': 2, 'T': 3}  
    memo = [cntS * [cntS] for i in xrange(4)]
    memo[lookup[S[cntS - 1]]][cntS - 1] = cntS - 1
    for i in xrange(cntS - 2, -1, -1):
        for j in xrange(4):
            memo[j][i] = memo[j][i + 1]
        memo[lookup[S[i]]][i] = i
    for p, q in zip(P, Q):
        if memo[0][p] <= q: candidate = 1
        elif memo[1][p] <= q: candidate = 2
        elif memo[2][p] <=q: candidate = 3
        else: candidate = 4
        ans.append(candidate)
    return ans
