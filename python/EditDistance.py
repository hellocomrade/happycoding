#https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
class SolutionEditDistance(object):
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        len1, len2, upperLeft, tmp = len(word1), len(word2), 0, 0
        memo = range(0, len1 + 1)
        for row in range(1, len2 + 1):
            upperLeft, memo[0] = memo[0], row
            for col in range(1, len1 + 1):
                tmp = memo[col]
                if word1[col - 1] == word2[row - 1]:
                    memo[col] = upperLeft
                else:
                    memo[col] = min(upperLeft + 1, memo[col - 1] + 1, memo[col] + 1)
                upperLeft = tmp
        return memo[len1]
