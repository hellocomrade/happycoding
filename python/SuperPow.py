# https://leetcode.com/problems/super-pow/
class SolutionSuperPow:
    def superPow(self, a, b):
        """
        :type a: int
        :type b: List[int]
        :rtype: int
        """
        ans, mod = 1, 1337
        def fast_pow(a, n, mod):
            ans, x, i = 1, a, 1
            while i <= n:
                if 0 != (i & n):
                    ans = (ans * x) % mod
                x = (x * x) % mod
                i <<= 1
            return ans
            
        for i in b:
            ans = fast_pow(a, i, mod) * fast_pow(ans, 10, mod) % mod
        return ans
