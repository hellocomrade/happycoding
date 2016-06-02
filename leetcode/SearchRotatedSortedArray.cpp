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
non-rotated sorted array as well. In this case, the first section's length is 0
*/
class SolutionSearchRotatedSortedArray {
public:
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
	int search2(const const vector<int>& nums, int target) {
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
	int search(const vector<int>& nums, int target)
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