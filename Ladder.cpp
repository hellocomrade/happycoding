#include <cassert>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/training9MXHWW-4KB/

Ladder
Count the number of different ways of climbing to the top of a ladder.
Task description
You have to climb up a ladder. The ladder has exactly N rungs, numbered from 1 to N. With each step, you can ascend by one or two rungs. More precisely:

with your first step you can stand on rung 1 or 2,
if you are on rung K, you can move to rungs K + 1 or K + 2,
finally you have to stand on rung N.
Your task is to count the number of different ways of climbing to the top of the ladder.

For example, given N = 4, you have five different ways of climbing, ascending by:

1, 1, 1 and 1 rung,
1, 1 and 2 rungs,
1, 2 and 1 rung,
2, 1 and 1 rungs, and
2 and 2 rungs.
Given N = 5, you have eight different ways of climbing, ascending by:

1, 1, 1, 1 and 1 rung,
1, 1, 1 and 2 rungs,
1, 1, 2 and 1 rung,
1, 2, 1 and 1 rung,
1, 2 and 2 rungs,
2, 1, 1 and 1 rungs,
2, 1 and 2 rungs, and
2, 2 and 1 rung.
The number of different ways can be very large, so it is sufficient to return the result modulo 2P, for a given integer P.

Write a function:

vector<int> solution(vector<int> &A, vector<int> &B);

that, given two non-empty zero-indexed arrays A and B of L integers, returns an array consisting of L integers specifying the consecutive answers; position I should contain the number of different ways of climbing the ladder with A[I] rungs modulo 2B[I].

For example, given L = 5 and:

A[0] = 4   B[0] = 3
A[1] = 4   B[1] = 2
A[2] = 5   B[2] = 4
A[3] = 5   B[3] = 3
A[4] = 1   B[4] = 1
the function should return the sequence [5, 1, 8, 0, 1], as explained above.

Assume that:

L is an integer within the range [1..30,000];
each element of array A is an integer within the range [1..L];
each element of array B is an integer within the range [1..30].
Complexity:

expected worst-case time complexity is O(L);
expected worst-case space complexity is O(L), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.

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