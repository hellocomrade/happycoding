#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/training9ZJJ2Z-764/
Observations:
A semi-prime number is actually a composite number that only has 3 divisors, 1 and two primes.
Using the same technique for prime factorization, we could calculate the smallest prime divsor for
every composite number in O(N * log(log(N))), which is as same as Sieve Of Eratosthene.

Then, we scan the vector to find out: for each natural number (starting from 2) i, if i divided by its
smallest prime number could generate another prime number. If so, i is a semi-prime number.

Notice it requires at most O(M) to complete all range queries, which means each query should be done in
O(1). In order to achieve this, we need a "prefix sum" like O(N) space to pre-count the number of semi-prime
number ending at natural number i. So for the range query, we then can simply do A[Q[i]]-A[P[i]-1], given
A as such an array.

Well, it took me 81 minutes to figure all this out... :(
*/
vector<int> solutionCountSemiprimes(int N, const vector<int> &P, const vector<int> &Q)
{
	assert(N > 0 && N < 50001);
	int lenp = P.size();
	int lenq = Q.size();
	assert(lenp == lenq && lenp > 0 && lenp < 30001);
	vector<int> primesDivisors(N + 1, 0);
	vector<int> counts(N + 1, 0), result(lenp, 0);
	int i = 2, k;
	while (i * i <= N)
	{
		if (0 == primesDivisors[i])
		{
			k = i*i;
			while (k <= N)
			{
				primesDivisors[k] = i;
				k += i;
			}
		}
		++i;
	}
	for (i = 2, k = 0; i <= N; ++i)
	{
		/*
		primesDivisors[i] == 0 means i itself is a prime number. Therefore, no need to check since
		prime number itself is not a semi-prime number for sure.
		this setup also avoid dividing-by-zero for the second check condition
		*/
		if (0 != primesDivisors[i] && 0 == primesDivisors[i / primesDivisors[i]])
			++k;
		counts[i] = k;
	}
	for (i = 0; i < lenp; ++i)
		result[i] = counts[Q[i]] - counts[P[i] - 1];
	return result;
}
void printSemiprimesCounts(const vector<int> &A)
{
	for (int c : A)
		cout << c << ",";
	cout << endl;
}
void testCountSemiprimes()
{
	cout << "Expect 10,4,0: ";
	printSemiprimesCounts(solutionCountSemiprimes(26, vector<int>({ 1, 4, 16 }), vector<int>({ 26, 10, 20 })));
	cout << "Expect 0,0,0: ";
	printSemiprimesCounts(solutionCountSemiprimes(1, vector<int>({ 1, 1, 1 }), vector<int>({ 1, 1, 1 })));
}
