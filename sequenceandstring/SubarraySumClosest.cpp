#include <vector>
#include <algorithm>

using namespace std;

//https://lintcode.com/problem/subarray-sum-closest/description
/*
139. Subarray Sum Closest

Description
Given an integer array, find a subarray with sum closest to zero. Return the indexes of the first number and last number.

Example

Given [-3, 1, 1, -3, 5], return [0, 2], [1, 3], [1, 1], [2, 2] or [0, 4].

Challenge

O(nlogn) time

Observations:

I am not sure if an O(N) solution exists. When one saw O(NlogN), BS might be on the top of the list coz another obvious method in
this time complexity doesn't seem to apply: sorting.

If one can take a second look, since subarray sum is mentioned, prefix sum array will be the first choice. It's not usual as well to
sort on prefix sum array. But for this case, it works perfectly: by sorting prefix sum array, one can examine:

- Individual element at index i, which represents the subarray in range of [0, i];

- Substraction of any two neighbor elemetns at index i and j, which represents the subbary in range of [min(i, j) + 1, max(i, j)];

The smallest diff is picked and the indexes shall be kept.

Edge cases are:

- abs() on INT_MIN, therefore long long is needed;

- Possible addition and substraction between INT_MIN and INT_MAX, therefore long long is needed;
*/
class SolutionSubarraySumClosest {
public:
	/*
	* @param nums: A list of integers
	* @return: A list of integers includes the index of the first number and the index of the last number
	*/
	vector<int> subarraySumClosest(vector<int> &nums) {
		size_t len = nums.size();
		vector<int> ans(2, 0);
		if (len < 1) return ans;
		long long diff;
		vector<std::pair<long long, int> > prefixSum(len);
		prefixSum[0].first = nums[0], prefixSum[0].second = 0;
		for (size_t i = 1; i < len; ++i) {
			prefixSum[i].first = prefixSum[i - 1].first + 1LL * nums[i];
			prefixSum[i].second = i;
		}
		std::sort(prefixSum.begin(), prefixSum.end());
		diff = std::abs(1LL * prefixSum[0].first);
		ans[0] = 0;
		ans[1] = prefixSum[0].second;
		for (size_t i = 1; i < len; ++i) {
			if (diff > std::abs(1LL * prefixSum[i].first)) {
				diff = std::abs(1LL * prefixSum[i].first);
				ans[0] = 0;
				ans[1] = prefixSum[i].second;
			}
			if (diff > std::abs(1LL * prefixSum[i].first - 1LL * prefixSum[i - 1].first)) {
				diff = std::abs(1LL * prefixSum[i].first - 1LL * prefixSum[i - 1].first);
				ans[0] = std::min(prefixSum[i].second, prefixSum[i - 1].second) + 1;
				ans[1] = std::max(prefixSum[i].second, prefixSum[i - 1].second);
			}
		}
		return ans;
	}
};