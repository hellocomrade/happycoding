#include <string>
#include <sstream>

using namespace std;

//https://leetcode.com/problems/permutation-sequence/
/*
60. Permutation Sequence

The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

"123"
"132"
"213"
"231"
"312"
"321"

Given n and k, return the kth permutation sequence.

Note:

Given n will be between 1 and 9 inclusive.
Given k will be between 1 and n! inclusive.

Example 1:

Input: n = 3, k = 3
Output: "213"
Example 2:

Input: n = 4, k = 9
Output: "2314"

Observations:

If we doing this using the algorithm in Next Permutation (leetcode 31), it will take NN! time if k = n!. So better off that route.

Actually we could predict the digits for the k permutation if the lexicographical order is maintained and n is no longer than 9.

Given n = 3,

"123"
"132"
"213"
"231"
"312"
"321"

There are total 6 permutations and for number from 1 to 3 (3 numbers total), among 6 permutations, each number shows up twice at the most significant digit.

this can be calculated by: [times showing up] = Factorial / n => 6 / 3 = 2

Then if k = 3, the index of the actual number can be calculated by: (k - 1) / [times showing up] => (3 - 1) / 2 = 1,

which will be the second number in the array of [1, 2, 3].

Now move to the second digit, factorial is equal to 2, given the fact that number 2 is taken at the previous step, only [1, 3] left.
So the question is transformed to: in array [1, 3], find the k' number, which k' = (k - 1) % factorial = (3 - 1) % 2 = 0, so 1 is chosen.

The reason we have to do a modulus operator is that k will eventually be larger than the remaining factorial and we only care the reminder.

This general idea shall work, but it took me lots of time to get the correct number for k and m at each iteration! The root of the trouble is:

k is given as 1 base, but all our calculations are based upon 0 based. For example, given n = 4 and k = 6, on the most significant digit, each number
in [1...4] shows up 6 times, then k / 6 is supposed to reveal the index, however 6 / 6 = 1, but 0 is expected.

Turn out to be way easier if we decrease k by 1 up front, then everything will be 0 based, that's getPermutation.

getPermutation1 tries not to touch k and see the extra for getting the right numbers?

Since 1 <=n <= 9, the inner loop is considered using constant time. The overal is O(N) time and O(1) space then.
*/
class SolutionPermutationSequence {
public:
	string getPermutation(int n, int k) {
		int f = 1, i = n, m = 0, j = 0, memo[9] = { 0 };
		while (i > 1) f *= i--;
		stringstream ss;
		for (i = n, --k; i > 0; --i, j = 0) {
			k = k % f, f /= i; m = k / f + 1;
			while (m > 0) if (0 == memo[j++]) --m;
			memo[j - 1] = 1;
			ss << j;
		}
		return ss.str();
	}
	string getPermutation1(int n, int k) {
		int factorial = 1, i = n, j = 0, m = 0, memo[9] = { 0 };
		stringstream ss;
		while (i > 1) factorial *= i--;
		for (i = n; i > 0; --i) {
			j = (k - 1) * i / factorial + 1, k = (k - 1) % (factorial / i) + 1, factorial /= i;
			for (m = 0; j > 0 && m < n; ++m)
				if (0 == memo[m]) --j;
			ss << m, memo[m - 1] = -1;
		}
		return ss.str();
	}
};
/*
Test cases:

1
1
2
1
2
2
3
1
3
2
3
3
3
4
3
5
3
6
4
3
4
6
4

Outputs:

"1"
"12"
"21"
"123"
"132"
"213"
"231"
"312"
"321"
"1324"
"1432"
"1342"
*/