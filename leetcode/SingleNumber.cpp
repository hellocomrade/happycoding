#include <vector>

using namespace std;

//https://leetcode.com/problems/single-number/
/*
136. Single Number

iven an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
class SolutionSingleNumber {
public:
	int singleNumber(vector<int>& nums) {
		int ret = 0;
		for (int i : nums)
			ret ^= i;
		return ret;
	}
};