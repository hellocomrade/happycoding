# https://leetcode.com/problems/scramble-string/
class SolutionScrambleString:

    # Copy/paste from leetcode, I would never think using decorator to handle memorization!
    def memoize(func):
        memo={}
        def wrapper(*args):
            if args in memo: return memo[args]
            res=func(*args)
            memo[args]=res
            return res
    
        return wrapper
    
    @memoize
    def isScramble(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        if len(s1) != len(s2):
            return False
        if sorted(s1) != sorted(s2):
            return False
        if len(s1) < 4 or s1 == s2:
            return True
        f = self.isScramble
        for i in range(1, len(s1)):
            if (f(s1[i:], s2[i:]) and f(s1[:i], s2[:i])) or \
            (f(s1[i:], s2[:-i]) and f(s1[:i], s2[-i:])):
                return True
        return False

    # It appears replacing 3d list with dictionary could boost performace?
    # Also, built-in sorted replaces count sort, seems to improve performae as well? Got 48ms, beat 100%...really...
    def isScramble0(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        len1, len2 = len(s1), len(s2)
        if len1 != len2: return False
        memo = {}
        def aux(s1, s2, i, j, sz):
            if 1 == sz: return s1[i] == s2[j]
            if (i, j, sz - 1) in memo: return memo[(i, j, sz - 1)]
            cnt = [0] * 26
            if sorted(s1[i : i + sz]) != sorted(s2[j : j + sz]):
                memo[(i, j, sz - 1)] = False
                return False
            ans, f = False, aux
            for k in range(1, sz):
                ans = (f(s1, s2, i, j, k) and f(s1, s2, i + k, j + k, sz - k)) or (f(s1, s2, i, j + sz - k, k) and f(s1, s2, i + k, j, sz - k))
                if True == ans: break
            memo[(i, j, sz - 1)] = ans
            return ans
        
        return aux(s1, s2, 0, 0, len1)   

    # Pay attention on how memo is created.
    # Originally using [[[-1]*len1]*len1]*len1, which created a 3d array from shallow copy of [-1]*len1]. 
    # Therefor, any change on memo[i][j][k] will affect others as well.
    def isScramble1(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        len1, len2 = len(s1), len(s2)
        if len1 != len2: return False
        memo = [[[-1 for _ in range(len1)] for _ in range(len1)] for _ in range(len1)]
        def aux(s1, s2, i, j, sz):
            if 1 == sz: return s1[i] == s2[j]
            if -1 != memo[i][j][sz - 1]: return True if 1 == memo[i][j][sz - 1] else False
            cnt = [0] * 26
            for k in range(sz):
                cnt[ord(s1[i + k]) - ord('a')] += 1
                cnt[ord(s2[j + k]) - ord('a')] -= 1
            for k in cnt: 
                if 0 != k:
                    memo[i][j][sz - 1] = 0
                    return False
            ans = False
            for k in range(1, sz):
                ans = (aux(s1, s2, i, j, k) and aux(s1, s2, i + k, j + k, sz - k)) or (aux(s1, s2, i, j + sz - k, k) and aux(s1, s2, i + k, j, sz - k))
                if True == ans: break
            memo[i][j][sz - 1] = 1 if True == ans else 0
            return ans
        
        return aux(s1, s2, 0, 0, len1)
  
