# https://app.codility.com/demo/results/trainingZQWJXS-XFH/
def solutionArrayInversionCount(A):
    # write your code in Python 3.6
    sz, aux, i, ans = len(A), [0] * len(A), 1, 0
    def merge(a1, a2, b, arr):
        cnt, i, j, sz1, sz2 = 0, 0, 0, len(a1), len(a2)
        while i < sz1 and j < sz2:
            if a1[i] <= a2[j]: aux[b], i = a1[i], i + 1
            else: aux[b], cnt, j = a2[j], cnt + sz1 - i, j + 1
            b += 1
        while i < sz1: aux[b], i, b = a1[i], i + 1, b + 1
        while j < sz2: aux[b], j, b = a2[j], j + 1, b + 1
        return cnt
    
    while i < sz:
        j = 0
        while j + i <= sz:
            ans += merge(A[j : j + i], A[j + i : min(sz, j + 2 * i)], j, aux)
            if ans > 1000000000: return -1
            j += 2 * i
        for k, val in enumerate(aux): A[k] = val
        i <<= 1
    return ans
