#include <vector>

using namespace std;

//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array
/*
153. Find Minimum in Rotated Sorted Array

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:

Input: [3,4,5,1,2]

Output: 1

Example 2:

Input: [4,5,6,7,0,1,2]

Output: 0

Observations:

This is a variation of leetcode 33, "Search Rotated Sorted Array". It has been proved that using nums[0] as anchor point
is the best choice. Therefore, in a rotated sorted array, BS condition is:

- If nums[m] < nums[0], the minimum value is between [0, m]. For example: [4,5,6,1,2,3,4,5]. Therefore, moving r to m - 1
and we take m as the index as the minimum value for now;

- Otherwise, l = m + 1;

One may argue how about the edge casethat the rotated sorted array is a sorted array? For example, [1,2,3,4,5]. If ans is initialized
with 0, the first branch will never be reached and ans will never be set. Therefore, ans remains as 0 in the edge case, which is the
correct answer.
*/
class SolutionFindMinimumInRotatedSortedArray {
public:
	int findMin(vector<int>& nums) {
		int l = 0, r = nums.size() - 1, m, ans = 0;
		while (l <= r) {
			m = l + (r - l) / 2;
			if (nums[m] < nums[0]) {
				r = m - 1;
				ans = m;
			}
			else l = m + 1;
			//cout << l <<','<<r<<endl;
		}
		return nums[ans];
	}
};
/*
Test cases:

[5,1,2,3,4]
[3,1,2]
[0,1,2]
[3,4,5,1,2]
[4,5,6,7,0,1,2]
[1,2,3,4,5]
[2,3,4,5,1]
[1]
[0,1]
[1,0]

Outputs:

1
1
0
1
0
1
1
1
0
0
*/