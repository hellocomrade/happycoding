# https://codility.com/demo/results/trainingYXSX3P-BKV/
# Simplicity of Python? Zen of Python?
# Note: the [-1] appended to the list comprehension is absoultely necessary if there is no valid result at all in given S
# max() can't handle a list with zero element and will throw exception.
def solution(S):
    return max([len(str) for str in S.split() if len(str) & 1 and str.isalnum() and sum(c.isdigit() for c in str) & 1] + [-1])
