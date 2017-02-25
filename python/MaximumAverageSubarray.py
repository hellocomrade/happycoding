#http://www.lintcode.com/en/problem/maximum-average-subarray/
class SolutionMaximumAverageSubarray:
    # @param {int[]} nums an array with positive and negative numbers
    # @param {int} k an integer
    # @return {double} the maximum average
    # This one doesn't use monotonic pair trick, but a simplier approach using a window on array that is no less than K 
    def maxAverage(self, nums, k):
        ans, err = 0, 1e-8
        if nums and k > 0:
            count = len(nums)
            prefixSum = [0.0] * (1 + count)
            l, r, mid, minSofar = min(nums), max(nums), 0.0, 0.0
            ans, flag = l, False
            while r - l >= err:
                mid, minSofar, flag = (r + l) / 2.0, 0.0, False
                for i in range(1, count + 1):
                    prefixSum[i] = prefixSum[i - 1] + nums[i - 1] - mid
                    if i >= k:
                        if prefixSum[i] - minSofar >= err:
                            ans, flag = max(mid, ans), True
                            break
                        minSofar = min(minSofar, prefixSum[i - k + 1])
                if flag:
                    l = mid
                else:
                    r = mid
        return 0.0 if abs(ans) < err else ans
    # This version Time Limit Exceeded
    def maxAverage1(self, nums, k):
        ans, err = 0, 1e-8
        if nums and k > 0:
            count = len(nums)
            prefixSum = [0.0] * count
            l, r, m = min(nums), max(nums), 0.0
            ans = l
            while r - l >= err:
                m, size, stk = l + (r - l) / 2.0, 0, []
                prefixSum[0] = nums[0] - m
                for i in range(1, count):
                    if prefixSum[i - 1] >= err:
                        size = max(size, i)
                    prefixSum[i] = prefixSum[i - 1] + nums[i] - m
                # don't forget the last one
                if prefixSum[count - 1] >= err:
                    size = max(size, count)
                if size < k:
                    stk.append((prefixSum[count - 1], count - 1))
                    for i in range(count - 2, -1, -1):
                        if prefixSum[i] > stk[-1][0]:
                            stk.append((prefixSum[i], i))
                    for i in range(0, count):
                        while len(stk) > 0 and prefixSum[i] < stk[-1][0]:
                            size = max(size, stk[-1][1] - i)
                            if size >= k:
                                break
                            stk.pop()
                if size >= k:
                    ans = max(ans, m)
                    l = m
                else:
                    r = m
        return 0.0 if abs(ans) < err else ans
