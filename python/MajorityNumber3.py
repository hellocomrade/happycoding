#http://www.lintcode.com/en/problem/majority-number-iii/
class SolutionMajorityNumber3:
    """
    @param nums: A list of integers
    @param k: As described
    @return: The majority number
    """
    def majorityNumber(self, nums, k):
        # write your code here
        l = len(nums)
        if l < 1 or k < 1:
            return -1
        kth = {}
        for i in nums:
            if len(kth) < k - 1:
                if i in kth:
                    kth[i] += 1
                else:
                    kth[i] = 1
            else:
                if i in kth:
                    kth[i] += 1
                else:
                    for key in kth.keys():
                        kth[key] -= 1
                        if kth[key] == 0:
                            del kth[key]
        if len(kth) > 0:
            s = l // k
            cnt = 0
            for key in kth.keys():
                for i in nums:
                    if i == key:
                        cnt += 1
                #print "{0},{1}".format(key, cnt)
                if cnt > s:
                    return key
                else:
                    cnt = 0
        return -1
