#include <cassert>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/training9MXHWW-4KB/

Observation:

In order to meet O(L) time complexity, each calculation must be finished in O(1),
which will require some memorization up front. However, it's not possible to calculate Fibonacci(30000)
without the help of some BigInteger implementation. unsigned long long probably can only do Fibonacci up to about 140.

Luckily, Codility only asks the reminder of some 2^N. So, we only need to store the reminder of any
Fibonacci using 2^L as the divisor. This will make sure we have all bits necessary to do any modulo
of 2^p, given p in vector B.

Since p is no more than 30 in vector B, we shall using 2^30 as the divisor. Otherwise, we would lose the
accuracy. For example, given m = 17, and we may ask the reminder of m up to 2^5. We could safely do this if
we keep the result of m/2^5 as n, then we could get any reminder from n from 2^1 to 2^5. On the other hand,
if we keep the result of m/2^1 as n1 = 1, we will not be able to get 17/2^5 since n1 = 1, the higher bits have been lost.
*/
vector<int> solutionLadder(vector<int> &A, vector<int> &B)
{
	const int L = 30000;
	const int M = 30;
	unsigned int divisor = 1 << 30;
	int len1 = A.size();
	int len2 = B.size();
	assert(len1 > 0 && len1 == len2);
	vector<int> memo(L + 1);
	vector<int> result(len1);
	memo[0] = 1;
	memo[1] = 1;
	for (int i = 2; i <= L; ++i)
	{
		assert(memo[i - 2] <= numeric_limits<int>::max() - memo[i - 1]);
		memo[i] = (memo[i - 2] + memo[i - 1]) % divisor;

	}
	for (int i = 0; i < len1; ++i)
	{
		assert(B[i] > 0 && B[i] <= M);
		assert(A[i] > 0 && A[i] <= L);
		//this can also be done through: result[i] = memo[A[i]] % ((1 << B[i]) - 1);
		//however, it only works with 2 to the power of p...
		result[i] = memo[A[i]] % (1 << B[i]);
	}
	return result;
}
void printLadderResult(const vector<int> &A)
{
	for (int i : A)
		cout << i << ",";
	cout << endl;
}
void testLadder()
{
	vector<int> ret1 = solutionLadder(vector<int>{ 4, 4, 5, 5, 1 }, vector<int>{ 3, 2, 4, 3, 1 });
	cout << "Expect 5,1,8,0,1:";
	printLadderResult(ret1);

	vector<int> ret2 = solutionLadder(vector<int>{ 1 }, vector<int>{ 1 });
	cout << "Expect 1:";
	printLadderResult(ret2);

	vector<int> ret3 = solutionLadder(vector<int>{ 30000 }, vector<int>{ 8 });
	cout << "Expect 1:";
	printLadderResult(ret3);
}
