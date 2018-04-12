#include <algorithm>
#include <vector>

//https://leetcode.com/problems/jump-game/
/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

A = [2,0,0], return true.

A = [0,1], return false.

Observation:
Kind of greedy, not DP for sure. Always pick the largest possible moves at each step.
Current move is consumed at each step by 1 and then compare with the available move at index i, the larger
one will be set as the current move.

Update on 4/12/2018:

- Test cases don't allow empty array

- If you do DP, you will get stack overflow or TLE:

https://leetcode.com/problems/jump-game/solution/
*/
class SolutionJumpGame {
public:
	bool canJump(std::vector<int>& nums) {
		int len = (int)nums.size(), nextMax = 0;
		for (int i = 0;i < len; ++i) {
			if (i > 0 && i > nextMax) return false;
			nextMax = std::max(nextMax, i + nums[i]);
		}
		return true;
	}
	bool canJump1(std::vector<int>& nums) {
		int len = nums.size();
		if (0 == len)return false;
		if (1 == len)return true;
		if (0 == nums[0])return false;
		int move = nums[0];
		//we have an ealier break condition: if remaining move is enough to reach the last index
		//directly, no need to loop anymore
		for (int i = 1; i < len && move < len - i; ++i)
		{
			move = std::max(move - 1, nums[i]);
			if (0 == move && i != len - 1)return false;
		}
		return true;
	}
};