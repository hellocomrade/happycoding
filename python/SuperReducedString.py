#!/bin/python3
from functools import reduce

# https://www.hackerrank.com/challenges/reduced-string/
def super_reduced_string(s):
    ans = reduce(lambda str, c : str + c if 0 == len(str) or str[-1] != c else str[:-1] if len(str) > 0 else "", s)
    return ans if len(ans) > 0 else "Empty String"
