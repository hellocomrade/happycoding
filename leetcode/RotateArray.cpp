#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

//https://leetcode.com/problems/rotate-array/
/*
189. Rotate Array

Given an array, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: [1,2,3,4,5,6,7] and k = 3

Output: [5,6,7,1,2,3,4]

Explanation:

rotate 1 steps to the right: [7,1,2,3,4,5,6]

rotate 2 steps to the right: [6,7,1,2,3,4,5]

rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: [-1,-100,3,99] and k = 2

Output: [3,99,-1,-100]

Explanation:

rotate 1 steps to the right: [99,-1,-100,3]

rotate 2 steps to the right: [3,99,-1,-100]

Note:
- Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
- Could you do it in-place with O(1) extra space?

Observations:

Old school, classic solution takes a "hand-waving" apporach. Since it's moving to right by k steps,

1. First reversing the order of the last k elements in nums;
2. Then reversing the order of the remaining elements from beginning of nums;
3. Finally reversing the entir nums;

Of course, for the cases k >= len(nums), one has to do k %= len(nums)

leetcode asks for at least 3 solutions: the most naive one would be: create a new array then copy over
each element to its new position after k moves. At last, overwrite nums with content in the new array.

The third solution, which can be found at: https://leetcode.com/problems/rotate-array/solution/
is based upon so called "Cyclic Replacement", which is a common trick to deal with array rearrangement problems
by shuffling an element around until it reaches its desired position.

That has been said, leetcode offical solution for it is not very elegant. The implementation in rotate1 looks better for me.

Starting from i = 0, nums[i] is swapped with nums[j], given j = (i + k) % len(nums). Then new nums[i] moves to j' = (j + k) % len(nums).
The cycling keeps going till the element should stay at nums[i] is found. Then moving to the next iteration.

The tricky part is the exit condition from for loop. How could we know that nums[j] is the element that has been re-positioned already without
using any aux storage? We don't. But, one can tell the moves should occur only len(nums) times. Therefore, the exit condition is when the counter
reaches len(nums).

Be aware: for each iteration in for loop, say there are N swaps happened, then there are actually N + 1 elements moved and put in the new positions.
*/
class SolutionRotateArray {
public:
	void rotate(vector<int>& nums, int k) {
		int len = (int)nums.size();
		if (1 > len || 0 == k) return;
		k %= len;
		std::reverse(nums.begin(), nums.end() - k);
		std::reverse(nums.end() - k, nums.end());
		std::reverse(nums.begin(), nums.end());
	}
	void rotate1(vector<int>& nums, int k) {
		int len = (int)nums.size();
		if (1 > len || 0 == k) return;
		for (int i = 0, j = (i + k) % len, cnt = 0; cnt < len; ++cnt, j = (++i + k) % len) {
			while (i != j) {
				std::swap(nums[i], nums[j]);
				j = (j + k) % len, ++cnt;
			}
		}
	}
};
/*
Test cases:
[1,2]
17
[1,2,3,4,5,6,7]
0
[1,2,3,4,5,6,7]
1
[1,2,3,4,5,6,7]
2
[1,2,3,4,5,6,7]
3
[1,2,3,4,5,6,7]
4
[1,2,3,4,5,6,7]
5
[1,2,3,4,5,6,7]
6
[1,2,3,4,5,6,7]
7
[1,2,3,4,5,6]
1
[1,2,3,4,5,6]
2
[1,2,3,4,5,6]
3
[1,2,3,4,5,6]
4
[1,2,3,4,5,6]
5
[1,2,3,4,5,6]
6
[1,2,3,4,5,6]
61
[-1,-100,3,99]
1
[-1,-100,3,99]
2
[-1,-100,3,99]
3
[-1,-100,3,99]
4
[-1,-100,3,99]
105
[-1,-100,3,99]
0
Outputs:
[2,1]
[1,2,3,4,5,6,7]
[7,1,2,3,4,5,6]
[6,7,1,2,3,4,5]
[5,6,7,1,2,3,4]
[4,5,6,7,1,2,3]
[3,4,5,6,7,1,2]
[2,3,4,5,6,7,1]
[1,2,3,4,5,6,7]
[6,1,2,3,4,5]
[5,6,1,2,3,4]
[4,5,6,1,2,3]
[3,4,5,6,1,2]
[2,3,4,5,6,1]
[1,2,3,4,5,6]
[6,1,2,3,4,5]
[99,-1,-100,3]
[3,99,-1,-100]
[-100,3,99,-1]
[-1,-100,3,99]
[99,-1,-100,3]
[-1,-100,3,99]
*/
