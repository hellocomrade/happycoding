class SolutionMaxLengthOfRepeatedSubarray:
    def findLength(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: int
        """
        ans, lena, lenb = 0, len(A), len(B)
        memo = [0] * (lenb + 1)
        for i in range(lena):
            for j in reversed(range(lenb)):
                memo[j + 1] = memo[j] + 1 if B[j] == A[i] else 0
                ans = max(ans, memo[j + 1])
        return ans
    def findLength1(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: int
        """
        ans, prev, t = 0, 0, 0
        memo = [0] * (len(B) + 1)
        for i in range(len(A)):
            prev = memo[0]
            for j in range(len(B)):
                if B[j] == A[i]:
                    t = memo[j + 1]
                    memo[j + 1] = prev + 1
                    ans = max(ans, memo[j + 1])
                else:
                    t, memo[j + 1] = memo[j + 1], 0
                prev = t
            #print(','.join(str(x) for x in memo))
        return ans
"""
Test cases:
[1,2,3,2,1]
[3,2,1,4,7]
[1,2,3]
[3,2,1]
[1]
[1]
[1,1,1,1,1]
[1,1,1]
[1,1,1,1]
[1,1,1,1]
[1,1,1,0,0,1,0,0,1,0]
[0,1,0,0,1,1,0]
Results:
3
1
1
3
4
5
"""
