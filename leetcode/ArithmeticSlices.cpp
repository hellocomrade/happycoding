#include <vector>

using namespace std;

//https://leetcode.com/problems/arithmetic-slices
/*
413. Arithmetic Slices

A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:

1, 3, 5, 7, 9

7, 7, 7, 7

3, -1, -5, -9

The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of array A is called arithmetic if the sequence:
A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.


Example:

A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.

Observations:

My first attempt, numberOfArithmeticSlices0, is an O(N) time complete search solution based upon the fact that given a arithmetic progression,

[1,3,5,7,9]

The total number of arithmetic progression slice with length no less than 3 is:

(n - 2) + (n - 3) + ... + 2 + 1 = (n - 1) * (n - 2) / 2

So, one can simply scan the array and count the consecutive elements with the same diff. If the diff changes, add the total slices
to the final result based upon the formula above. Then rest counter to 1, and move index backward by 1 so the next iteration shall pick
up the new diff. One more complication is at the end of the scan, of course, as ususal, extra codes to handle possible counter after the loop
exits. It can be done inside the loop with extra check to make sure if i == len, no element from the array should be retrieved.

There is a more elegant solution, someone saying it's a DP...Assume an array DP is offered to store the number of valid slices ends at index i, then
at i + 1, if A[i + 1] - A[i] == A[i] - A[i - 1], then DP[i + 1] = DP[i] + 1, otherwise DP[i + 1] = 0. The final result is the sum of all counts in DP.

This "DP" solution can be simplified if one realizes that only the DP[i] is necessary for DP[i + 1] and DP[i + 1] is either DP[i] + 1 or 0. So, the array DP
is not necessary. Only one tmp variable is needed. Such an implementation is in numberOfArithmeticSlices.
*/
class SolutionArithmeticSlices {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		size_t cnt = 1, len = A.size(), ans = 0;
		for (size_t i = 2, cntHere = 0; i < len; ++i) {
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) ++cntHere;
			else cntHere = 0;
			ans += cntHere;
		}
		return static_cast<int>(ans);
	}
	int numberOfArithmeticSlices0(vector<int>& A) {
		size_t cnt = 1, len = A.size(), ans = 0;
		int diff = 0;
		for (size_t i = 1; i <= len;++i) {
			if (1 == cnt) diff = A[i] - A[i - 1];
			if (i < len && diff == A[i] - A[i - 1]) ++cnt;
			else {
				if (cnt > 2) ans += (cnt - 1) * (cnt - 2) / 2;
				if (len != i) --i;
				cnt = 1;
			}
		}
		return static_cast<int>(ans);
	}
};
/*
Test cases:

[]
[1]
[1,2]
[1,2,3]
[1,3,5,7,9]
[7,7,7,7]
[3,-1,-5,-9]
[1,4,7,11,15,19]
[1,4,7,11,15,19,11,3,-5,-2,1,0,0,0,1,2]
[1,1,2,5,7]

Outputs:

0
0
0
1
6
3
3
4
10
0
*/