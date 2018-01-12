#include <cstdlib>

//https://leetcode.com/problems/powx-n/
/*
50. Pow(x, n)

Implement pow(x, n).

Observations:
n could be negative. Abs(n) then get result ans, if n < 0, do (1/ans) at the end.

Kind of Binary Search O(logN)
a^b, b = 2^0 + 2^1 + 2^2... if necessary. For example:

a^9 --> 9 in binary is 1001, a^9 = a^(2^0 + 2^3) = a^1 * a^8 = a * (a*a*a*a*a*a*a*a)

So we check the last bit of a, if it's 1, then multiply a^(2^k) onto the result, otherwise, only
increase multiplier to a^(2^k*2^k), k in [1, n]

1. Possible integer overflow on abs if INT_MIN is given;
2. 0^0 = 1, 0^k = 0 for K > 0;
3. 7.0^-4, 7.0^4;

Offical solutions:

https://leetcode.com/problems/powx-n/solution/

Wiki for Exponetiation by Squaring:

https://en.wikipedia.org/wiki/Exponentiation_by_squaring

*/
class SolutionPow {
private:
	double _aux(double x, long long n) {
		if (n < 1)return 1.0;
		double m = _aux(x, n / 2LL);
		return m * m * (1 == n % 2LL ? x : 1.0);
	}
public:
	//Iterative
	double myPow(double x, int n) {
		//Possible integer overflow if INT_MIN, abs(-2147483648)
		long long nl = std::abs((long long)n);
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
	//Recursie
	double myPow1(double x, int n) {
		double ans = this->_aux(x, std::abs(n * 1LL));
		return n < 0 ? 1.0 / ans : ans;
	}
};