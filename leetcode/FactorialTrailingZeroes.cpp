//https://leetcode.com/problems/factorial-trailing-zeroes/
/*
172. Factorial Trailing Zeroes

Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.

Observations:

For any given integer (let's assume it's non-negative for now) N, tailing zero as a result of multiplication,
involves prime multipliers 2 and 5. So, we are actually looking for the number of paris of 2 and 5. In fact, if
you can find K 5s, there will be at least K 2s. I don't have a solid mathematical prove, but it's very intuitive to me.

Therefore, the question is transferred to: how many 5s in the sequence of multipliers of N, N - 1, N - 2, 1?

Take an example 15, 15 X 14 X...X 10 X...X 8 X...X 5 X...X 2 X 1. We have 15, 10, 5, all three of them have a 5, total 3 5s.

It appears we can simply do 15 / 5 = 3, see how many 5s in the given integer?

How about N = 25? We will have 25, 20, 15, 10, 5, total 5 numbers with 5s but 25! has 6 tailing zeros! Why? 25 contains 2 5s actually.

So, the above assumption of doing N / 5 is not sufficient, we actually have to examine given N with all 5's multiples as long as
they are smaller than N.

It seems we have an algorithm running in logarithmic time? But leetcode's sloppy description and testing code bring the extra:

What's if N is not positive? By running through leetcode testing code, N = -49 and output is -10, which is silly... It's a flaw in testing code.

However, we have to mimic it since it's the judge. In fact, if we have to correctly handle negative integer, we will have to pay attention
on the integer overflow trap on ABS if –2147483648 is given.

Even we only consider non-negative integer, if the implementation is not recursive, 5's multiples could overflow if a really large integer
is given, such as 2147483647. Therefore, have to use long integer instead.
*/
class SolutionFactorialTrailingZeroes {
public:
	int trailingZeroes(int n) {
		int ans = 0;
		long base = 5L;
		while (0 != n / base) {
			ans += (int)(n / base);
			base *= 5L;
		}
		return ans;
	}
	int trailingZeroes1(int n) {
		if (0 == n / 5) return 0;
		return n / 5 + trailingZeroes(n / 5);
	}
};
/*
Test cases:
0
15
27
310
-49
-51
51
–2147483648
2147483647

Outputs:
0
3
6
76
-10
-12
12
0
536870902
*/