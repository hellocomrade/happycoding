#https://leetcode.com/problems/longest-consecutive-sequence/
class SolutionLongestConsecutiveSequence(object):
    def longestConsecutive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        memo, ans, cnt = set(), 0, 0
        for i in nums:
            memo.add(i)
        for i in nums:
            if False == (i - 1 in memo):
                cnt = 1
                while (i + cnt) in memo:
                    cnt = cnt + 1
                ans = max(ans, cnt)
        return ans
