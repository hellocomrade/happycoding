#https://codility.com/demo/results/training55SF2F-ART/
def solutionCountTriangles(A):
    ans, size = 0, len(A)
    A.sort()
    for i in range(size - 2):
        k = i + 2
        for j in range(i + 1, size - 1):
            while k < size and A[i] + A[j] > A[k]:
                k = k + 1
            ans = ans + k - j - 1
    return ans
