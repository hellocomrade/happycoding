#https://codility.com/demo/results/trainingNE5FFD-8AF/
def solution(N, A):
    ans = [0] * N
    maxAtHere, maxSofar = 0, 0
    for i in A:
        if i == N + 1:
            maxSofar = max(maxSofar, maxAtHere)
        else:
            ans[i - 1] = ans[i - 1] + 1 if ans[i - 1] >= maxSofar else maxSofar + 1
            maxAtHere = max(ans[i - 1], maxAtHere)
    for i in xrange(N):
        if ans[i] < maxSofar:
            ans[i] = maxSofar
    return ans
