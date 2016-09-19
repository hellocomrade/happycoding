# http://www.lintcode.com/en/problem/jump-game-ii/
class SolutionJumpGame2:
    # @param A, a list of integers
    # @return an integer
    def jump(self, A):
        size = len(A) - 1
        nextStop, longestStop, jmp = 0, 0, 0
        for i in xrange(size):
            if i + A[i] >= size:
                return jmp + 1
            longestStop = max(longestStop, i + A[i])
            if i == nextStop:
                if longestStop == nextStop:
                    return -1
                nextStop = longestStop
                jmp += 1
        return jmp
