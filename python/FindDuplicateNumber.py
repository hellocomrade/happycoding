class Solution:
    def findDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i, j, m, cnt = 1, len(nums) - 1, 0, 0
        while i <= j:
            m, cnt = (i + j) // 2, 0
            for k in nums:
                if k <= m:
                    cnt += 1
            #print("{},{}".format(m, cnt))
            if cnt > m:
                j = m - 1
            else:
                i = m + 1
        return i
        
    def findDuplicate1(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        i, j, m, cnt = 1, len(nums) - 1, 0, 0
        while i <= j:
            m, cnt = (i + j) // 2, 0
            for k in nums:
                if k < m:
                    cnt += 1
            #print("{},{}".format(m, cnt))
            if cnt > m - 1:
                j = m - 1
            else:
                i = m + 1
        return i - 1
