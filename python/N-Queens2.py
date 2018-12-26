# https://leetcode.com/problems/n-queens-ii/
class SolutionNQueens2:
    """
    @param n: The number of queens.
    @return: The total number of distinct solutions.
    """
    def totalNQueens(self, n):
        ans, colMemo, diag1Memo, diag2Memo = 0, [False] * n, [False] * (2 * n - 1), [False] * (2 * n - 1)
        def bt(rowIdx):
            nonlocal ans
            if rowIdx == n:
                ans += 1
                return
            for i in range(n):
                if True == colMemo[i] or True == diag1Memo[rowIdx + i] or True == diag2Memo[n - rowIdx + i - 1]:
                    continue
                colMemo[i] = diag1Memo[rowIdx + i] = diag2Memo[n - rowIdx + i - 1] = True
                bt(rowIdx + 1)
                colMemo[i] = diag1Memo[rowIdx + i] = diag2Memo[n - rowIdx + i - 1] = False
        
        bt(0)
        return ans
