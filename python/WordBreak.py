#https://leetcode.com/problems/word-break/
class SolutionWordBreak(object):
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """
        maxLen = 0 if 0 == len(wordDict) else len(reduce(lambda x, y : x if len(x) > len(y) else y, wordDict))
        strLen = len(s)
        memo = [False] * (strLen + 1)
        memo[0] = True
        dictionary = set(wordDict)
        for i in range(1, strLen + 1):
            for j in range(i - 1, -1, -1):
                if i - j > maxLen:
                    break
                if True == memo[j] and s[j : i] in dictionary:
                    memo[i] = True
                    break
        return memo[strLen]
