//https://leetcode.com/problems/sum-of-two-integers/
/*
371. Sum of Two Integers

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3.

Observations:

I am not sure why leetcode categorizes this as EASY. I envy anyone who could figure this out in about 15 minutes if
you never took class like Computer Architect etc. and happened to hear and remember half-adder:

https://en.wikipedia.org/wiki/Adder_%28electronics%29#Half_adder

Here is a pretty good explanation:

https://www.geeksforgeeks.org/add-two-numbers-without-using-arithmetic-operators/

Bitwise XOR can sum two bits and bitwise AND can get the carry. If we extend this trick on two bit sequences,
XOR gives us all bits at positions with 1-0 pairs, say A in the sequences and AND gives all 1-1 pairs, say B, which are carries.

Then we left shift B by 1 and use that as the operator for the next addition with A. This ends if B is 0, which means there is
no carry anymore and the final result is in A.
*/
class SolutionSumOfTwoIntegers {
public:
	int getSum(int a, int b) {
		int t = 0;
		while (0 != b) {
			t = a;
			a = a ^ b;
			b = (t & b) << 1;
		}
		return a;
	}
	int getSum1(int a, int b) {
		if (0 == b) return a;
		return getSum1(a ^ b, (a & b) << 1);
	}
};