#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

//https://www.lintcode.com/problem/maximum-subarray-difference
/*
45. Maximum Subarray Difference

Description

Given an array with integers.

Find two non-overlapping subarrays A and B, which |SUM(A) - SUM(B)| is the largest.

Return the largest difference.

The subarray should contain at least one number

Example

Example 1:

Input:[1, 2, -3, 1]

Output:6

Explanation:

The subarray are [1,2] and [-3].So the answer is 6.

Example 2:

Input:[0,-1]

Output:1

Explanation:

The subarray are [0] and [-1].So the answer is 1.

Challenge

O(n) time and O(n) space.

Observations:

This is a variation of lintcode 42 (Maximum Subarray II):

https://github.com/hellocomrade/happycoding/blob/master/dynamicprogramming/MaximumSubarray2.cpp

And the rationale is based upon the classic Maximum Subarray:

https://github.com/hellocomrade/happycoding/blob/master/leetcode/MaxSubArray.cpp

Two conditions:

1. Any subarray shall contain at least 1 element;
2. No overlap;

Also, the inferences are:

1. One subarray has the max sum, one subarray has the min sum;
2. Max and min can be picked from either side of the given array;

If we are given 4 arrays, memo1, memo2, memo3, and memo4 to track:

memo1[i]: largest subarray sum at index i if nums is looped from left;
memo2[i]: smallest subarray sum at index i if nums is looped from left;
memo3[j]: largest subarray sum at index j if nums is looped from right;
memo4[j]: smallest subarray sum at index j if nums is looped from right;

Then find MAX(MAX(memo1[i] - memo4[i + 1]) , MAX(memo3[i] - memo2[i + 1]));

In fact, only memo1 is needed. Values in memo4 and memo2 are not necessarily stored. They can
be calculated on the fly and substracted by memo1[i - 1] on the fly.

How about memo3? Well, we could reuse memo1 by reversing the nums and re-calculate subarray sum at i
in memo1.
*/
class SolutionMaximumSubarrayDifference {
public:
	/**
	 * @param nums: A list of integers
	 * @return: An integer indicate the value of maximum difference between two substrings
	 */
	int maxDiffSubArrays(vector<int> &nums) {
		int len = (int)nums.size();
		if (0 == len) return 0;
		long long ans = numeric_limits<long long>::min();
		vector<long long> vec1(len, 0LL);
		function<void()> mSubSumOnNums = [&]() {
			long long maxHere = 0;
			for (int i = 0; i < len; ++i) {
				maxHere = std::max(maxHere + nums[i], nums[i] + 0LL);
				vec1[i] = std::max((0 == i ? nums[i] : vec1[i - 1]), maxHere);
			}
		};
		function<void()> getMax = [&]() {
			long long maxSofar = 0, maxHere = 0;
			for (int i = len - 1; i > 0; --i) {
				maxHere = std::max(maxHere - nums[i], nums[i] * -1LL);
				maxSofar = std::max((len - 1 == i ? nums[i] * -1LL : maxSofar), maxHere);
				ans = std::max(ans, vec1[i - 1] + maxSofar);
			}
		};
		mSubSumOnNums(), getMax();
		std::reverse(nums.begin(), nums.end());
		mSubSumOnNums(), getMax();
		return static_cast<int>(ans);
	}
};
void TestMaximumSubarrayDifference() {
	SolutionMaximumSubarrayDifference so;
	vector<int> vec1 = { 1, 2, -3, 1 };
	assert(6 == so.maxDiffSubArrays(vec1));
	vector<int> vec2 = { 1, 1, 1, 1 };
	assert(2 == so.maxDiffSubArrays(vec2));
}