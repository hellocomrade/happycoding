#include <cassert>
/*
A positive integer D is a factor of a positive integer N if there exists an integer M such that N = D * M.

For example, 6 is a factor of 24, because M = 4 satisfies the above condition (24 = 6 * 4).

Write a function:

int solution(int N);

that, given a positive integer N, returns the number of its factors.

For example, given N = 24, the function should return 8, because 24 has 8 factors, namely 1, 2, 3, 4, 6, 8, 12, 24. There are no other factors of 24.

Assume that:

N is an integer within the range [1..2,147,483,647].

Complexity:

expected worst-case time complexity is O(sqrt(N));
expected worst-case space complexity is O(1).


test case includes:
[correctness test]
24,
square,
tiny
N=41,42
simple2: 69,64
simple3: 6!
simple4:
simple5
extreme_one: 1

[performance test]
medium1:9!
medium2: 10!
big1
big2:2^28
big3
extreme_maxint:max_int

Observations:
Based on one divisor, we can find the symmetric divisor. More precisely, if number a is a divisor of n,
then n/a is also a divisor. One of these two divisors is less than or equal to square root of n
(If that were not the case, n would be a product of two numbers greater than the square root of n, which is impossible.)

Thus, iterating through all the numbers from 1 to the square root of n allows us to find all the divisors.
If number n is of the form k^2 , then the symmetric divisor of k is also k. This divisor should be counted
just once.
*/
int countFactors(int N)
{
	int cnt = 0;
	assert(N > 0);
	int candidate = 1;
	while (candidate*candidate < N)
	{
		if (N%candidate == 0)
			cnt += 2;
		++candidate;
	}
	if (candidate*candidate == N)
		++cnt;
	return cnt;
}