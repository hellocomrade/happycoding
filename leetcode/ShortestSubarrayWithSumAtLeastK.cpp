#include <deque>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
/*
862. Shortest Subarray with Sum at Least K

Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.

If there is no non-empty subarray with sum at least K, return -1.

Example 1:

Input: A = [1], K = 1

Output: 1

Example 2:

Input: A = [1,2], K = 4

Output: -1

Example 3:

Input: A = [2,-1,2], K = 3

Output: 3


Note:

- 1 <= A.length <= 50000
- -10 ^ 5 <= A[i] <= 10 ^ 5
- 1 <= K <= 10 ^ 9

Observations:
"Contiguous subarray" should give one the hint that prefix sum array shall be used. A naive O(N^2) implmentation could be:

class Solution {
public:
	int shortestSubarray(vector<int>& A, int K) {
		int ans = A.size() + 1;
		vector<long long> prefixSum(A.size() + 1, 0);
		std::partial_sum(A.begin(), A.end(), prefixSum.begin() + 1);
		for(int i = 0; i < prefixSum.size(); ++i)
			for(int j = i + 1; j - i < ans && j < prefixSum.size(); ++j)
				if(prefixSum[j] - prefixSum[i] >= K) {
					ans = std::min(ans, j - i);
					break;
				}
		return ans == A.size() + 1 ? -1 : ans;
	}
};

While the local optimizations such as early break have been made, it's still a TLE which indicate there
should be a linear or sub-linear algorithm is preferred.

Considering leetcode 239 (Sliding Window Maximum): https://github.com/hellocomrade/happycoding/blob/master/leetcode/SlidingWindowMaximum.cpp
A sliding window using a deque to maintain a monotonic list for one of the pointers while the other pointer
iterates.

For this case, the left pointer should be put on a deque that is maintained in an increasing order from front to back,
in other words, the smallest is on the front.

The idea is, when the right pointer reaches index i, prefixSum[i] - prefixSum[deque.front()] will be compared with K.
If it meets the need (prefixSum[i] - prefixSum[deque.front()] >= K), one can safely discard deque.front() from the deque
because: for any index that right pointer i' will be represented, i' > i, and therefore (i - deque.front()) will always
be smaller than (i' - deque.front()). For this problem, the "shortest" is needed.

Once prefixSum[i] is compared with the values on the deque from front to the back until (prefixSum[i] - prefixSum[deque.front()] < K),
in order to maintain the increasing order on the deque, i will be inserted from the back of the deque. Anything on the back
of the deque that prefixSum[deque.back()] > prefixSum[i] can be safely removed for the similar reason mentioned above because
prefixSum[i] is smaller and closer to any future right pointer.

This algorithm's time complexity is O(N). This is because each element on the prefixSum
array will be visted (inserted into and removed from) on the deque at most twice.
*/
class SolutionShortestSubarrayWithSumAtLeastK {
public:
	int shortestSubarray(vector<int>& A, int K) {
		int len = A.size() + 1;
		int ans = len;
		deque<int> dq;
		vector<long long> prefixSum(len, 0);
		std::partial_sum(A.begin(), A.end(), prefixSum.begin() + 1);
		for (int i = 0; i < len; ++i) {
			while (false == dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= K) {
				ans = std::min(ans, i - dq.front());
				dq.pop_front();
			}
			while (false == dq.empty() && prefixSum[i] <= prefixSum[dq.back()]) dq.pop_back();
			dq.push_back(i);
		}
		return ans == len ? -1 : ans;
	}
};
/*
Test cases:

[1]
1
[1,2]
4
[2,-1,2]
3
[2,-1,3,-2,-5]
3
[56,-21,56,35,-9]
61
[-28,81,-20,28,-29]
89
[45,95,97,-34,-42]
21

Output:

1
-1
3
1
2
3
1
*/