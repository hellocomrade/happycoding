#include <algorithm>

//https://leetcode.com/problems/powx-n/
/*
50. Pow(x, n)

Implement pow(x, n).

Observations:
Kind of Binary Search O(logN)
a^b, b = 2^0 + 2^1 + 2^2... if necessary. For example:

a^9 --> 9 in binary is 1001, a^9 = a^(2^0 + 2^3) = a^1 * a^8 = a * (a*a*a*a*a*a*a*a)

So we check the last bit of a, if it's 1, then multiply a^(2^k) onto the result, otherwise, only
increase multiplier to 2^k*2^k

1. Possible integer overflow on abs if INT_MIN is given;
2. 0^0 = 1, 0^k = 0 for K > 0;
3. 7.0^-4, 7.0^4;
*/
class SolutionPow {
public:
	double myPow(double x, int n) {
		long nl = std::abs((long long)n);
		double ret = 1;
		double cnt = x;
		while (nl > 0)
		{
			if (nl & 1LL)
				ret *= cnt;
			nl >>= 1;
			cnt *= cnt;
		}
		return n >= 0 ? ret : 1 / ret;
	}
};