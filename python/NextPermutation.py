#https://leetcode.com/problems/next-permutation/
class SolutionNextPermutation:
    # @param num :  a list of integer
    # @return : a list of integer
    def nextPermutation(self, num):
        size = len(num)
        if size > 0:
            i, j = size - 1, -1
            while i > 0 and num[i - 1] >= num[i]:
                i -= 1
            if i > 0:
                while num[j] <= num[i - 1]:
                    j -= 1
                num[j], num[i - 1] = num[i - 1], num[j]
            num = num[0 : i] + num[-1 : i - size - 1 : -1]
        return num
