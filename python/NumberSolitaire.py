#https://codility.com/demo/results/trainingJVSSXY-EN5/
def solution(A):
    # write your code in Python 2.7
    size = len(A)
    memo = [-10000] * 6
    memo[0] = A[0]
    for step in range(1, size):
        memo[step % 6] = max(memo) + A[step]
    return memo[(size - 1) % 6]
