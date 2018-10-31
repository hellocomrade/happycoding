# https://leetcode.com/problems/gray-code/
#
# Use keyword nonlocal to access outter variable that is changed internally
# https://www.python.org/dev/peps/pep-3104/
class SolutionGrayCode:
    """
    @param n: a number
    @return: Gray code
    """
    def grayCode(self, n):
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
