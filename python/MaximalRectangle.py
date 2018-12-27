# https://leetcode.com/problems/maximal-rectangle/
class SolutionMaximalRectangle:
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if 1 > len(matrix): return 0
        sz = len(matrix[0]) + 1
        memo, ans = [0] * sz, 0
        for row in matrix:
            stk = [-1]
            for i in range(sz):
                if i < sz - 1: memo[i] = 0 if '0' == row[i] else memo[i] + 1
                while memo[stk[-1]] > memo[i]:
                    ans = max(ans, memo[stk.pop()] * (i - 1 - stk[-1]))
                stk.append(i)
        return ans
 
