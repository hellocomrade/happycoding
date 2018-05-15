//https://leetcode.com/problems/add-digits
/*
258. Add Digits

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

Example:

Input: 38

Output: 2

Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.

Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?

Observations:

Naive approach will run for O(N) time by actually calculating the digits. More efficient O(1) algorithm exists if you know the
concept of "Digit Root" or you are really smart...

https://en.wikipedia.org/wiki/Digital_root

0	if n = 0
dr(n) = 9	if n != 0 and n mod 9 = 0
n mod 9

Or

dr(n) = 1 + ((n - 1) mod 9)

The second formula works for all integers, positive, negative or zero.
*/
class SolutionAddDigits {
public:
	//Digit Root O(1)
	int addDigits(int num) {
		return 1 + (num - 1) % 9;
	}
	//Naive O(N)
	int addDigits1(int num) {
		int ans = num;
		while (ans > 9) {
			num = ans, ans = 0;
			while (num > 0) {
				ans += num % 10;
				num /= 10;
			}

		}
		return ans;
	}
};