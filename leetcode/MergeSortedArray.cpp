#include <vector>

using namespace std;

//https://leetcode.com/problems/merge-sorted-array/
/*
88. Merge Sorted Array

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:

- The number of elements initialized in nums1 and nums2 are m and n respectively.
- You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.

Example:

Input:

nums1 = [1,2,3,0,0,0], m = 3

nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]

Observations:

This is a subroutine for merge sort, which can be done in O(N) time and O(N) space.
However, for this specific question, it actually can be done using O(1) space given the fact
nums1 is with size of (m + n).

Since both nums1 and nums2 are sorted, the problem can be solved by adding the larger number
between nums1 and nums2 to the end of array nums1. One shall maintain three pointers.
i = m + n - 1, j = m - 1, k = n - 1. Obviously, j and k point to the end of nums1 (with values) and nums2,
i points to the end of the target nums1 (without value).

Worry about overwrite? Well, since all visited elements are relocated already, overwrite is not a concern at all.

Edge cases:

1. If k runs out before j, all elements remaining at the beginning of nums1 are at the right places already.
   Nothing needs to be done;
2. If the number of elements in nums1 is less than nums2, it's also possible j could run out before k. In that case,
   one shall keep adding remaining elements in nums2 to nums1 according to pointer i;

***Update on 2020-3-13***

This question was asked during a FB phone interview:

https://leetcode.com/discuss/interview-question/537801/facebook-phone-binary-tree-right-side-view-merge-sorted-array

The general idea is a 3-pointers solution, i, j, k, repspectively tracks from the end of nums1 (the real nums1 without filling 0),
the end of nums2 and the ends of nums1 (with filling 0). Then put element on the right place from right to left.

Other than the original solution, there is an alternative that is worth mention because it appears not needing
any extra variable. The idea is: since one of j and k will be decreased by 1 anyway, we could try to use j + k to
represent i. Moreover, we could use input arguments m and n. Therefor all i, j, k can be saved.

See code commented out below. One line version doesn't work because nums1[--m] : nums2[--n] will
be evaulated first and therefore left side [m + n - 1] will be shorter by 1...Took me a while to find this out...
*/
class SolutionMergeSortedArray {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int i = m + n - 1, j = m - 1, k = n - 1;
		while (i > -1 && k > -1)
			nums1[i--] = (j > -1 && nums1[j] >= nums2[k]) ? nums1[j--] : nums2[k--];
	}
	/*
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		while(m + n > 0 && n > 0) nums1[m + n - 1] = (m > 0 && nums1[m - 1] >= nums2[n - 1]) ? nums1[--m] : nums2[--n];
	}
	*/
	void merge0(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		while (0 < m + n && 0 < n) {
			if (0 < m && nums1[m - 1] >= nums2[n - 1]) nums1[m + n - 1] = nums1[m - 1], --m;
			else nums1[m + n - 1] = nums2[n - 1], --n;
		}
	}
};
/*
Test cases:

[1,2,3,0,0,0]
3
[2,5,6]
3
[1,3,5,7,0,0,0,0]
4
[2,4,6,8]
4
[1,4,6,8,0,0,0,0,0]
4
[2,3,5,7,9]
5
[1]
1
[]
0
[]
0
[]
0
[0]
0
[1]
1
[-1,0,0,3,3,3,0,0,0]
6
[1,2,2]
3
[2,0]
1
[1]
1

Outputs:

[1,2,2,3,5,6]
[1,2,3,4,5,6,7,8]
[1,2,3,4,5,6,7,8,9]
[1]
[]
[1]
[-1,0,0,1,2,2,3,3,3]
[1,2]
*/