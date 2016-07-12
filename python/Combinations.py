class SolutionCombinations:
    def __aux(self, ans, arr, begin, end, k, idx):
        if idx == k:
            ans.append([i for i in arr])
            return
        for i in xrange(begin, end):
            arr[idx] = i
            self.__aux(ans, arr, i + 1, end, k, idx + 1) 
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
            self.__aux(ans, arr, 1, n + 1, k, 0)
        return ans
