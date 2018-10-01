#include <cassert>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/smallest-range-ii/
/*
910. Smallest Range II

Given an array A of integers, for each integer A[i] we need to choose either x = -K or x = K, and add x to A[i] (only once).

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

Output: 3

Explanation: B = [4,6,3]


Note:

- 1 <= A.length <= 10000
- 0 <= A[i] <= 10000
- 0 <= K <= 10000

Observations:

This is based upon leetcode 908 (Smallest Range I). In this case, one can only applies K or -K on
each element. Three possibilites:

1. Add K on each element, then the answer is max(A) - min(A);
2. Substract K on each element, then the answer is as same as the above;
3. m out of len(A) applied adding K, others have K substracted. If the result array is given name B,
then the answer is max(B) - min(B);

Obviously, the effort shall be focused on item 3: how to find max(B) and min(B) if m could be any number
between 1 and len(A) - 1?

If A is sorted and the smallest possible difference is the target, it's obvious that adding K shall be
applied on the left side and substracting K is on the right side. Why? Adding K onto the larger numbers and
substracting K onto the smaller numbers will only enlarge the difference.

With the thought above in mind, B can be represented as:

[A[0] + K, A[2] + K, A[m - 1] + K, A[m] - K, A[len(A) - 1] - K]

Where are the max(B) and min(B)? Since A has been sorted, both subarraies:

[A[0] + K, A[2] + K, A[m - 1] + K], denoted as B1

and

[A[m] - K, A[len(A) - 1] - K]], denoted as B2

are sorted as well. It's easy to tell:

max(B1) = A[m - 1] + K, min(B1) = A[0] + K;

max(B2) = A[len(A) - 1] - K, min(B2) = A[m] - K;

So, given any m in between [1, len(A) - 1]

max(B) = max(max(B1), max(B2))

min(B) = min(min(B1), min(B2))

In terms of implementation, the original ans is set to A[len - 1] - A[0] (case 1 and 2) after A is sorted.
Then, linearly scanning A in order to get every possible max(B1) and min(B2). Update ans if
necessary.

Overall time complexity: O(NlogN), space complexity is O(logN) due to the quick sort
*/
class SolutionSmallestRange2 {
public:
	int smallestRangeII(vector<int>& A, int K) {
		std::sort(A.begin(), A.end());
		int len = (int)A.size(), ans = A[len - 1] - A[0];
		for (int i = 0; i < len - 1; ++i)
			ans = std::min(ans, std::max(A[len - 1] - K, A[i] + K) - std::min(A[0] + K, A[i + 1] - K));
		return ans;
	}
};
void TestSmallestRange2() {
	SolutionSmallestRange2 so;
	vector<int> vec1{ 1 };
	assert(0 == so.smallestRangeII(vec1, 0));
	vector<int> vec2{ 10, 0 };
	assert(6 == so.smallestRangeII(vec2, 2));
	vector<int> vec3{ 3, 6, 1 };
	assert(3 == so.smallestRangeII(vec3, 3));
	vector<int> vec4{ 1, 2, 50, 100 };
	assert(95 == so.smallestRangeII(vec4, 2));
	vector<int> vec5{ 34, 161, 154, 68, 35, 689, 235, 138, 757, 25, 25, 138, 34, 0, 364, 235 };
	assert(515 == so.smallestRangeII(vec5, 121));
}