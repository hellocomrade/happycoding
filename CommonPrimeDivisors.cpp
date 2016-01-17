#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingWJ5MNW-XB5/
Observations:
1. if (1,1) is given, since both of them don't have any prime divisor, the counts are both 0. They both
have 0 prime divisor, therefore, they have identical number of prime divisors.
2. for any prime number pair having nonidentical primes, they will not have the same prime divisor for sure.
3. for any prime number pair having idnetical number, they have same prime divisor as itself.
4. for any composite number pair, if they have same prime divisors, those primes must be divisors of this
pair's gcd as well. We then transform the problem to:

Given A, B, C=gcd(A,B), how could we tell A/C and B/C only contain prime divisors in C?

if so, the value of gcd(A/C, C) will always be a valid divisor of A/C. We then continue this by:
D=A/C, D /= gcd(D,C), if gcd(D,C) == 1 and D == 1, we know all prime divisors in D are included in
C.

if both A and B meet the above requirement, they must have the identical prime divisors.
*/
int solutionCommonPrimeDivisors(vector<int> &A, vector<int> &B)
{
	int len = A.size();
	assert(len >= 1 && len < 60001 && B.size() == len);
	int a, b, c, d = 0, cnt = 0;
	for (int i = 0; i < len; ++i)
	{
		a = A[i];
		b = B[i];
		d = gcd(a, b);
		while ((c = gcd(a, d)) != 1)
			a /= c;
		while ((c = gcd(b, d)) != 1)
			b /= c;
		if (1 == a && 1 == b)
			++cnt;
	}
	return cnt;
}
void testCommonPrimeDivisors()
{
	//[[1, 5, 17, 1, 2147483646], [1, 5, 16, 2, 715827882]]
	cout << "Expect 1: " << solutionCommonPrimeDivisors(vector<int>{2 * 3 * 5}, vector<int>{2 * 3 * 10}) << endl;
	cout << "Expect 0: " << solutionCommonPrimeDivisors(vector<int>{2 * 7 * 5}, vector<int>{2 * 3 * 10}) << endl;
	cout << "Expect 1: " << solutionCommonPrimeDivisors(vector<int>{11 * 17 * 5}, vector<int>{5 * 17 * 11 * 11}) << endl;
	cout << "Expect 0: " << solutionCommonPrimeDivisors(vector<int>{11 * 17 * 31}, vector<int>{31 * 3 * 10 * 31}) << endl;
	cout << "Expect 1: " << solutionCommonPrimeDivisors(vector<int>{2 * 3 * 3 * 7}, vector<int>{8 * 3 * 14 }) << endl;
	cout << "Expect 2: " << solutionCommonPrimeDivisors(vector<int>{1, 5, 10, 6, 3}, vector<int>{1, 8, 5, 2, 9}) << endl;
	cout << "Expect 3: " << solutionCommonPrimeDivisors(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) << endl;
}