#include <vector>
#include <numeric>
#include <functional>

using namespace std;

//https://leetcode.com/problems/single-number-iii/
/*
260. Single Number III

Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

Example:

Input:  [1,2,1,3,2,5]

Output: [3,5]

Note:
- The order of the result is not important. So in the above example, [5, 3] is also correct.
- Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

Observations:

I didn't work this out myself. I was stuck on the fact that XOR result is a ^ b given a, b as the two
single numbers. I had hard time to figure out the way to split them...

So the idea is: since a and b are different, it's "obvious" to tell there is at least 1 bit that a is
set by 1 and b is set by 0 or vice versa. If such a 1 bit, B can be found on a ^ b, we could run XOR again on
the given array. Based upon B, all numbers can be categorized in two groups: 1. B bit is not 0; 2. B bit is 0;

The other numbers that appear twice will again NOT have any effect on XOR operation here even in this
group mode coz the numbers with B set will fall into one group and vice versa.

Theoretically, as for B, any set bit (bit with 1) is sufficient. However, it appears the rightmost set bit
is a low hanging fruit. Given xor as the result of the first round XOR:

xor = std::accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());

xor &= -xor
OR
xor = (xor & (xor - 1)) ^ xor;

Either will find the rightmost 1 bit.
*/
class SolutionSingleNumber3 {
public:
	vector<int> singleNumber(vector<int>& nums) {
		//int acc = std::accumulate (flags, std::end(flags), 0, std::bit_xor<int>());
		vector<int> ans(2, 0);
		int rmbit = 0;
		//xor = std::accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
		//xor = (xor & (xor - 1)) ^ xor;
		rmbit = std::accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
		rmbit &= -rmbit;
		for (int i : nums)
			if (0 != (rmbit & i)) ans[0] ^= i;
			else ans[1] ^= i;
		return ans;
	}
};