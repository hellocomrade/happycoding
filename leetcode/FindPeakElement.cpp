#include <vector>

using namespace std;

//https://leetcode.com/problems/find-peak-element/
/*
162. Find Peak Element

A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

Note:
Your solution should be in logarithmic complexity.

Observations:
Same as local minima, given num[-1] = num[n] = -∞, local maxima is guaranteed.

Therefore, apply BS, given m = l + (r - l) / 2, if:

- num[m] < num[m + 1], local maxima exists in [m + 1, len(num) - 1] range;

- num[m] > num[m + 1], local maxima exists in [0, m];

Since we have an imaginary boundaries here, edge cases has to be considered when:

- 0 == m;

- len - 1 == m;

- 1 == len;

findPeakElement1 is my submission. It works but ugly. The official solution looks way better, findPeakElement

https://leetcode.com/problems/find-peak-element/solution/

Instead of returning m directly, we let loop exits, with carefully considered conditions, l is the answer for sure.

*/
class SolutionFindPeakElement {
public:
	int findPeakElement(vector<int>& nums) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		while (l < r) {
			m = l + (r - l) / 2;
			if (nums[m] < nums[m + 1])l = m + 1;
			else r = m;
		}
		return l;
	}
	int findPeakElement1(vector<int>& nums) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		while (l <= r) {
			m = l + (r - l) / 2;
			if (0 == m && m + 1 < len - 1 && nums[m] > nums[m + 1])return m;
			if (len - 1 == m && m - 1 > -1 && nums[m] > nums[m - 1])return m;
			if (nums[m] > nums[m - 1] && nums[m] > nums[m + 1])return m;
			else if (nums[m] < nums[m + 1]) l = m + 1;
			else r = m - 1;
		}
		return 0;
	}
};
/*
Test cases:
[]
[1]
[1,2,3,1]
[1,2]
[2,1]
[0,5,0,1,2]
[0,5,0,1,2,3]

Results:
-1
0
2
1
0
4
5
*/