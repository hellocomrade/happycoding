#https://codility.com/demo/results/training678XY4-C56/
from functools import reduce

def solution(A):
    # write your code in Python 2.7
    return reduce(lambda a, b : a ^ b, A)
