#https://codility.com/demo/results/training4NGMVM-MQT/
#Ref: pigeonhole principle 
def solutionMissingInteger(A):
    size = len(A)
    B = [0] * (size + 1)
    for i in range(size):
        if A[i] > 0 and A[i] <= size:
            B[A[i]] = 1
    for i in range(1, size + 1):
        if B[i] == 0:
            return i
    return size + 1
