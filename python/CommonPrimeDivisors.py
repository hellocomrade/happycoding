#https://codility.com/demo/results/trainingM3JK3F-58G/
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)
def solution(A, B):
    # write your code in Python 2.7
    cnt = 0
    for i in xrange(len(A)):
        a, b = A[i], B[i]
        g = gcd(a, b)
        while True:
            d = gcd(a, g)
            if 1 == d:
                break
            a /= d
        while True:
            d = gcd(b, g)
            if 1 == d:
                break
            b /= d
        cnt += 1 if a == 1 and b == 1 else 0
    return cnt
