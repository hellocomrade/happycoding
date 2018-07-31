#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

//https://lintcode.com/problem/maximum-subarray-ii/description
/*
42. Maximum Subarray II

Given an array of integers, find two non-overlapping subarrays which have the largest sum.
The number in each subarray should be contiguous.
Return the largest sum.

The subarray should contain at least one number

Example

For given [1, 3, -1, 2, -1, 2], the two subarrays are [1, 3] and [2, -1, 2] or [1, 3, -1, 2] and [2], they both have the largest sum 7.

Challenge
Can you do it in time complexity O(n) ?

Observations:

This is a good invention from lintcode. The problem can be translated to:

- Since no overlap is allowed and each subarray has to have at least 1 element, given i as index in nums,
one can have the largest sum at i: MAX(max_sum(0, i) + max_sum(i + 1, len(nums) - 1), max_sum(0, i - 1) + max_sum(i, len(nums) - 1));

- The largest sum from [0, len(nums) - 1] is the final answer;

- This can be done using the approach from maximum subarray and two pointers: run maximum subarray sum at i from 0 to len(num) - 2 as sum1,
then do it again reversely from len(num) - 1 to 1 as sum2. The max sum at index i is sum1[i] + sum2[len - i - 1];

- sum2 can be saved since one can get the largest sum while the second max subarray sum is going;
*/
class SolutionMaximumSubarray2 {
public:
	/*
	* @param nums: A list of integers
	* @return: An integer denotes the sum of max two non-overlapping subarrays
	*/
	int maxTwoSubArrays(vector<int> &nums) {
		size_t len = nums.size();
		if (len < 2) return 0 == len ? 0 : numeric_limits<int>::min();
		long long infinite = numeric_limits<long long>::min(), sum = 0LL, ans = infinite, rsum;
		vector<long long> sum1(len - 1, infinite);
		for (int i = 0; i < len - 1; ++i) {
			sum1[i] = std::max(0 == i ? 1LL * nums[i] : sum1[i - 1], sum + nums[i]);
			sum = std::max(0LL, sum + nums[i]);
		}
		sum = 0LL;
		for (int i = len - 1; i > 0; --i) {
			rsum = std::max(len - 1 == i ? 1LL * nums[i] : rsum, sum + nums[i]);
			sum = std::max(0LL, sum + nums[i]);
			ans = std::max(ans, sum1[i - 1] + rsum);
		}
		return static_cast<int>(ans);
	}
};