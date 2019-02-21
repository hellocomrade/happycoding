import itertools

# https://leetcode.com/problems/compare-version-numbers/ 
class Solution:
    def compareVersion(self, version1: 'str', version2: 'str') -> 'int':
        for (i, j) in itertools.zip_longest(*(map(int, v.split('.')) for v in (version1, version2)), fillvalue=0):
            if i != j: return 1 if i > j else -1
        return 0


    # Recursive ver,
    def compareVersion(self, version1: 'str', version2: 'str') -> 'int':
        s1, _, r1 = version1.partition('.')
        s2, _, r2 = version2.partition('.')
        i1, i2 = int(s1), int(s2)
        if i1 != i2: return 1 if i1 > i2 else -1
        if not r1 and not r2: return 0
        return self.compareVersion(r1 if len(r1) > 0 else '0', r2 if len(r2) > 0 else '0')
