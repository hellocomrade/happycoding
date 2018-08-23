#include <cassert>
#include <vector>

using namespace std;

//https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
/*
81. Search in Rotated Sorted Array II

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.

Observations:
This is a follow up on leetcode 33. By introducing duplicates into nums, the previous condition for deciding where target
value is in terms of rotation doesn't work: (nums[m] < nums[l]) ^ (target < nums[l]), nums[l] could be equal to nums[r] due to
the potential duplicates.

I tried couple combinations to solve this but still keep the original idea in leetcode 33, none of them worked out.

It appears that we will have to face the fact that the worse case for this one is O(N).

Since the trouble is brought by duplicates, we could though solve the duplicates on two ends in a while loop. The question is then:

If we are only bothered by the duplicates at two ends of the array, or we have to deal with it on every subarray in range of [l, r] in each iteration?

After a second thoughts, we actually only care the duplicates at two ends of the array. In fact, given [AB] as a rotated sorted array,
there is no way you can find duplicates in both A and B unless they are at the beginning of A and end of B.

All in all, only duplicates at beginning and end of array affect the algorithm in leetcode 33. We could solve it by moving pointers l and r
inward if nums[l] == nums[r]. Then same algorithm in leetcode 33 can be applied.

***Update on 8/23/2018***

It appears using nums[k], k is the leftmost after duplicates removal as the anchor point is a simpler choice than nums[l], which may subject to change when l is changed.
Original thought on using nums[0] as leetcode 33 (Search in Rotated Sorted Array) would work, but the inner branches are based upon unbalanced inner conditions.

In fact nums[k] is equivalent to nums[0] in leetcode 33 since there is no duplicates in leetcode 33.

An other edge case is: before duplicate removals, one may think using:

target == nums[0]

to take care the case th target is the first element in the nums. Then during duplicate removals, there is no need for this check anymore.
It will fail the following case:

[0,1,1,0]

After duplicate removal, j > i, there is no chance anymore to discover 1. Therefore (target == nums[l]) has to be done in while loop.
*/
class SolutionSearchRotatedSortedArray2 {
public:
	bool search(vector<int>& nums, int target) {
		if (true == nums.empty()) return false;
		int l = 0, r = (int)nums.size() - 1, m = 0, p;
		while (l < r && nums[l] == nums[r]) {
			if (target == nums[l]) return true;
			++l, --r;
		}
		p = nums[l];
		while (l <= r) {
			m = l + (r - l) / 2;
			if (target == nums[m]) return true;
			if ((nums[m] < p) ^ (target < p)) {
				if (target > nums[m]) r = m - 1;
				else l = m + 1;
			}
			else {
				if (target > nums[m]) l = m + 1;
				else r = m - 1;
			}
		}
		return false;
	}
	bool search1(const vector<int>& nums, int target) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		while (l < r && nums[l] == nums[r]) {
			if (target == nums[l]) return true;
			++l, --r;
		}
		while (l <= r) {
			m = l + (r - l) / 2;
			if (target == nums[m]) return true;
			if ((nums[m] < nums[0]) ^ (target < nums[0])) {
				if (target >= nums[l]) r = m - 1;
				else l = m + 1;
			}
			else {
				if (target > nums[m]) l = m + 1;
				else r = m - 1;
			}
		}
		return false;
	}
};
void TestSearchRotatedSortedArray2() {
	SolutionSearchRotatedSortedArray2 so;
	assert(true == so.search(vector<int>{1, 1, 3, 1}, 3));
	assert(true == so.search(vector<int>{1, 3, 1, 1, 1}, 3));
}
/*
Test cases:

[1,3,1,1,1]
3
[9,5,6,7,8,9,9,9,9,9,9]
8
[0,1,1,0]
1
[1,1,3,1]
3
[4,4,4,5,5,6,1,1,2,3,4,4]
4
[4,4,4,5,5,6,1,1,2,3,4,4]
5
[4,4,4,5,5,6,1,1,2,3,4,4]
6
[4,4,4,5,5,6,1,1,2,3,4,4]
1
[4,4,4,5,5,6,1,1,2,3,4,4]
2
[4,4,4,5,5,6,1,1,2,3,4,4]
7

Outputs:

true
true
true
true
true
true
true
true
true
false
*/