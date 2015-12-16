#include <cassert>
#include <iostream>

using namespace std;

/*
http://en.wikipedia.org/wiki/Integer_factorization
http://en.wikipedia.org/wiki/Trial_division
First of all, we shall know the magic of square root of N, since it plays
a foundmental role in number manipulation, especially decomposition.

We could prove that there could be at most one prime divisor that is greater than square root of N.
Negation: if there are two prime divisors greater than the square root, since they can not be decompsited,
d1*d2 > N, which is impossible.
This means we will have to do an extra check to see if the remaining of N is greater than 1, if so, the
remaining is the last prime divisor.
*/
int countPrimeFactorization(int N)
{
	assert(N > 1);
	int count = 0;
	int prime = 2;
	while (N > 1 && prime*prime <= N)
	{
		if (0 == N%prime)
		{
			++count;
			while (0 == N%prime)
				N /= prime;
		}
		else
			++prime;
	}
	if (N > 1)
		++count;
	return count;
}
void testPrime()
{
	cout << "Expect 1: " << countPrimeFactorization(8) << endl;
	cout << "Expect 1: " << countPrimeFactorization(2) << endl;
	cout << "Expect 1: " << countPrimeFactorization(49) << endl;
	cout << "Expect 2: " << countPrimeFactorization(36) << endl;
	cout << "Expect 2: " << countPrimeFactorization(103 * 373) << endl;
}