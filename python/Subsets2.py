# https://leetcode.com/problems/subsets-ii/
"""
Iteration version of Subset2. Backtracing version is in C++

Sort first then build the ans in an appending mode. Avoid duplicates by starting from the last appending position for nums[i - 1]
in ans if nums[i] == nums[i - 1]

Given [1, 2, 2]
1: []
2: [] + [1]
3: [], [1] + [2], [1, 2]
4: [], [1], [2], [1, 2] + [2, 2], [1, 2, 2]

On step 4, found duplicates, instead of appending from index 0 in ans, we start from index 2 in ans.
"""
class SolutionSubset2:
    def subsetsWithDup(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        nums.sort()
        ans, m = [[]], 0
        for i in range(len(nums)):
            n, m = m, len(ans)
            if 0 == i or nums[i] != nums[i - 1]:
                n = 0
            for j in range(n, m):
                ans.append(ans[j] + [nums[i]])
        return ans
