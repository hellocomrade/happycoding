//https://leetcode.com/problems/power-of-three/
/*
326. Power of Three

Given an integer, write a function to determine if it is a power of three.

Example 1:

Input: 27

Output: true

Example 2:

Input: 0

Output: false

Example 3:

Input: 9

Output: true

Example 4:

Input: 45

Output: false

Follow up:

Could you do it without using any loop / recursion?

Obserations:

Solving using loop/recursion is trivial. If integer is 4 bytes only, finding the largest power of 3 is
3^19 = 1162261467.

Therefore, any power of 3 in 4 bytes integer range should be dividable by 3^19. This is doable since
3 is a prime number, the only divisor of 3^19 is 3^18, 3^17, 3^16,..., 3^0, which cover all power of 3.
*/
class SolutionPowerOfThree {
public:
	bool isPowerOfThree(int n) {
		return 0 < n && 0 == 1162261467 % n;
	}
};