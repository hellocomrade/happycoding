#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/find-k-closest-elements/
/*
658. Find K Closest Elements

Given a sorted array, two integers k and x, find the k closest elements to x in the array. The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

Example 1:

Input: [1,2,3,4,5], k=4, x=3

Output: [1,2,3,4]

Example 2:

Input: [1,2,3,4,5], k=4, x=-1

Output: [1,2,3,4]

Note:
- The value k is positive and will always be smaller than the length of the sorted array.
- Length of the given array is positive and will not exceed 104
- Absolute value of elements in the array and x will not exceed 104

UPDATE (2017/9/19):

The arr parameter had been changed to an array of integers (instead of a list of integers). Please reload the code definition to get the latest changes.

Observations:

The theory is: given a sorted array A, the k closest elements to x in A is a subarray of A (not a subsequence of A). This is easy to prove by negation:

If a subsequence A', [ai, a(i+1), ..., a(i + k - 1)] exists as the k closest elements to X in A, [a1, a2, a3, a4, a5, ..., an], with any given x, if there is a gap
in A', one could always replace the the elements at two ends of A' with skipped element and get a smaller diff. This is already considered the neagive number cases.

For example:

[-10, -9, -8, 2, 3, 20], k = 4 and x = 0, subsequence [-10, -9, 2, 3] is not the answer coz -8 is skipped. If -10 is replaced with -8, one can get a smaller diff
[-9, -8, 2, 3] and this is the answer.

The naive approach will be sorting A in ascending order by the absolute diff on each element against x then pick the first k smallest elements. Note such k smallest elements
may not be in its natural ascending order since the relations for sorting is decided by the abs diff to x. Therefore, the second sort has to be done in order
to return the result in their natural ascending order. Time complexity O(NlogN) and space complexity is O(K).

This can actually be done in O(logN + K) time using BS and a sliding window/two pointers. Take a closer look on the problem, one may notice that such a k elements subarray will always
contains the closest number to x in A (or the same as x in A) coz its diff is the smallest one. In an alreayed sorted array, finding such an element can be done in O(logN)
using binary search, not to mention the fact STL offers std::lower_bound, which is almost perfect for this job.

Why almost? Coz it only finds the no less than, not the exact closest number to x, considering the following:

[1,4], x = 2, std::lower_bound will find [4], but the closest number is [1]. Given k = 1, [4] should not be picked as answer. There kicks in the two pointers. One
shall find a range that guarantees to cover smallest k elements using the element M that is no less than x as the pivot.

How big is this range? From M, goes to both left and right to k, total (2k + 1) elements, it should cover all cases including the example given above. So, one may have

Left side: MAX(0, M's index - k - 1);
Right side: MIN(len(A) - 1, M's index + k - 1);

So, the range is (k + 2) elements from M, including M; k elements to the right, including M;

Actually, if ones goes with MAX(0, M's index - k) on left and MIN(len(A) - 1, M's index + k) on right, it works as well.

Then with this range in hand, one can run a sliding window with size k and keep tracking the min diff.

There is actually a more elegant solution that get things done in one BS procedure. I will post it later once I think I fully
understand the code.
*/
class SolutionFindKClosestElements {
public:
	vector<int> findClosestElements(vector<int>& arr, int k, int x) {
		vector<int> ans(k, 0);
		int diff_min = numeric_limits<int>::max(), len = (int)arr.size(), l_min = 0, diff = 0;
		std::vector<int>::iterator itor = std::lower_bound(arr.begin(), arr.end(), x);
		//The following coarse "guess" works as well
		//for (int i = std::max(0, (int)(itor - arr.begin()) - k), r = std::min((int)(itor - arr.begin()) + k, len), l = i; i <= r; ++i) {
		for (int i = std::max(0, (int)(itor - arr.begin()) - k - 1), r = std::min((int)(itor - arr.begin()) + k - 1, len), l = i; i <= r; ++i) {
			if (l + k == i) {
				if (diff < diff_min) diff_min = diff, l_min = l;
				diff -= std::abs(arr[l++] - x);
			}
			if (i < r) diff += std::abs(arr[i] - x);
		}
		for (int i = l_min, j = 0; i < l_min + k; ++i) ans[j++] = arr[i];
		return ans;
	}
};
/*
Test cases:

[1,2,3,4,5]
4
3
[1,2,3,4,5]
4
-1
[1, 2, 3]
3
2
[1, 2, 3]
2
3
[1, 4, 6, 8]
3
3
[-12,-8,-8,0,0,1,4,10,12,16,16,20,21,27,32]
5
-10
[1]
1
10
[10,10,10,10,10]
3
100
[-1,0,1,2,3]
3
1
[-1,1]
1
0

Outputs:

[1,2,3,4]
[1,2,3,4]
[1,2,3]
[2,3]
[1,4,6]
[-12,-8,-8,0,0]
[1]
[10,10,10]
[0,1,2]
[-1]
*/