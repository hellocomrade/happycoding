#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/wiggle-sort-ii/
/*
324. Wiggle Sort II

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

Input: nums = [1, 5, 1, 1, 6, 4]

Output: One possible answer is [1, 4, 1, 5, 1, 6].

Example 2:

Input: nums = [1, 3, 2, 2, 3, 1]

Output: One possible answer is [2, 3, 1, 3, 1, 2].

Note:

You may assume all input has valid answer.

Follow Up:

Can you do it in O(n) time and/or in-place with O(1) extra space?

Observations:

This is an interesting question that can be actually used to examine/practice multiple classic algorithms.

Naive solution will require sorting the given array first then interleave smaller section (including median value)
with greater section of the array. However, if the median value in the array has duplicates, interleaving could fail.

[1,2,2,3] can be wiggled into [2, 3, 1 ,2]; however by split the array into [1, 2] and [2, 3], interleaving
them will lead to [1, 2, 2, 3], which is wrong!

A trick has to play here: interleaving from the right to left: like [2, 1] and [3, 2], which leads to [2, 3, 1, 2].

This is a kind of trick mainly depending on instinct plus experience. If you get it, you have it...

For such as a naive implementation, overall time complexity is O(NlogN) due to sorting plus O(N) space for interleaved
result.

In fact, there is no need to have a fully sorted array since the only value we really care is median. As long median
is set, the order in smaller section subarray and larger section subarray is irrelevant. Of course, the duplicate
on median still needs to be dealt with.

If Nth smallest number algorithm is applied here, median can be found in O(N). Fortunately C++ offers
nth_element that exactly meets our need! However, it has a flaw: nth_element or any Nth smallest number
algorithm based upon quick-select can only guarantee that " none of the elements preceding nth are greater than it,
and none of the elements following it are less.". For our purpose, we prefer to have median along with all
its dupliates are in order, in other words: they stay in the middle of the array. Still, we are looking for
an algorithm that can partially sorting on median value only and the preferred time complexity is O(N).

Is it doable? Yes, three-way-partitioning. See leetcode 75 (Sort Colors) or at:

https://en.wikipedia.org/wiki/Dutch_national_flag_problem#Pseudocode

It's a linear algorithm to categorize numbers in 3 groups based upon the group value in the middle.

After 3-way-partitioning, interleaving the array is straightforward.

Now, we have a linear algorithm for wiggle sort using extra O(N) space.

In order to meet O(1) space in follow-up, some genius figured out "virtual-indexing":

https://leetcode.com/problems/wiggle-sort-ii/discuss/77677/O(n)%2BO(1)-after-median-Virtual-Indexing

I don't think I can do it during an interview, can you?
*/
class SolutionWiggleSort2 {
public:
	void wiggleSort(vector<int>& nums) {
		int len = (int)nums.size(), i = (len - 1) / 2, j = len - 1, m = 0, l = 0, r = len - 1, mi = 0;
		if (1 > len) return;
		vector<int> vec(nums.begin(), nums.end());
		std::nth_element(vec.begin(), vec.begin() + i, vec.end());
		m = vec[i];
		while (mi <= r) {
			if (m > vec[mi]) std::swap(vec[l++], vec[mi++]);
			else if (m < vec[mi]) std::swap(vec[r--], vec[mi]);
			else ++mi;
		}
		for (int k = 0; k < len; ++k)
			nums[k] = (0 == (k & 1)) ? vec[i--] : vec[j--];
	}
};
/*
Test cases:

[1,5,1,1,6,4]
[1,3,2,2,3,1]
[]
[1]
[1,2]
[2,1]
[1,2,3]
[5,6,5,6,4,6,5,5]

Outputs:

[1,4,1,5,1,6]
[2,3,1,3,1,2]
[]
[1]
[1,2]
[1,2]
[2,3,1]
[5,6,5,6,5,6,4,5]
*/