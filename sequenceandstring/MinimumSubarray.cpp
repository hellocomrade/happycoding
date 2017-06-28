#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

//http://lintcode.com/en/problem/minimum-subarray
/*
Minimum Subarray

Given an array of integers, find the subarray with smallest sum.

Return the sum of the subarray.

Notice

The subarray should contain one integer at least.

Example
For [1, -1, -2, 1], return -3.
*/
class Solution {
public:
	/**
	* @param nums: a list of integers
	* @return: A integer denote the sum of minimum subarray
	*/
	int minSubArray(vector<int> nums) {
		size_t size = nums.size();
		long long minHere = 0LL, minSofar = numeric_limits<long long>::max();
		for (size_t i = 0; i < size; ++i) {
			minSofar = std::min(minSofar, minHere + nums[i]);
			minHere = std::min(0LL, minHere + nums[i]);
		}
		return static_cast<int>(minSofar);
	}
};