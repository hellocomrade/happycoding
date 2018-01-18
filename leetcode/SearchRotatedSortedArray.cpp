#include <cassert>
#include <vector>
#include <limits>

using namespace std;

//https://leetcode.com/problems/search-in-rotated-sorted-array/
/*
33. Search in Rotated Sorted Array

Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Observations:

Rotated, sorted array:

[A -- B, C -- D] given  C < D < A < B

Take nums[0] as a reference to check which sides of the array we are at. Be aware, it could be a
non-rotated sorted array as well. In this case, the first section's length is 0.

A "smart" solution using Positive Infinity and Negative Infinity to tell which half should be dropped, search00
Consider a rotated array from a sorted array in ascending order. [A,B], A and B are two subarrays eacn of them is in order.

If target is searched against A but actually in range of B or vise versa, the middle value that target is supposed to
compare with will be set accordingly based upon the fact if target is in range:

- Target value is in range, then mid value is nums[mid], regular BS is conducted;

- Target value is on A but searched against B now, then mid value is Negative Infinity, when regular bS is conducted,
this arrangement will make l = mid + 1, moving toward B;

- Target value is on B but searched against A now, then mid value is Positive Infinity...

Whether target value is in range is desicded by:

(nums[m] < nums[0]) ^ (target < nums[0])

This is equavlent to (nums[m] < nums[0] && target > nums[0]) || (nums[m] > nums[0] && target < nums[0])

Since there is no duplicates in nums, the above condition guarantees the conclusion.

search0 was built using the same idea introduced above, however, it actually does the work in branches rather than using
the smart infinity idea. It looks pretty charming since when (nums[m] < nums[0]) ^ (target < nums[0]) is true, we simply
conduct BS in a reversed way. It looks elegant, but it's actually not coz you can rewrite it in function search:

Since we know target value is not in range and know which range target value belongs to, we can simply move toward
that direction and ignore the comparison between target value and mid value at all. This actually fits the logic of this
algorithm better and actually closer to search00. Note: we don't compare with nums[0] here, instead, we compare with nums[l].
*/
class SolutionSearchRotatedSortedArray {
public:
	int search(vector<int>& nums, int target) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		while (l <= r) {//cout << l << ',' << r << endl;
			m = l + (r - l) / 2;
			if (target == nums[m])return m;
			if ((nums[m] < nums[l]) ^ (target < nums[l])) {
				if (target >= nums[l])r = m - 1;
				else l = m + 1;
			}
			else {
				if (target > nums[m])l = m + 1;
				else r = m - 1;
			}
		}
		return -1;
	}
	int search0(vector<int>& nums, int target) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		while (l <= r) {//cout << l << ',' << r << endl;
			m = l + (r - l) / 2;
			if (target == nums[m])return m;
			if ((nums[m] >= nums[l]) ^ (target >= nums[l])) {
				if (target > nums[m])r = m - 1;
				else l = m + 1;
			}
			else {
				if (target > nums[m])l = m + 1;
				else r = m - 1;
			}
		}
		return -1;
	}
	int search00(vector<int>& nums, int target) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		long lb = numeric_limits<int>::min() - 1L, ub = numeric_limits<int>::max() + 1L, mval;
		while (l <= r) {
			m = l + (r - l) / 2;
			if ((nums[m] < nums[0]) ^ (target < nums[0]))mval = target < nums[0] ? lb : ub;
			else mval = nums[m];
			if (target == mval)return m;
			else if (target > mval)l = m + 1;
			else r = m - 1;
		}
		return -1;
	}
	//I am still not happy with this...
	int search000(vector<int>& nums, int target) {
		int len = (int)nums.size(), l = 0, r = len - 1, m = 0;
		while (l <= r) {//cout << l << ',' << r << endl;
			m = l + (r - l) / 2;
			if (target == nums[m])return m;
			if (nums[m] >= nums[l]) {
				if (target > nums[m] || (target < nums[m] && target < nums[l]))l = m + 1;
				else r = m - 1;
			}
			else {
				if (target > nums[m] && target <= nums[r])l = m + 1;
				else r = m - 1;
			}
		}
		return -1;
	}
	//first version, kind of easy to understand to me
	int search1(const vector<int>& A, int target) {
		int len = A.size();
		if (len < 1)return -1;
		int l = 1, h = len - 1, m = 0, f = A[0];
		if (target == f)return 0;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (A[m] == target)return m;
			else if (target > f)
			{
				if (f > A[m] || (f < A[m] && target < A[m]))
					h = m - 1;
				else if (f < A[m] && target > A[m])
					l = m + 1;
			}
			else
			{
				if (f < A[m] || (f > A[m] && target > A[m]))
					l = m + 1;
				else if (f > A[m] && target < A[m])
					h = m - 1;
			}
		}
		return -1;
	}
	//second version, a bit harder to swallow though, especially on the boundary cases involving
	//nums[0], you can make it easier by excluding nums[0] up front, see the next version.
	int search2(const vector<int>& nums, int target) {
		int len = nums.size();
		if (len < 1)return -1;
		int first = nums[0];
		int l = 0, h = len - 1, m = 0;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (nums[m] == target)return m;
			else if (nums[m] > target)
			{
				if (first <= nums[m] && target < first)
					l = m + 1;
				else
					h = m - 1;
			}
			else
			{
				if (first > nums[m] && target >= first)
					h = m - 1;
				else
					l = m + 1;
			}
		}
		return -1;
	}
	//nums[0] has been selected as the refernce, and target is compared with it up front
	//This eliminates the need for considering the boundary cases mentioned in search2
	int search3(const vector<int>& nums, int target) {
		int len = nums.size();
		if (len < 1)return -1;
		int first = nums[0];
		if (first == target)return 0;
		int l = 1, h = len - 1, m = 0;
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if (nums[m] == target)return m;
			else if (nums[m] > target)
			{
				if (first < nums[m] && target < first)
					l = m + 1;
				else
					h = m - 1;
			}
			else
			{
				if (first > nums[m] && target > first)
					h = m - 1;
				else
					l = m + 1;
			}
		}
		return -1;
	}
	/*
	This version conducts regular BS. This is fine if both target and mid are on the same side. If they
	are not, we will introduce fake +infinity and -infinity
	*/
	int search4(const vector<int>& nums, int target)
	{
		int len = nums.size();
		if (len < 1)return -1;
		int first = nums[0];
		if (first == target)return 0;
		int l = 1, h = len - 1, m = 0;
		long long mid = 0, up = numeric_limits<long long>::max(), down = numeric_limits<long long>::min();
		while (l <= h)
		{
			m = l + (h - l) / 2;
			if ((first < nums[m] && target > first) || (first > nums[m] && target < first))
				mid = nums[m];
			else if (target < first)
				mid = down;//-infinity, target is on the right side
			else
				mid = up;//infinity, target is on the left side
			if (mid == target)return m;
			else if (mid < target)
				l = m + 1;
			else
				h = m - 1;
		}
		return -1;
	}
};
void TestSearchRotatedSortedArray()
{
	SolutionSearchRotatedSortedArray so;
	assert(4 == so.search(vector<int>{4, 5, 6, 7, 0, 1, 2}, 0));
	assert(0 == so.search(vector<int>{4, 5, 6, 7, 0, 1, 2}, 4));
	assert(2 == so.search(vector<int>{4, 5, 6, 7, 0, 1, 2}, 6));
	assert(3 == so.search(vector<int>{4, 5, 6, 7, 0, 1, 2}, 7));
	assert(-1 == so.search(vector<int>{4, 5, 6, 7, 0, 1, 2}, 3));
	assert(-1 == so.search(vector<int>{4, 5, 6, 7, 0, 1, 2}, 8));

	assert(-1 == so.search(vector<int>{4}, 7));
	assert(-1 == so.search(vector<int>{4}, 0));
	assert(0 == so.search(vector<int>{4}, 4));

	assert(-1 == so.search(vector<int>{3, 4}, 7));
	assert(-1 == so.search(vector<int>{3, 4}, 0));
	assert(1 == so.search(vector<int>{3, 4}, 4));
	assert(0 == so.search(vector<int>{3, 4}, 3));

	assert(0 == so.search(vector<int>{4, 3}, 4));
	assert(1 == so.search(vector<int>{4, 3}, 3));

	assert(0 == so.search(vector<int>{5, 1, 3}, 5));
	assert(2 == so.search(vector<int>{5, 1, 3}, 3));

	assert(4 == so.search(vector<int>{4, 5, 6, 7, 0}, 0));
	assert(0 == so.search(vector<int>{4, 5, 6, 7, 0}, 4));

	assert(1 == so.search(vector<int>{8, 0, 1, 2, 3, 4}, 0));
	assert(2 == so.search(vector<int>{8, 0, 1, 2, 3, 4}, 1));
	assert(5 == so.search(vector<int>{8, 0, 1, 2, 3, 4}, 4));
}
