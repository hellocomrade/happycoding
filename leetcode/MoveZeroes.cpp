#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/move-zeroes/
/*
283. Move Zeroes

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]

Output: [1,3,12,0,0]

Note:

- You must do this in-place without making a copy of the array.
- Minimize the total number of operations.

Observations:

In-place in such a situation almost always means two-pointers. Like other "Easy" problems, there is an ad-hoc catch. If you
figure it out, problem solved. Otherwise, it's not easy at all...

The idea is: moving non-zero elements to the left if there is any zero and then back fill zero at the end of the array.
			 No worry on overwriting since every non-zero element moving to the left. Their relative positions will not
			 be changed if moving sequentially.

With two pointers: one for looping the array, the other one is for marking the insertion index for the next non-zero element.
Variable insertPos (the second pointer) only increases if current element pointed by variable i (the first pointer) is non-zero.
This means:
- If nums[i] is zero, bypass it. It's bucket will be overwritten by follownig non-zero element if there is any;
- If nums[i] is non-zero, move it to the position pointed by insertPos.

In other words, insertPos is measured in a way that only non-zero elements are counted. The new array built in place then.

After that, back fill zero from insertPos till the end of the array. In case there is no zero at all, every element is "moved"
to its original place. In this case, insertPos ends up at len(nums). No back fill is needed.
*/
class SolutionMoveZeroes {
public:
	void moveZeroes(vector<int>& nums) {
		int len = (int)nums.size(), insertPos = 0;
		for (int i = 0; i < len; ++i)
			if (0 != nums[i]) nums[insertPos++] = nums[i];
		std::fill(nums.begin() + insertPos, nums.end(), 0);
	}
};
/*
Test cases:

[0,1,0,3,12]
[]
[1]
[0]
[1,2,3,4]
[0,0,1]
[1,0]

Outputs:

[1,3,12,0,0]
[]
[1]
[0]
[1,2,3,4]
[1,0,0]
[1,0]
*/