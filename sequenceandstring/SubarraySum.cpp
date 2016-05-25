#include <unordered_map>
#include <vector>

using namespace std;

//http://www.lintcode.com/en/problem/subarray-sum/
/*
Subarray Sum

Given an integer array, find a subarray where the sum of numbers is zero. Your code should return the index of the first number and the index of the last number.

Notice

There is at least one subarray that it's sum equals to zero.

Example
Given [-3, 1, 2, -3, 4], return [0, 2] or [1, 3].

Observation:
This can be done in O(N) with O(N) space.
We first calcuate prefix sum and then we can find that a subarray's sum is zero as long as two elements in
prefix sum array are equal. Say if prefixSum[i] is equal to prefixSum[j], j > i, the sub array is from i - 1 to j.

In order to maintain O(N) time complexity, we will need to find out which two are equal in O(1).
This can be achieved using hashtable. The key is the prefix sum, and the value is the index.
We then scan prefixSum array from left to right, we will check if the prefixSum at index j is already on
hashtable, if it does, we retrieve the index i on hashtable using prefixSum[j] as the key, then we have both index.

Otherwise, we put (prefixSum[j], j) on hashtable.
*/
class SolutionSubarraySum {
public:
	/**
	* @param nums: A list of integers
	* @return: A list of integers includes the index of the first number
	*          and the index of the last number
	*/
	vector<int> subarraySum(vector<int> nums){
		// write your code here
		vector<int> ret(2, 0);
		int len = nums.size();
		unordered_map<int, int> map;
		map.emplace(nums[0], 0);
		for (int i = 1; i < len; ++i)
		{
			nums[i] += nums[i - 1];
			if (nums[i] == 0)
			{
				ret[1] = i;
				return ret;
			}
			if (map.find(nums[i]) != map.end())
			{
				ret[0] = map[nums[i]] + 1;
				ret[1] = i;
				return ret;
			}
			map.emplace(nums[i], i);
		}
		return ret;
	}
};