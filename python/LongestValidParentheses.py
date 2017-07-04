#https://leetcode.com/problems/longest-valid-parentheses
class SolutionLongestValidParentheses(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        size, ans = len(s), 0
        memo = [0] * size
        for i in range(1, size):
            if ')' == s[i] and i - memo[i - 1] > 0 and '(' == s[i - memo[i - 1] - 1]:
                memo[i] = memo[i - 1] + 2 + (memo[i - memo[i - 1] - 2] if i - memo[i - 1] > 1 else 0)
                ans = max(ans, memo[i])
        return ans
    
    def longestValidParentheses1(self, s):
        """
        :type s: str
        :rtype: int
        """
        size, ans = len(s), 0
        memo = [0] * size
        for i in range(1, size):
            if ')' == s[i] and i - memo[i - 1] - 1 >= 0 and '(' == s[i - memo[i - 1] - 1]:
                memo[i] = memo[i - 1] + 2
                if i - memo[i - 1] - 2 >= 0:
                    memo[i] = memo[i] + memo[i - memo[i - 1] - 2]
                ans = max(ans, memo[i])
        return ans
