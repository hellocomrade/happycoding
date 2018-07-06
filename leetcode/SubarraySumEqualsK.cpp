#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

//https://leetcode.com/problems/subarray-sum-equals-k
/*
560. Subarray Sum Equals K

Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:

Input:nums = [1,1,1], k = 2

Output: 2

Note:
- The length of the array is in range [1, 20,000].
- The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

Observations:

This is related to 2Sum (leetcode 1), but apply on prefix sum/partial sum. With such a partial sum array: psum, the problem is
translated to 2Sum: finding 2 elements in psum, who's sum is k.

Given an array: [0,0,0,0,0,0,0,0,0,0] and k = 0, the result is 55.
*/
class SolutionSubarraySumEqualsK {
public:
	int subarraySum(vector<int>& nums, int k) {
		int ans = 0, psum = 0;
		unordered_map<int, int> memo;
		++memo[0];
		for (int i : nums) {
			psum += i;
			if (0 < memo.count(psum - k)) ans += memo[psum - k];
			++memo[psum];
		}
		return ans;
	}
	int subarraySum0(vector<int>& nums, int k) {
		int ans = 0;
		std::partial_sum(nums.begin(), nums.end(), nums.begin());
		unordered_map<int, int> memo;
		++memo[0];
		for (int i : nums) {
			if (0 < memo.count(i - k)) ans += memo[i - k];
			++memo[i];
		}
		return ans;
	}
};