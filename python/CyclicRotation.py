#https://codility.com/demo/results/trainingZHF5BH-5NM/
def solution(A, K):
    # write your code in Python 2.7
    if not A:
        return []
    size = len(A)
    K = K % size
    l = A[-K - 1:-size - 1:-1] + A[-1:-K - 1:-1]
    return l[::-1]
