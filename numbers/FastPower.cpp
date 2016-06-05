//http://www.lintcode.com/en/problem/fast-power/
/*
Fast Power

Calculate the an % b where a, b and n are all 32bit integers.

Example
For 2^31 % 3 = 2

For 100^1000 % 1000 = 0

For 1^2147483647 % 2147483647 = 1

Challenge
O(logn)

Observations:
Since requiring O(logN), we need to figure out a way to "divide and conquer". It's actually not exactly
DC as the hint says coz we need to disregard half of the scope in orde to achieve logN. Usually we do
this by N/2, just like binary search. Can we do it here?

Fisrt of all, let's see how modulus plays here.
1. Given a number K = m * n, and divisor L
K % L == (m % L) * (n % L)

32 = 2^3 * 2^2, given 5 as divisor: 32 % 5 = 2, on the other hand
8 % 5 = 3, 4 % 5 = 4, (3 * 4) % 5 = 2

2. Given a number K, a number M, and divisor L
(K * M) % L = (M * (K % L)) % L

With the above two discoveries, we could come out a solution.
So, what if we always only do modulus on (n/2) and do it recursively?

First: if n is a odd number
2^5 = 2^2 * 2^3, we only need to know the modulus of 2^2, then we could know 2^3 by considering it as 2^2 * 2,
which falls into the second theorem.
Then we could combine the result of 2^2 % D with 2^3 % D to get 2^5 % D through theorem 1.

When n is an even number,
2^4 = 2^2 * 2^2, we can skip theorem 2, given K as the result of 2^2 % D, we simply do (K * K) % D to get the result.

The termination of recursion depends on the result f n/2, which has two possible results: 0 and 1
if 0: we do 1 % b (you can't simply return 1, since b could be 1 as well)
if 1: we do a % b
*/
class SolutionFastPower {
public:
	/*
	* @param a, b, n: 32bit integers
	* @return: An integer
	*/
	int fastPower(int a, int b, int n) {
		// write your code here
		if (n == 0)return 1 % b;
		else if (n == 1)return a % b;
		long long ret = fastPower(a, b, n / 2);
		return (n / 2 * 2 != n) ? (ret * ((ret * a) % b)) % b : (ret * ret) % b;
	}
};