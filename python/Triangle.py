#https://leetcode.com/problems/triangle/
#
# Write for comparison purpose with Scala version at:https://github.com/hellocomrade/happycoding/blob/master/scala/Triangle.scala
#
# Note: this won't be the fastest Python version. It's just a practice effort on functional programming
#
from functools import reduce

class TriangleSolution(object):
    def minimumTotal(self, triangle):
        """
        :type triangle: List[List[int]]
        :rtype: int
        """
        return 0 if 0 == len(triangle) else \
        reduce(lambda memo, tri: [min(tri[i] + memo[i], tri[i] + memo[i + 1]) for i in range(len(tri))],
               reversed(triangle))[0]

def test():
    so = TriangleSolution
    assert -10 == so.minimumTotal([[-10]])
    assert 11 == so.minimumTotal([[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]])
