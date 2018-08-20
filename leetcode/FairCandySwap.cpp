#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

//https://leetcode.com/problems/fair-candy-swap/
/*
888. Fair Candy Swap

Alice and Bob have candy bars of different sizes: A[i] is the size of the i-th bar of candy that Alice has, and B[j] is the size of the j-th bar of candy that Bob has.

Since they are friends, they would like to exchange one candy bar each so that after the exchange, they both have the same total amount of candy.  (The total amount of candy a person has is the sum of the sizes of candy bars they have.)

Return an integer array ans where ans[0] is the size of the candy bar that Alice must exchange, and ans[1] is the size of the candy bar that Bob must exchange.

If there are multiple answers, you may return any one of them.  It is guaranteed an answer exists.



Example 1:

Input: A = [1,1], B = [2,2]

Output: [1,2]

Example 2:

Input: A = [1,2], B = [2,3]

Output: [1,2]

Example 3:

Input: A = [2], B = [1,3]

Output: [2,3]

Example 4:

Input: A = [1,2,5], B = [2,4]

Output: [5,4]


Note:

- 1 <= A.length <= 10000
- 1 <= B.length <= 10000
- 1 <= A[i] <= 100000
- 1 <= B[i] <= 100000
- It is guaranteed that Alice and Bob have different total amounts of candy.
- It is guaranteed there exists an answer.

Observations:

Seeking exchaning one element from each array to achieve an equal sum.

Tried to look for an O(N) time and O(1) space solution but didn't get any. It will be either O(NlogN) time with O(1) space
or O(N) time with O(N) space.

The idea is, given Xi for array X and Yj for array Y

SUM(X) - Xi + Yj == SUM - Yj - Xi

=>

SUM(X) - 2 * Xi = SUM(Y) - 2 * Yj

Yj = (SUM(Y) - SUM(X) + 2 * Xi) / 2

Given the fact that an answer is guaranteed, no guard code is needed.

Caculate sums from two arrays first then loop through array A and see if such element in array B is available. This
can be done through sorting array B and BS or a hash set, which requires O(N) extra space but guarantee O(1) access.
*/
class SolutionFairCandySwap {
public:
	vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
		int suma = std::accumulate(A.begin(), A.end(), 0), sumb = std::accumulate(B.begin(), B.end(), 0), t;
		std::sort(B.begin(), B.end());
		vector<int> ans(2, 0);
		for (int i : A) {
			t = (sumb - suma + 2 * i) / 2;
			auto itor = std::lower_bound(B.begin(), B.end(), t);
			if (B.end() != itor && t == *itor) {
				ans[0] = i, ans[1] = *itor;
				break;
			}
		}
		return ans;
	}
};
/*
Test cases:

[1,1]
[2,2]
[1,2]
[2,3]
[2]
[1,3]
[1,2,5]
[2,4]
[1,5,8]
[2,3,5]
[1]
[1]

Outputs:

[1,2]
[1,2]
[2,3]
[5,4]
[5,3]
[1,1]
*/