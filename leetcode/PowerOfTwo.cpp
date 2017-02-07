//https://leetcode.com/problems/power-of-two/
/*
231. Power of Two

Given an integer, write a function to determine if it is a power of two.
*/
class SolutionPowerOfTwo {
public:
	bool isPowerOfTwo(int n) {
		return n > 0 && 0 == (n & (n - 1));
	}
};