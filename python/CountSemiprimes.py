#https://codility.com/demo/results/training56JA7K-E86/
# you can write to stdout for debugging purposes, e.g.
# print "this is a debug message"
def factorization(N):
    f = [0] * (N + 1)
    f[0] = f[1] = -1
    i = 2
    while i * i <= N:
        if f[i] == 0:
            k = i * i
            while k <= N:
                if f[k] == 0:
                   f[k] = i
                k += i
        i += 1
    return f
def solution(N, P, Q):
    # write your code in Python 2.7
    ans = []
    prefixSum = [0] * (N + 1)
    fact = factorization(N)
    for i in xrange(2, N+1):
        if fact[i] != 0 and fact[i // fact[i]] == 0:
            prefixSum[i] = prefixSum[i - 1] + 1
        else:
            prefixSum[i] = prefixSum[i - 1]
    for i in xrange(len(P)):
        ans += [prefixSum[Q[i]] - prefixSum[P[i] - 1]]
    return ans
