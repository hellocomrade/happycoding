#https://leetcode.com/problems/next-permutation/
#it appears your python code could run faster if comments are removed?
class SolutionNextPermutation:
    # @param num :  a list of integer
    # @return : a list of integer
    def nextPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        size = len(nums)
        if size > 0:
            i, j = size - 1, -1
            while i > 0 and nums[i - 1] >= nums[i]:
                i -= 1
            if i > 0:
                while nums[j] <= nums[i - 1]:
                    j -= 1
                nums[j], nums[i - 1] = nums[i - 1], nums[j]
            #not like lintcode, leetcode requires returning nothing, so nums must be reversed in place
            #the following approach will not work since it creates a new list and
            #python passing parameter by value
            #nums = nums[0 : i] + nums[-1 : i - size - 1 : -1]
            #instead, we only modify nums using slice, which will actually change
            #elements inside nums. The following is actually faster than a loop to swap elements pairs
            nums[i:] = nums[-1 : i - size - 1 : -1]
