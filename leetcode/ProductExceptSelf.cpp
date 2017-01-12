#include <vector>

using namespace std;

//https://leetcode.com/problems/product-of-array-except-self/
/*
238. Product of Array Except Self

Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)

Observations:
Division is not allowed is the key. Then, O(1) space, however giving the hint that output array doesn't count as extra.

So, it actually allows us to use output array for extra space...

Basic idea is: we get the accumulated prodcuts from left to right and keep the result in output array; Then, go backward and store the result in input array.
Given such arrays left2right and right2left and index i, output[i] = left2right[i - 1] * right2left[i + 1].

This is the same idea like prefix sum array...

Couple complications:
1. When we collect the final results, if left2right is using output array, the scanning should be done backward to avoid overwriting on intermidate results that is still necessary to keep for further product;
2. Edge case output[0] = output[1] or output[len - 1] = output[len - 2], depending on output is right2left or left2right.
3. Edge case ouput[len - 1] = input[len - 2] or output[0] = input[1], depending on output is right2left or left2right.
4. An extra temp variable may be applied to store the intermidate result, however, this won't improve any performance, since you will have to have 2 assignment in the second loop.

*/
class SolutionProductExceptSelf {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		int len = (int)nums.size();
		vector<int> ans = nums;
		for (int i = 1; i < len; ++i)nums[i] *= nums[i - 1];
		for (int i = len - 2; i > -1; --i)ans[i] *= ans[i + 1];
		ans[0] = ans[1];
		for (int i = 1; i < len - 1; ++i)
			ans[i] = nums[i - 1] * ans[i + 1];
		ans[len - 1] = nums[len - 2];
		return ans;
	}
	vector<int> productExceptSelf1(vector<int>& nums) {
		int len = nums.size();
		vector<int> ans(nums);
		int postfixMulti = nums[len - 1];
		for (int i = 1; i < len; ++i)ans[i] *= ans[i - 1];
		ans[len - 1] = ans[len - 2];
		for (int i = len - 2; i > 0; --i)
		{
			ans[i] = postfixMulti * ans[i - 1];
			postfixMulti *= nums[i];
		}
		ans[0] = postfixMulti;
		return ans;
	}
};