#https://leetcode.com/problems/interleaving-string
class SolutionInterleavingString(object):
    def isInterleave(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        lenS1, lenS2 = len(s1), len(s2)
        # if s3's length is not equal to len(s1) + len(s2), there is no need to move forward
        # For example s1 = "a", s2 = "b", s3 = "a"
        if len(s3) != lenS2 + lenS1:
            return False
        #Reduce memory on list memo by picking the shorter string between s1 and s2 as X axis
        strShorter = s1 if lenS1 <= lenS2 else s2
        strLonger = s2 if strShorter == s1 else s1
        lenStrShorter, lenStrLonger = len(strShorter), len(strLonger)
        memo = [False] * (lenStrShorter + 1)
        for i in range(lenStrLonger + 1):
            for j in range(lenStrShorter + 1):
                if 0 == i and 0 == j:
                    memo[0] = True
                elif 0 == i:
                    memo[j] = True if (s3[j - 1] == strShorter[j - 1] and True == memo[j - 1]) else False
                elif 0 == j:
                    memo[0] = True if (s3[i - 1] == strLonger[i - 1] and True == memo[0]) else False
                else:
                    memo[j] = True if ((s3[i + j - 1] == strShorter[j - 1] and True == memo[j - 1]) or (s3[i + j - 1] == strLonger[i - 1] and True == memo[j])) else False
        return memo[lenStrShorter]
