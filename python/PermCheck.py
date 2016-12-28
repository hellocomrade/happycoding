#https://codility.com/demo/results/trainingBTGWMG-N4X/
#
#no need for the extra O(N) space, it can be done with O(1) space and O(N) time
def solution(A):
    size = len(A)
    for i in range(size):
        while A[i] != i + 1:
            if A[i] > size or A[A[i] - 1] == A[i]: return 0
            A[A[i] - 1], A[i] = A[i], A[A[i] - 1]
    return 1
