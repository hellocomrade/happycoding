from functools import reduce

#https://leetcode.com/problems/happy-number/
class Solution:
    def fun(self, n):
        ans, t = 0, 0
        while n > 0:
            t = n % 10
            ans += t ** 2
            n //= 10
        return ans
    
    def isHappy(self, n):
        """
        :type n: int
        :rtype: bool
        """
        #fun = lambda m: reduce(lambda a, b: a + b ** 2, [0] + [int(c) for c in str(m)])
        #Using lambda here is slower than plain function due to the way to extract digits
        fun = lambda m: sum([int(c) ** 2 for c in str(m)])
        hare, tortoise = n, n
        while True:
            hare, tortoise = self.fun(self.fun(hare)), self.fun(tortoise)
            if hare == tortoise:
                break;
        return 1 == hare
