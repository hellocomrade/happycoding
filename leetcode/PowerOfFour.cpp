//https://leetcode.com/problems/power-of-four/
/*
342. Power of Four

Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example 1:

Input: 16

Output: true

Example 2:


Input: 5

Output: false

Follow up: Could you solve it without loops/recursion?

Observations:

This is a follow-up on leetcode 326 (Power Of Three). The naive solution can achieve constant time:

First check if 0 == n & (n - 1) to decide if n is a power of 2;

If yes, check the tailing zero on n in binary. For example: 10000 is power of 4, but 1000 is not.
Therefore even number of tailing zero leads to a power of 4.

If no loops/recursions are allowed:

- First method would be using bitwise mask.

Power of 4 no more than 16 are:

00001
00100
10000

OR them together:

mask = 10101

If we OR any power of 4 no more than 16 on this mask, the result is mask itself.

Apply this on 32 bits integer, mask = 01010101010101010101010101010101, aka 0x55555555


- Second method requires more in-depth observation:

It can be proved that given any power of 4, N, 1 == N % 3
*/
class SolutionPowerOfFour {
public:
	bool isPowerOfFour(int num) {
		return 0 < num && 0 == (num & (num - 1)) && 0 != (0x55555555 & num);
	}
	bool isPowerOfFour0(int num) {
		return 0 < num && 0 == (num & (num - 1)) && 0 != (num & 0b01010101010101010101010101010101);
	}
	bool isPowerOfFour1(int num) {
		return 0 < num && 0 == (num & (num - 1)) && 1 == num % 3;
	}
};