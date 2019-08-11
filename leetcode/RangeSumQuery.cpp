#include <vector>

using namespace std;

//https://leetcode.com/problems/range-sum-query-immutable/
/*
303. Range Sum Query - Immutable

Given an integer array nums, find the sum of the elements between indices i and j (i <= j), inclusive.

Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1

sumRange(2, 5) -> -1

sumRange(0, 5) -> -3

Note:

- You may assume that the array does not change.
- There are many calls to sumRange function.

Observations:

Straightforward for Prefix Sum. Didn't consider integer overflow...
*/
namespace RangeSumQuery {
	class NumArray {
	private:
		vector<int> prefixSum;
		int len;
	public:
		NumArray(vector<int>& nums) : prefixSum(nums.size() + 1, 0) {
			this->len = (int)nums.size();
			for (int i = 0; i < this->len; ++i)
				this->prefixSum[i + 1] = nums[i] + prefixSum[i];
		}

		int sumRange(int i, int j) {
			if (0 > i || 0 > j || i >= this->len || j >= this->len) return -1;
			return this->prefixSum[j + 1] - this->prefixSum[i];
		}
	};
}
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
 /*
 Test cases:

 ["NumArray","sumRange","sumRange","sumRange"]
 [[[-2,0,3,-5,2,-1]],[0,2],[2,5],[0,5]]
 ["NumArray","sumRange"]
 [[[0]],[0,0]]
 ["NumArray","sumRange","sumRange","sumRange"]
 [[[-1,1]],[0,0],[1,1],[0,1]]

 Outputs:

 [null,1,-1,-3]
 [null,0]
 [null,-1,1,0]
 */