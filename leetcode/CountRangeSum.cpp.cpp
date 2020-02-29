#include <cassert>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

//https://leetcode.com/problems/count-of-range-sum/
/*
327. Count of Range Sum

Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i <= j), inclusive.

Note:

A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:

Input: nums = [-2,5,-1], lower = -2, upper = 2,

Output: 3

Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.

Observations:

It's not hard to realize prefix sum here. Then the question turns to: given an array PS with
(prefix sums, index of the prefix sum), find any pair (i, j) that i < j on this array that satisfies:

PS[j] - PS[i] >= lower && PS[j] - PS[i] <= upper

The naive algorithm using two loops takes O(N^2) time.

In order to improve the performance, countRangeSum_1 is a good try. It actually passed OJ. However,
std::distince has linear complexity on non-random-access iterator. So the overall time complexity is:
N(log2 + ... + logN).

Can we make it true O(NlogN)? leetcode 315 (Count of Smaller Numbers After Self) takes advantage of merge
sort. It achieves OlogN by counting while merge sort is conducted.

For me, I tried to copy the same iterative merge sort here, but failed coz it's hard to tell i < j when PS[i]
is compared with PS[j] in linear time on each iteration...

Recursive merge sort though, can solve this perfectly. The nature of recursive merge sort guarantees on each
iteration:

- Left half and right half are both sorted;
- All elements in the left half have indexes less than the ones in te right half;

Therefore, using two pointers (a window) to find out the possible [lower, upper] range on the right half
for every element on the left half is trivial. Furthermore, it's actually a linear algorithm! This is because
the elements on both halves are in non-decreasing order, so the window is always moving to the right.

In other words, say i and i + 1 are both on the left half, so the window for i + 1 could be as same as i or
move to right since PS[i + 1] > PS[i] and lower/upper are constant... Or, if we examine two pointers, they
always move to the right during this process and therefore, a pointer only visit an element on the right half
at most once.

This proves the algorithm is O(NlogN). See countRangeSum.
*/
class SolutionCountRangeSum {
public:
	int countRangeSum(const vector<int>& nums, int lower, int upper) {
		int len = (int)nums.size(), ans = 0;
		if (0 == len) return ans;
		vector<long long> prefixSum(len + 1, 0), aux(len + 1, 0);
		for (int i = 1; i <= len; ++i) prefixSum[i] = nums[i - 1] + prefixSum[i - 1];
		function<int(int, int)> mergeSort = [&](int l, int r) -> int {
			int ans = 0, m = l + (r - l) / 2, i = l, j = m, n = l;
			if (1 == r - l) return ans;
			ans = mergeSort(l, m) + mergeSort(m, r);
			for (int a = l, b = m, c = m; a < m; ++a) {
				while (b < r && prefixSum[b] - prefixSum[a] < lower) ++b;
				while (c < r && prefixSum[c] - prefixSum[a] <= upper) ++c;
				ans += c - b;
			}
			while (i < m && j < r) {
				if (prefixSum[i] <= prefixSum[j]) aux[n++] = prefixSum[i++];
				else aux[n++] = prefixSum[j++];
			}
			while (i < m) aux[n++] = prefixSum[i++];
			while (j < r) aux[n++] = prefixSum[j++];
			std::copy(aux.begin() + l, aux.begin() + r, prefixSum.begin() + l);
			return ans;
		};
		ans = mergeSort(0, len + 1);
		return ans;
	}
	int countRangeSum_1(vector<int>& nums, int lower, int upper) {
		multiset<long long> m;
		long long ans = 0, sum = 0;

		m.insert(0);
		for (int i = 0; i < nums.size(); i++) {
			sum += nums[i];
			ans += distance(m.lower_bound(sum - upper), m.upper_bound(sum - lower));
			m.insert(sum);
		}
		return ans;
	}
};
void TestCountRangeSum() {
	SolutionCountRangeSum so;
	assert(3 == so.countRangeSum(vector<int> {-2, 5, -1}, -2, 2));
	assert(10 == so.countRangeSum(vector<int> {1, 2, 3, 4}, 1, 100));
}
/*
Test cases:

[-2,5,-1]
-2
2
[-2,5,-1]
1
3
[-2,5,-1]
-3
3
[-2,5,-1]
-2
3
[1,-2,3,6,2,3,3,-7,1]
-8
3
[1,-2,3,6,2,3,3,-7]
-5
5
[1,2,3,4]
1
100

Outputs:

3
2
4
4
18
13
10
*/