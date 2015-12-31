#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/media/train/9-Sieve.pdf
A natural number (i.e. 1, 2, 3, 4, 5, 6, etc.) is called a prime number (or a prime)
if it has exactly two positive divisors, 1 and the number itself.

The Sieve of Eratosthenes is a very simple and popular technique for finding all the prime
numbers in the range from 2 to a given number n. The algorithm takes its name from the
process of sieving—in a simple way we remove multiples of consecutive numbers.

Initially, we have the set of all the numbers {2, 3,...,n}. At each step we choose the
smallest number in the set and remove all its multiples.

Notice that we needn’t cross out multiples of i which are less than i^2. Such multiples are of the
form k * i, where k<i. These have already been removed by one of the prime divisors of k.
*/
vector<bool> sieve(int N)
{
	assert(N > 0);
	vector<bool> primes(N + 1, true);
	primes[0] = primes[1] = false;
	int i = 2, k;
	while (i * i <= N)
	{
		if (true == primes[i])
		{
			k = i * i;
			while (k <= N)
			{
				primes[k] = false;
				k += i;
			}
		}
		++i;
	}
	return primes;
}
void printPrimes(const vector<bool> &primes)
{
	int count = 0;
	for (bool b : primes)
	{
		if (true == b)
			cout << count << ",";
		++count;
	}
	cout << endl;
}
void testSieve()
{
	printPrimes(sieve(20));
	printPrimes(sieve(12));
}