#include <cassert>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

//https://leetcode.com/problems/maximum-product-subarray/
/*
152. Maximum Product Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

Observations:
I saw this one under DP category. Didn't look like DP to me. Well, then I noticed that we probably need to track/memorize couple variables,
but still hard to qualify a DP in my opinion.

Comparing with the famous/classic max subarray (addtion version), this one is about multiplication. We will have to deal with positve, negative and zero.
A really small negative number from previous product could jump to a really big one if the next operator is a negative and vice versa. Zero, on the other hand,
should be considered as a stopper since we only alow contiguous subarray product.

I made the naive version (maxProduct1), which keep tracking the max positive and min negative. Note, these two can be swapped if the next operator is a negative.
We reset everything if we meet a zero. There are couple edge cases we have to cover in order to pass all test cases. Leetcode did a pretty good job to set edge cases up.

After a glance at "top solutions", I realize that we can mimic the look from classic max subarray. Still the same idea from the description above, but sounds more DP:

We only need to memorize two variables: max_at_last_pos, min_at_last_pos

The new max at current position is the maximum among (nums[i] * max_at_last_pos), (nums[i] * min_at_last_pos), or nums[i]
The new min at current position is the minimum among (nums[i] * max_at_last_pos), (nums[i] * min_at_last_pos), or nums[i]

Then we take maxsofar from max(maxsofar, max_at_current_pos)
*/
class SolutionMaxProductSubarray {
public:
	/**
	* @param nums: a vector of integers
	* @return: an integer
	*/
	/*
	Second version
	*/
	int maxProduct(const vector<int>& nums) {
		size_t len = nums.size();
		if (len < 1)return 0;
		long long minhere = nums[0], maxhere = nums[0], oldmaxhere, maxsofar = nums[0];
		for (size_t i = 1; i < len; ++i) {
			oldmaxhere = maxhere;
			maxhere = std::max(std::max(nums[i] * maxhere, nums[i] * minhere), nums[i] * 1LL);
			minhere = std::min(std::min(nums[i] * minhere, nums[i] * oldmaxhere), nums[i] * 1LL);
			maxsofar = std::max(maxsofar, maxhere);
		}
		return maxsofar;
	}
	/*
	First version. There are lots of edges I have to cover, which made the code messy
	*/
	int maxProduct1(const vector<int>& nums) {
		size_t len = nums.size();
		if (len < 1)return 0;
		long long pinfinit = numeric_limits<long long>::min();
		long long ans = nums[0], positive = pinfinit, negative = 1, tmp;
		for (size_t i = 0; i < len; ++i) {
			if (nums[i] > 0) {
				positive = pinfinit == positive ? nums[i] : positive * nums[i];
				negative *= nums[i];
			}
			else {
				if (0 == nums[i]) {
					//in case positive is never assigned, need to compare with zero as well
					ans = std::max(0LL, std::max(positive, ans));
					positive = pinfinit;
					negative = 1;
				}
				else {
					negative = negative > 0 ? nums[i] : negative * nums[i];
					ans = std::max(ans, std::max(positive, negative));
					tmp = pinfinit == positive ? 1 : positive;
					positive = negative > 0 ? negative : pinfinit;
					negative = negative > 0 ? tmp * nums[i] : tmp * negative;
				}
			}
		}
		//in case negative is never assigned, which makes it 1, need to reset it to zero
		return static_cast<int>(std::max(ans, std::max(positive, negative == 1 ? 0 : negative)));
	}
};
void TestMaxProductSubarray() {
	SolutionMaxProductSubarray so;
	assert(-2 == so.maxProduct(vector<int>{-2}));
	assert(6 == so.maxProduct(vector<int>{2, 3, -2, 4}));
	assert(48 == so.maxProduct(vector<int>{-2, -3, -2, -4}));
	assert(48600 == so.maxProduct(vector<int>{-3, -1, 3, 5, -6, -6, -1, 6, -3, -5, 1, 0}));
	assert(48600 == so.maxProduct(vector<int>{-3, -1, 3, 5, -6, -6, -1, 6, -3, -5, 1, 0, -6, -5, 0, -2, 6, 1, 0, 5}));
	assert(60 == so.maxProduct(vector<int>{2, 3, -5, -2}));
	assert(60 == so.maxProduct(vector<int>{1, 0, -1, 2, 3, -5, -2}));
	assert(0 == so.maxProduct(vector<int>{0}));
	assert(0 == so.maxProduct(vector<int>{-2, 0, -1}));
}