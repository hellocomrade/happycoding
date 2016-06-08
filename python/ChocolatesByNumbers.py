#https://codility.com/demo/results/trainingWXTUUR-BVE/
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)
def solution(N, M):
    # write your code in Python 2.7
    g = gcd(N, M)
    return N / g
