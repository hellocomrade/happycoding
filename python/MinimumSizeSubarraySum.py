#https://leetcode.com/problems/minimum-size-subarray-sum
#https://leetcode.com/articles/minimum-size-subarray-sum/
class SolutionMinimumSizeSubarraySum(object):
    def minSubArrayLen_ON_1(self, s, nums):
        """
        :type s: int
        :type nums: List[int]
        :rtype: int
        """
        size = len(nums)
        l, sum, ans = 0, 0, size + 1, 
        for i in range(0, size):
            sum += nums[i]
            while sum >= s:
                ans = min(ans, i - l + 1)
                sum -= nums[l]
                l += 1
        return 0 if ans == size + 1 else ans
        
    def minSubArrayLen_ON_2(self, s, nums):
        """
        :type s: int
        :type nums: List[int]
        :rtype: int
        """
        l, r, sum, ans, size = 0, 0, 0, len(nums) + 1, len(nums)
        while l < size and r <= size:
            if sum >= s:
                ans = min(ans, r - l)
                if 1 == ans:
                    break
                sum -= nums[l]
                l += 1
            else:
                if r < size:
                    sum += nums[r]
                r += 1
        return 0 if ans == size + 1 else ans
    
    def minSubArrayLen_NlogN(self, s, nums):
        """
        :type s: int
        :type nums: List[int]
        :rtype: int
        """
        size = len(nums)
        if 0 == size:
            return 0
        ans, idx = size + 1, 0
        # Since nums are filled with positives, prefix sum is an monotonic increasing list
        for i in range(1, size):
            nums[i] += nums[i - 1]
        for i in range(0, size):
            idx = bisect.bisect_left(nums, s + (nums[i - 1] if i > 0 else 0))
            if idx < size:
                ans = min(ans, idx - i + 1)
        return 0 if size + 1 == ans else ans
