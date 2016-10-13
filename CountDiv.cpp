#include <iostream>
#include <cassert>

using namespace std;

//https://codility.com/demo/results/trainingD4B24H-8MD/
/*
CountDiv
Compute number of integers divisible by k in range [a..b].
Task description
Write a function:

int solution(int A, int B, int K);
that, given three integers A, B and K, returns the number of integers within the range [A..B] that are divisible by K, i.e.:

{ i : A ≤ i ≤ B, i mod K = 0 }
For example, for A = 6, B = 11 and K = 2, your function should return 3, because there are three numbers divisible by 2 within the range [6..11], namely 6, 8 and 10.

Assume that:

A and B are integers within the range [0..2,000,000,000];
K is an integer within the range [1..2,000,000,000];
A ≤ B.
Complexity:

expected worst-case time complexity is O(1);
expected worst-case space complexity is O(1).

Observations:
0 is considered mod K = 0 for all given K.

If we count number of divisors in [0, A] as AA and [0, B] as BB for K and use 0 as the base line. By BB - AA, we will have the
number of divisors? The only exception is when A % K == 0, in this case, we need plus 1.
*/
int solutionCountDiv(int A, int B, int K) {
	return B / K - A / K + (0 == A % K ? 1 : 0);
}
void testCountDiv() {
	assert(3 == solutionCountDiv(6, 11, 2));
	assert(20 == solutionCountDiv(11, 345, 17));
	assert(1 == solutionCountDiv(0, 0, 11));
	assert(0 == solutionCountDiv(1, 1, 11));
	assert(1 == solutionCountDiv(0, 1, 11));
	assert(1 == solutionCountDiv(10, 10, 5));
	assert(0 == solutionCountDiv(10, 10, 7));
	assert(0 == solutionCountDiv(10, 10, 20));
}