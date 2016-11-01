#https://codility.com/demo/results/trainingAZVZNA-7P7/
def solutionAbsDistinct(A):
    size = len(A)
    front, end, last, count = 0, size - 1, None, 0
    while front < end:
        if abs(A[front]) >= abs(A[end]):
            last = abs(A[front])
            front += 1
        else:
            last = abs(A[end])
            end -= 1
        while front < size and abs(A[front]) == last:
            front += 1
        while end > -1 and abs(A[end]) == last:
            end -= 1
        count += 1
    if front == end and last != abs(A[front]):
        count += 1
    return count
