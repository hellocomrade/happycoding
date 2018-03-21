#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

//https://leetcode.com/problems/divide-two-integers/
/*
29. Divide Two Integers

Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

Observation:

Redo this after almost 2 years:

Since mentioned no *, / or %, the only left are: +, - and bitwise operations.

If you try substract divisor from dividend in a loop, you would get an ETL for the case like (2147483647 / 3), obviously
it asks for a sub-linear solution. Well, if we can't figure out a magic O(1) algorithm, O(logN) is acceptable. You could follow
the idea of BS, like what I did two years ago or you can put this way: if we could reduce the dividend or divisor by a factor,
I meant: (dividend / k) or (divisor / k) in each iteration, we could achieve O(logN). The problem is division is forbidden!
The only option left may be << and >>, then are equivalent to (* 2) and (/ 2).

It's all about "Rate of Convergence"

Naive idea is:

By multiplying divisor with 2 and then compare with dividend, we can reduce dividend quicker. If dividend is no less than 2 times of
divisor, we know the final result shall be added with 2. Then we substract 2 times of divisor from dividend and try 4 times of divosr in the
next run. Kind of greedy. If current k times of divisor is greater than current dividend, we shrink the k times of divisor to half by >>.
See divide2.

The optimization on this is: instead of substracting divisdend on each interation, we find the largest divisor << i, which satisfies:

dividend >= divisor << i and dividend < (divisor << (i + 1))

Then we add i to the final result and substract dividend by (divisor << i)

Then start over again from divisor << 0 if and only if remaining dividend is no less than divisor.

See divide1 and divide0

The generalized idea is:

- Any number can be represented by the additions of power of 2s, plus 1 if the number is odd (it's actually 2^0).

So, dividend can be written like 2^i1 + 2^i2 + 2^i3... + 2^in, given i1 ... in in range of [31, 0]

So, if we divide dividend by divisor K, it implies according to the above:

Dividend = 2^i1 / K + 2^i2 / K + 2^i3 / K ... + 2^in / K

- Since using / is not allowed, we can try the following:

if (K << i1) is no greater than 2^i1, we can tell 2^i1 / K = (1 << i1), given both operands as integers.

- Then we substract (k << i1) from dividend and start over again till dividend is less than original divisor.

See divide

Of course, there are couple integer overflow situations to consider:

- abs(MIN_INT)

- bitwise operation between integer and long, the alignment is to integer

********

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
	//From most significant bit to lest significant bit, total 32 iterations at most. We could say it's O(1) for a given 32-bits integer?
	int divide(int dividend, int divisor) {
		if (0 == divisor)return numeric_limits<int>::max();
		long dividendL = std::abs(dividend * 1L), divisorL = std::abs(divisor * 1L), ans = 0L, d = 0L;
		for (int i = 31; i > -1 && dividendL >= divisorL; --i) {
			d = divisorL << i;
			if (dividendL >= d) {
				dividendL -= d;
				//Make sure 1L here coz gcc will convert wider number to shorter one during (ans | 1), 
				//which could overflow the result even ans is given type Long
				ans |= 1L << i;
			}
		}
		return !((0 <= dividend) ^ (0 < divisor)) ? static_cast<int>(std::min(ans, (long)numeric_limits<int>::max() * 1L)) : static_cast<int>(std::max(ans * -1L, (long)numeric_limits<int>::min() * 1L));
	}
	//From LSB to MSB, 32 iteration at most? Using one less local variable.
	int divide0(int dividend, int divisor) {
		if (0 == divisor)return numeric_limits<int>::max();
		long dividendL = std::abs(dividend * 1L), divisorL = std::abs(divisor * 1L), ans = 0, cnt = 0;
		while (dividendL >= divisorL) {
			while (dividendL >= divisorL << (1 + cnt)) ++cnt;
			ans += (1L << cnt), dividendL -= divisorL * (1L << cnt), cnt = 0;
		}
		return !((0 <= dividend) ^ (0 < divisor)) ? static_cast<int>(std::min(ans, numeric_limits<int>::max() * 1L)) : static_cast<int>(std::max(ans * -1L, numeric_limits<int>::min() * 1L));
	}
	//From LSB to MSB, 32 iteration at most?
	int divide1(int dividend, int divisor) {
		if (0 == divisor)return numeric_limits<int>::max();
		long dividendL = std::abs(dividend * 1L), divisorL = std::abs(divisor * 1L), ans = 0, d = divisorL, t = 1;
		while (dividendL >= divisorL) {
			t = divisorL, d = 1;
			while (dividendL >= (t << 1)) d <<= 1, t <<= 1;
			ans += d, dividendL -= t;
		}
		return !((0 <= dividend) ^ (0 < divisor)) ? static_cast<int>(std::min(ans, numeric_limits<int>::max() * 1L)) : static_cast<int>(std::max(ans * -1L, numeric_limits<int>::min() * 1L));
	}
	//From LSB to MSB, 32 iteration at most?
	int divide2(int dividend, int divisor) {
		if (0 == divisor)return numeric_limits<int>::max();
		long dividendL = std::abs(dividend * 1L), divisorL = std::abs(divisor * 1L), ans = 0, d = divisorL, t = 1;
		while (d >= divisorL) {
			if (dividendL >= d) {
				ans += t;
				dividendL -= d;
				d <<= 1, t <<= 1;
			}
			else d >>= 1, t >>= 1;
		}
		return !((0 <= dividend) ^ (0 < divisor)) ? static_cast<int>(std::min(ans, numeric_limits<int>::max() * 1L)) : static_cast<int>(std::max(ans * -1L, numeric_limits<int>::min() * 1L));
	}
	int divide3(int dividend, int divisor) {
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
	int divide4(int dividend, int divisor) {
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
/*
Test cases:

0
1
1
1
1
-1
-1
1
7
3
10
5
8
2
12345
67
7
9
10
1
-10
1
0
9
-2147483648
-1
2147483647
3

Outputs:

0
1
-1
-1
2
2
4
184
0
10
-10
0
2147483647
715827882
*/