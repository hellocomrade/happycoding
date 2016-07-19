#https://leetcode.com/problems/minimum-size-subarray-sum/
class SolutionMinSizeSubArrSum(object):
    def minSubArrayLen(self, s, nums):
        """
        :type s: int
        :type nums: List[int]
        :rtype: int
        """
        size = len(nums)
        ans = size + 1
        i, j, sum = 0, 0, 0
        while j <= size:
            if sum < s:
                if j == size:
                    break
                sum += nums[j]
                j += 1
            else:
                ans = min(ans, j - i)
                sum -= nums[i]
                i += 1
        return ans if ans != size + 1 else 0
