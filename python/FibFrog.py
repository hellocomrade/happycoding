#First try 83%: https://codility.com/demo/results/trainingV9VJTJ-VJV/
#Second try 91%: https://codility.com/demo/results/trainingRN29KC-37M/
#Third: https://codility.com/demo/results/training8K76AN-GC2/
#
# Did this one before in C++, but still can't guarantee a 100% till the third submit
# Given a list A, we should do A.append(1) immediately since that's the real destination no matter the original A[-1] is 1 or 0
# See the description: "the frog can get to the other side of the river (from position −1 to position N)"
# 
# Failed on edge cases: [], an empty A should return 1; [0] should return 1; [0,0] should return 1; [1,1,1] should return 2;
def fibonacciUp2N(N):
    fibN = [1, 1]
    while fibN[-1] < N:
        fibN.append(fibN[-1] + fibN[-2])
    return fibN
    
def solutionFibFrog(A):
    # write your code in Python 2.7
    A.append(1)
    size = len(A)
    fibs = fibonacciUp2N(size)
    sizeF = len(fibs)
    if (sizeF > 1):
        fibs, sizeF = fibs[1:], sizeF - 1
    memo = [size + 1] * (size + 1)
    memo[0] = 0
    for i in range(size):
        if 1 == A[i]:
            for j in range(sizeF):
                if fibs[j] <= i + 1:
                    memo[i + 1] = min(memo[i + 1], 1 + memo[i + 1 - fibs[j]])
    return -1 if memo[size] == (size + 1) else memo[size]
