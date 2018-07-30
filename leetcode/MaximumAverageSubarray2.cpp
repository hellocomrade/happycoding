#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/maximum-average-subarray-ii
/*
644 Maximum Average Subarray II

Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value.
And you need to output the maximum average value.

Example 1:

Input: [1,12,-5,-6,50,3], k = 4

Output: 12.75

Explanation:

when length is 5, maximum average value is 10.8,

when length is 6, maximum average value is 9.16667.

Thus return 12.75.


Note:

- 1 <= k <= n <= 10,000.
- Elements of the given array will be in range [-10,000, 10,000].

The answer with the calculation error less than 10-5 will be accepted.

Observations:

This is NOT a free problem, one who's interested in solving this will have to pay. That has been said, lintcode provides this as a "medium" level
problem for free:

https://www.lintcode.com/problem/maximum-average-subarray-ii/description

I actually "solved" this before and left it in the binarysearch folder. That's one and half year ago. Now, it looks like fresh to me...

Anyway, instead of doing brute force in O(N^2), there is a Nlog(MAX_IN_ARRAY, MIN_IN_ARRAY) solution. It's a BS greedy. But the really complication
is on the theory to eliminate the half:

Given m = (MAX_IN_ARRAY + MIN_IN_ARRAY) / 2.0, as the possible average of the subarray with at least k elements. If such subarray exists, one should
expect to have at least one subarray which sum is no less than m and size is no less than k. If such subarray does exists, left boundary for BS is moved to m;
Otherwise, moving right pointer to m.

In order to achieve OlogN time, the discovery of such a subarray has to be done in O(N) time. This is equivalent to:

Given index j, j >= k - 1, subarray with size at least k are: [0, j], [1, j], ..., [j - k + 1, j]. Such a subarray shall satisfy:
SUM([l, j]) / (j - l + 1) >= m;

One may try prefix sum here. For any given PrefixSum[j], j >= k - 1, if PrefixSum[t] is minimum among PrefixSum[0] to PrefixSum[j - k + 1], in which (j - t) is no less than (k - 1),
then the maximum sum at index j is known by (PrefixSum[j] - PrefixSum[t]).

In the solution, two modifications have been made:

1. Instead of calculating real prefix sum, only prefix sum on average is done. prefixSumAvgHere += nums[i] - m; Therefore,
the comparsion with m is replaced by comparing with zero. If such a maximum subarray sum is no less than zero, one could know
m is a valid average.

2. There is no need to keep all prefix sums. A two pointer (tortoise hare) approach is taken. Tortoise is always k steps away from
hare. Tortoise points to the minimum prefix sum from index 0, which is at least k steps away from hare which points to the prefix sum
ends at index j. The prefix sum is actually calcuated twice but O(N) space is saved.

Extra considerations:

- If len(nums) is 1, returns nums[0];

- Floating point number as result may returns -0.00, have to do (ans >= error ? ans : 0.0)
*/
class SolutionMaximumAverageSubarray {
public:
	/*
	* @param nums: an array with positive and negative numbers
	* @param k: an integer
	* @return: the maximum average
	*/
	double maxAverage(const vector<int> &nums, int k) {
		int min_int = numeric_limits<int>::min();
		size_t len = nums.size(), i = 0;
		double error = 1e-5, l = numeric_limits<int>::max(), r = min_int, m = 0.0, minPrefixSumAvgBehindAtLeastK = 0.0, prefixSumAvgBehindAtLeastK = 0.0, prefixSumAvgHere = 0.0, ans = min_int;
		for (int i : nums) l = std::min((int)l, i), r = std::max((int)r, i);
		while (r - l >= error) {
			m = (r + l) / 2.0, prefixSumAvgHere = minPrefixSumAvgBehindAtLeastK = prefixSumAvgBehindAtLeastK = 0.0;
			for (i = 0; i < len; ++i) {
				prefixSumAvgHere += nums[i] - m;
				if (i >= k - 1) {
					if (prefixSumAvgHere - minPrefixSumAvgBehindAtLeastK >= error) {
						ans = std::max(ans, m);
						i = len + 1;
						break;
					}
					prefixSumAvgBehindAtLeastK += nums[i - k + 1] - m;
					minPrefixSumAvgBehindAtLeastK = std::min(minPrefixSumAvgBehindAtLeastK, prefixSumAvgBehindAtLeastK);
				}
			}
			if (len + 1 == i) l = m;
			else r = m;
		}
		return 1 == len ? nums[0] : (ans >= error ? ans : 0.0);
	}
};
void TestMaximumAverageSubarray() {
	SolutionMaximumAverageSubarray so;
	so.maxAverage(vector<int> {1, 12, -5, -6, 50, 3}, 3);
}
/*
Test cases:

[-1,0,1]
3
[-2147483648,-2147483648,-2147483648,-2147483648]
2

Outputs:

0.000
0.000
*/