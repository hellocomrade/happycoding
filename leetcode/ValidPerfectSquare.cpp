//https://leetcode.com/problems/valid-perfect-square/
/*
367. Valid Perfect Square

Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Returns: True
Example 2:

Input: 14
Returns: False

Observation:
Oops, first submit forgot m*m could overflow if m is int...
*/
class SolutionValidPerfectSquare {
public:
	bool isPerfectSquare(int num) {
		if (1 == num)return 1;
		long long h = num / 2, l = 1LL, m = 0LL;
		while (l <= h) {
			m = l + (h - l) / 2;
			if (num == m * m)return true;
			else if (num > m * m) l = m + 1;
			else h = m - 1;
		}
		return false;
	}
};