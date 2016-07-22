#https://codility.com/demo/results/training35TMTU-RKD/
def solutionPermMissingElem(A):
    size = len(A)
    return (size + 1) * (size + 2) / 2 - sum(A)
