# Ugly but works, for a better impl
# See: https://github.com/hellocomrade/happycoding/blob/master/leetcode/FindPeakElement.cpp
class SolutionFindPeakElement:
    def findPeakElement(self, nums: List[int]) -> int:
        l, r, sz = 0, len(nums) - 1, len(nums)
        if 1 == sz:
            return 0
        while l <= r:
            mid = l + (r - l) // 2
            if (0 == mid and nums[mid] > nums[mid + 1]) or (mid == sz - 1 and nums[mid] > nums[mid - 1]) or (nums[mid] > nums[mid - 1] and nums[mid] > nums[mid + 1]):
                return mid
            elif 0 == mid or nums[mid] < nums[mid + 1]:
                l = l + 1
            else:
                r = r - 1
        return -1
