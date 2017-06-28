#https://leetcode.com/problems/longest-increasing-subsequence/
class SolutionLIS:
    """
    @param nums: The integer array
    @return: The length of LIS (longest increasing subsequence)
    """
    def longestIncreasingSubsequence_DP(self, nums):
        memo, ans = [1] * len(nums), 1
        for i in range(1, len(nums)):
            for j in range(0, i):
                if nums[j] < nums[i]:
                    memo[i] = max(memo[i], memo[j] + 1)
            ans = max(ans, memo[i])
        return ans if len(nums) > 0 else 0
        
    def longestIncreasingSubsequence_NlogN(self, nums):
        ans, tmp = 0, 0
        for i in range(1, len(nums)):
            #Find rightmost value in sublist of nums that is no less than nums[i]
            tmp = bisect.bisect_left(nums[0 : ans + 1], nums[i])
            if tmp > ans:
                ans += 1
                nums[ans] = nums[i]
            else:
                nums[tmp] = nums[i]
        return ans + 1 if len(nums) > 0 else 0
