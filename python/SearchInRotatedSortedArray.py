# https://leetcode.com/problems/search-in-rotated-sorted-array/
class SolutionSearchInRotatedSortedArray:
    def search(self, nums: List[int], target: int) -> int:
        l, r, m = 0, len(nums) - 1, 0
        while l <= r:
            m = (l + r) // 2
            if nums[m] == target: 
                return m
            if nums[m] < target:
                if (nums[0] <= target) ^ (nums[0] <= nums[m]):
                    r = m - 1
                else:
                    l = m + 1
            else:
                if (nums[0] <= target) ^ (nums[0] <= nums[m]):
                    l = m + 1
                else:
                    r = m - 1
        return -1
