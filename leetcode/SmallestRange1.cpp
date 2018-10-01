#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/smallest-range-i/
/*
908. Smallest Range I

Given an array A of integers, for each integer A[i] we may choose any x with -K <= x <= K, and add x to A[i].

After this process, we have some array B.

Return the smallest possible difference between the maximum value of B and the minimum value of B.

Example 1:

Input: A = [1], K = 0

Output: 0

Explanation: B = [1]

Example 2:

Input: A = [0,10], K = 2

Output: 6

Explanation: B = [2,8]

Example 3:

Input: A = [1,3,6], K = 3

Output: 0

Explanation: B = [3,3,3] or B = [4,4,4]


Note:

- 1 <= A.length <= 10000
- 0 <= A[i] <= 10000
- 0 <= K <= 10000

Observations:

The question asks to minimize the difference between max(A) and min(A) by applying x on elements.

It's easy to know the smallest max(B) is max(A) - K and largest min(B) is min(A) + K.
If max(A) - min(A) - 2 * K < 0, a smaller K can be applied and max(A) - min(A) - 2 * K = 0. The smallest
difference one can get.
*/
class SolutionSmallestRange1 {
public:
	int smallestRangeI(vector<int>& A, int K) {
		int mx = 0, mn = 10001;
		for (int i : A) {
			mx = std::max(mx, i);
			mn = std::min(mn, i);
		}
		return std::max(0, mx - mn - 2 * K);
	}
};