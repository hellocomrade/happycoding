class SolutionCombinations_2Slow:
    def _aux(self, ans, arr, begin, end, k, idx):
        if idx == k:
            ans.append([i for i in arr])
            return
        for i in range(begin, end):
            arr[idx] = i
            self._aux(ans, arr, i + 1, end, k, idx + 1) 
    """    
    @param n: Given the range of numbers
    @param k: Given the numbers of combinations
    @return: All the combinations of k numbers out of 1..n   
    """
    def combine(self, n, k):      
        # write your code here 
        ans = []
        if n >= k and k >= 0:
            arr = [0] * k
            self._aux(ans, arr, 1, n + 1, k, 0)
        return ans
        
class SolutionCombinations1(object):
    def _aux(self, ans, ret, i, k, n):
        if k == 0:
            return ans.append(ret[:])
        for j in range(i, n + 1):
            if j + k > n + 1: return
            ret.append(j)
            self._aux(ans, ret, j + 1, k - 1, n)
            ret.pop()
            
    def combine(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[List[int]]
        """
        ans, ret = [], []
        if n >= 1 and k > 0:
            self._aux(ans, ret, 1, k, n)
        return ans

class SolutionCombinations2(object):
    def _aux(self, ans, ret, i, k, n):
        if k == 0:
            return ans.append(ret[:])
        for j in range(i, n + 1):
            if j + k > n + 1: return
            ret.append(j)
            self._aux(ans, ret, j + 1, k - 1, n)
            ret.pop()
            
    def combine(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[List[int]]
        """
        ans, ret = [], []
        if n >= 1 and k > 0:
            self._aux(ans, ret, 1, k, n)
        return ans
