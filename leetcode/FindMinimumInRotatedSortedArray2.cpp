#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
/*
154. Find Minimum in Rotated Sorted Array II

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

The array may contain duplicates.

Example 1:

Input: [1,3,5]

Output: 1

Example 2:

Input: [2,2,2,0,1]

Output: 0

Note:

- This is a follow up problem to Find Minimum in Rotated Sorted Array.

- Would allow duplicates affect the run-time complexity? How and why?

Observations:

This is a follow up for leetcode 153, "Find Minimum in Rotated Sorted Array". Since duplicates could be introduced on
both end of the array, original approach has to be modified and duplicates have to be bypassed until the elements at two ends
are not the same. Then regular "rotated sorted array search" algorithm can be applied. The only change is that the original
value of ans. Instead of ans[0], ans[l] is used. l here is the index on the left after duplicates removal.

Worse case though is O(N), due to linear scanning for duplicates removal.

Surprisingly, (nums[m] < nums[0]) is still good even there might be duplicates in the middle of the array that might make one
think if a <= makes more sense.

I failed couple times because of the initial value for ans before apply the "regular algorithm". ans actually should be
set twice, one before duplicates removal, so the case like [1,2,3,4,5] can be covered. The other one after duplicates removal,
so the case like [3,3,1,2,3,3] can be covered.
*/
class SolutionFindMinimumInRotatedSortedArray2 {
public:
	int findMin(vector<int>& nums) {
		int l = 0, r = nums.size() - 1, m, ans = nums[0];
		while (l < r && nums[l] == nums[r]) ++l, --r;
		ans = std::min(ans, nums[l]);
		while (l <= r) {
			m = l + (r - l) / 2;
			if (nums[m] < nums[0]) {
				r = m - 1;
				ans = std::min(ans, nums[m]);
			}
			else
				l = m + 1;
		}
		return ans;
	}
};
/*
Test cases:

[9,5,6,7,8,9,9,9,9,9,9]
[1]
[1,1]
[1,1,1]
[10,10,1,10]
[10,10,1,10,10,10]
[10,1,10,10,10]
[10,10,11,17,18,19,1,10,10,10]
[3,1,3]
[3,1,1,3]
[1,3,5]
[2,2,2,0,1]
[1,1,1,1]
[4,4,5,5,6,7,8,1,1,2,2,2,3,4,4]
[5,5,1,2,3,3]
[5,1,2,3,3]
[5,1,2,3]
[5,1,1,2,3]

Outputs:

5
1
1
1
1
1
1
1
1
1
1
0
1
1
1
1
1
1
*/