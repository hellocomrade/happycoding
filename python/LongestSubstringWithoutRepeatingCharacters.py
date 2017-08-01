# https://leetcode.com/problems/longest-substring-without-repeating-characters/
class SolutionLongestSubstringWithoutRepeatingCharacters(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        memo, start, ans = dict(), 0, 0
        for i in range(len(s)):
            if s[i] in memo and (memo[s[i]] >= start):
                ans = max(ans, i - start)
                start = memo[s[i]] + 1
            memo[s[i]] = i
        return max(ans, len(s) - start)
