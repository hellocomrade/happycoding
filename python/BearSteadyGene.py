#!/bin/python3

# https://www.hackerrank.com/challenges/bear-and-steady-gene/
#
# Method canBeSettled means a substring has been found to make the whole string steady.
# This is decided by checking if every gene in current counters is no more than 1/4 of the overall size
def canBeSettled(dict, target):
    for cnt in dict.values():
        if cnt > target:
            return False
    return True

def steadyGene(gene):
    size, geneCnt, l, r = len(gene), {}, 0, 0
    ans, avg = size, size / 4
    for g in gene:
        geneCnt[g] = geneCnt[g] + 1 if g in geneCnt else 1
    if True == canBeSettled(geneCnt, avg):
        return 0
    while r < size:
        geneCnt[gene[r]] -= 1
        while True == canBeSettled(geneCnt, avg):
            ans = min(ans, r - l + 1)
            geneCnt[gene[l]] += 1
            l += 1
        r += 1
    return ans
