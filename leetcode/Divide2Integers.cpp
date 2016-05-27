#include <limits>
#include <iostream>
using namespace std;

//https://leetcode.com/problems/divide-two-integers/
/*
29. Divide Two Integers

Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

Observation:
Linear solution by substraction is not allowed. So basic idea is binary search.

The first version is a bit slow coz I thought since multiplication/division is not allowed, bitwise shift should not be allowed
as well. But, can't get around it on the variable f. Therefore, when divisor is larger than dividend, I have
to reset divisor to its original value, which degrade the performance of BS...

The second version, since bitwise shift is allowed, we could do *2 and /2. It's fast to process dividor now.

However, the real challenge here is for integer overflow.

-2147483648 / 1 is OK, but -2147483648 / - 1 will cause overflow

Same for abs, which I always falls in the same river: abs(-2147483648) will cause overflow if assigned to int.

*/
class SolutionDivide2Integers {
public:
	int divide1(int dividend, int divisor) {
		if (0 == divisor)return numeric_limits<int>::max();
		else if (0 == dividend)return 0;
		bool neg = (dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0);
		long long dividendL = abs((long long)dividend), divisorL = abs((long long)divisor);
		if (dividendL < divisorL)return 0;
		long long dv = divisorL, prevdv = numeric_limits<long long>::max(), lastdv = 0, f = 1, cnt = 0;
		while (dv <= prevdv && dv >= divisorL)
		{
			if (dividendL - dv >= 0)
			{
				cnt += f;
				f <<= 1;
				if (dividendL == dv)
					break;
				else
					dividendL -= dv;
				lastdv = dv;
				dv += dv;
			}
			else
			{
				prevdv = dv - lastdv;
				dv = divisorL;
				f = 1;
			}
		}
		if (neg)
			return cnt > numeric_limits<int>::max() + 1LL ? numeric_limits<int>::min() : cnt * (neg ? -1 : 1);
		else
			return cnt > numeric_limits<int>::max() ? numeric_limits<int>::max() : cnt;
	}
	int divide(int dividend, int divisor) {
		if (0 == dividend)return 0;
		else if (0 == divisor)return numeric_limits<int>::max();
		bool neg = (dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0);
		long long dividendL = abs((long long)dividend), divisorL = abs((long long)divisor);
		long long dv = divisorL, f = 1, cnt = 0;
		while (dv >= divisorL) // exit condition: dv should be always greater than the original divisor
		{
			if (dividendL - dv >= 0)
			{
				cnt += f;
				f <<= 1;
				if (dividendL == dv)
					break;
				else
					dividendL -= dv;
				dv <<= 1;
			}
			else
			{
				dv >>= 1;
				f >>= 1;
			}
		}
		if (neg)
			return cnt * -1;
		else
			return cnt > numeric_limits<int>::max() ? numeric_limits<int>::max() : cnt;
	}
};
void TestDivide2Integers()
{
	SolutionDivide2Integers so;
	cout << "Expect 2: " << so.divide(6, 3) << endl;
	cout << "Expect 0: " << so.divide(1004958205, -2137325331) << endl;
	cout << "Expect 1: " << so.divide(1, 1) << endl;
	cout << "Expect 0: " << so.divide(1, 2) << endl;
	cout << "Expect 4: " << so.divide(9, 2) << endl;
	cout << "Expect 2: " << so.divide(11, 4) << endl;
	cout << "Expect 16: " << so.divide(33, 2) << endl;
	cout << "Expect 2147483647: " << so.divide(numeric_limits<int>::min(), -1) << endl;
	cout << "Expect -2147483648: " << so.divide(numeric_limits<int>::min(), 1) << endl;
}