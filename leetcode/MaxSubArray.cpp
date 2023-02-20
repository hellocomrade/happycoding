#include <vector>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

//https://leetcode.com/problems/maximum-subarray/
/*
53. Maximum Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.
click to show more practice.
More practice:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
Observations:
So classic, have done multiple times here and there. But once for a while, I could easily forget the subtle details and take more than 15
minutes to get this done, which is a shame...

Update on 2023-02-20

It has been a while...anyway, added divide-and-conquer version of max-sub-array. Given a 2-element-array, [a, b], if using divide-and-conquer,
the max-sub-array, shall come from any of the following 3:

1. [a]
2. [b]
3. [a + b]

In other words, the sub-max coming from either left side or right side, or cross the boundary, in this case, it's (a + b).

The first 2 cases can be covered intutively by divide-and-conquer, the third case, which is the max-sum of a sub sequence that guarantees covering the middle point,
however, it's straightforward to calculate as well: starting from the middle point, scan toward left and get the max-sum in the range of [left, mid], scan toward right
and get the amx-sum in the range of [mid, right]. Adding them togather gets the third case.
*/
class SolutionMaximumSubArray {
public:
	int maxSubArray(vector<int>& nums) {
		size_t len = nums.size();
		long long ans = numeric_limits<long long>::min(), prevContri2Max = 0;
		for (int i : nums) {
			ans = std::max(ans, prevContri2Max + i);
			prevContri2Max = std::max(0LL, prevContri2Max + i);
		}
		return 0 == len ? 0 : static_cast<int>(ans);
	}
	int maxSubArray0(vector<int>& nums) {
		size_t len = nums.size();
		long long maxSofar = numeric_limits<int>::min(), maxEndingHere = 0;
		for (int i : nums) {
			maxEndingHere = std::max((long long)i, maxEndingHere + i);
			maxSofar = std::max(maxSofar, maxEndingHere);
		}
		return 0 == len ? 0 : static_cast<int>(maxSofar);
	}
	int maxSubArray_divide_conquer(vector<int>& nums) {
		std::function<long long(int, int)> _maxSubArray = [&](int l, int r) -> long long {
			if (l > r)
				return numeric_limits<long long>::min();
			if (l == r)
				return nums[l];
			int m = l + (r - l) / 2;
			long long sum = 0LL;
			long long lmax = numeric_limits<long long>::min();
			long long rmax = numeric_limits<long long>::min();
			for (int i = m; i >= l; --i) {
				sum += nums[i];
				lmax = std::max(lmax, sum);
			}
			sum = 0LL;
			for (int i = m + 1; i <= r; ++i) {
				sum += nums[i];
				rmax = std::max(rmax, sum);
			}
			return std::max(lmax + rmax, std::max(_maxSubArray(l, m), _maxSubArray(m + 1, r)));
		};
		return (int)_maxSubArray(0, nums.size() - 1);
	}
};