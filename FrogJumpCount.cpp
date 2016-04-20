#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/media/train/15-DynamicProgramming.pdf

Problem: A small frog wants to get from position 0 to k (1 <= k <= 10,000). The frog can
jump over any one of n fixed distances s0, s1, ..., sn−1 (1 <= si <= k). The goal is to count the
number of different ways in which the frog can jump to position k. To avoid overflow, it is
sufficient to return the result modulo q, where q is a given number.

We assume that two patterns of jumps are different if, in one pattern, the frog visits
a position which is not visited in the other pattern.

Observation:
This is actually a variation of integer partition. Comparing with integer partition,
1. The partition has a contraint: you can only partition the integer by the given array S;
2. The duplicates are valid. For example, here is a partition of 4
   4
   3 + 1
   2 + 2
   2 + 1 + 1
   1 + 1 + 1 + 1

   if [1, 2, 3, 4] is given, then (3, 1) and (1, 3) are considered as two different ways to reach 4;
3. Instead of printing out the partitions, this one asks to print count % P. It's like Fibonacci sequence...
*/
int solutionFrogJumpCount(int K, const vector<int> &A)
{
	const int divisor = 1 << 7;
	int len = A.size();
	int empty = 0;
	vector<int> memo = vector<int>(K + 1, empty);
	memo[0] = 1;
	for (int i = *std::min_element(A.begin(), A.end()); i <= K; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			if (i >= A[j])
				memo[i] = (memo[i] + memo[i - A[j]]) % divisor;
		}
	}
	return memo[K];
}
void testFrogJumpCount()
{
	cout << "Expect 47: " << solutionFrogJumpCount(10, vector<int>{1, 3, 5}) << endl;
}
