//https://leetcode.com/problems/sqrtx/
/*
69. Sqrt(x)

Implement int sqrt(int x).

Compute and return the square root of x.

Observations:
Binary search

It's a good guess to set up upper boundary to x / 2, as long as x > 1. This will cut search range to half.

Potential integer overflow, if you do m * m <= x, therefore replace it with x / m >= m. Otherwise, both
x and m have to be long long.
*/
class SolutionSqrt {
public:
	int mySqrt(int x) {
		if (x <= 0)return 0;
		if (x == 1)return 1;
		int l = 1, h = x / 2, m = 0, ans = 0;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (x / m >= m)
			{
				l = m + 1;
				ans = m;
			}
			else
				h = m - 1;
		}
		return ans;
	}
};