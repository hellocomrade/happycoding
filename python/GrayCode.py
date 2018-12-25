# https://leetcode.com/problems/gray-code/
class SolutionGrayCode:
    # Iterative
    def grayCode(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        ans = [0]
        for i in range(n):
            ans += [1 << i | j for j in reversed(ans)]
        return ans
    
    # Backtracing
    # Use keyword nonlocal to access outter variable that is changed internally
    # https://www.python.org/dev/peps/pep-3104/
    def grayCode0(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        ans, i = [], 0
        def fun(n):
            nonlocal i
            if 0 == n:
                ans.append(i)
            else:
                fun(n - 1)
                i ^= 1 << (n - 1)
                fun(n - 1)
        
        fun(n)
        return ans

    """
    @param n: a number
    @return: Gray code
    """
    def grayCode1(self, n):
        i, ans = 0, []
        def fun(idx):
            nonlocal i
            if idx == n:
                ans.append(i)
            else:
                fun(idx + 1)
                i ^= 1 << idx
                fun(idx + 1)
        fun(0)
        return ans
 
