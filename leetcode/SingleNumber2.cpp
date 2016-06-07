#include <vector>

using namespace std;

//https://leetcode.com/problems/single-number-ii/
/*
137. Single Number II

Given an array of integers, every element appears three times except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Observation:
If we want the final result to reveal the single number, We need to figure out a way to let bit flip from 0 to 0 in 3 times.
Two bits are used here since we are talking about counting in binary. A single bit can only represent 0 and 1, which are two states. Now,
we need three states 0 - 1 - 0.

For example, both bit1 and bit2 are set to 0 at first. At position k, number i has 1 set, so

00

bit1 = (0 ^ 1) & (~0) = 1;
bit2 = (0 ^ 1) & (~1) = 0;

01

The second number happens to be i again,
bit1 = (1 ^ 1) & (~0) = 0;
bit2 = (0 ^ 1) & (~0) = 1;

10

The third number happens to be i again,
bit1 = (0 ^ 1) & (~1) = 0;
bit2 = (1 ^ 1) & (~0) = 0;

00
We come back to 00 from 00 -> 01 -> 10. The single number will be stored in the integer bit1
*/
class SolutionNumber2 {
public:
	//Slower, 32O(N), but it's an easy to understand one
	int singleNumber1(vector<int>& nums) {
		int bit1 = 0, bit2 = 0;
		unsigned int mask = 1 << 31;
		int cnt = 0, ans = 0;
		while (mask)
		{
			cnt = 0;
			for (int i : nums)
				if ((mask & i) != 0)++cnt;
			if (cnt % 3 != 0)
				ans |= mask;
			mask >>= 1;
		}
		return ans;
	}
	//faster, use two bits as sginal lights
	int singleNumber(vector<int>& nums) {
		int bit1 = 0, bit2 = 0;
		for (int i : nums)
		{
			bit1 = (bit1 ^ i) & ~bit2;
			bit2 = (bit2 ^ i) & ~bit1;
		}
		return bit1;
	}
};