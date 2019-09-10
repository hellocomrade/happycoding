#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/burst-balloons
/*
312. Burst Balloons

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons.
If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

- You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
- 0 <= n <= 500, 0 <= nums[i] <= 100

Example:

Input: [3,1,5,8]

Output: 167

Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []

			 coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

Observations:

This should be either DP or BT and since it only asks for the max value, usually that's a sign of DP.

However, I failed to compose a solution using DP. I can kind of figuring out the sub-problem and tell that
bottom-up DP should be a good fit for this. But I fell into the trap trying to solve this using combination of
digits.

By browsing the solutions in discussion section, I can tell this problem using some unusual tricks that have
been seen in others:

1. Using a 2D array memo[i][j] to store max value in range of [i, j], which can be found in leetcode 5 (Longest Palindromic Substring);
2. Think backward instead of forward, which can be found in leetcode 174 (Dungeon Game);

The idea is: a 2D array memo[i][j] is used to store the max coins from range [i, j] in given nums. Starting
from 1 ballon only, memo[1][1], memo[2][2], ... till memo[1][len], which should have the max coins for the problem.

We will have to introduce two dummy elements 1 and patch them to the beginning and end of nums. This change
makes the index range from [0, len(nums) - 1] to [1, len(nums)]

Before moving forward, a mist has to be cleared: when we say memo[2][2], it appears to be only involved one element in nums. However,
based upon the description of the problem: nums[left] * nums[i] * nums[right], in order to calculate memo[2][2], both
nums[1] and nums[3] will be involved: memo[2][2] = nums[1] * nums[2] * nums[3]. For the edge case memo[1][1],
memo[1][1] = nums[0] * nums[1] * nums[2], nums[0] = 1 is the dummy element prepended onto nums before hand.

By using bottom-up DP, we start with len = 1 till len = len(nums). We will examine every [i, j] that the length is len.
for DP part, given any [i, j], the naive idea is: finding all possibilities of balloon bursting in range of [i, j].
Starting with k in [i, j], split [i, j] into [i, k - 1] and [k + 1, j]. Then pick the next ones in [i, k - 1] and [k + 1, j].
This sounds great but no easy way to implment this and take advantage of pre-calculated memo unless we try all combinations in nums
coz any element can be picked and leaves the remaining elements forming a new sequence.

Now, we can go to the fun part, which has been well discussed here:

https://leetcode.com/problems/burst-balloons/discuss/76229/For-anyone-that-is-still-confused-after-reading-all-kinds-of-explanations...

"This transition function basically says in order to get the maximum value we can get for bursting all the balloons between [ i , j] , we just loop through each balloon between these two indexes and make them to be the last balloon to be burst,"

for (int k = i; k <= j; ++k)
	memo[i][j] = std::max(memo[i][j], nums[k] * nums[i - 1] * nums[j + 1] + memo[i][k - 1] + memo[k + 1][j]);

Instead of picking from the first balloon in [i, j], picking k in [i, j] as the last ballon, the coins gained
for that is nums[k] * nums[i - 1] * nums[j + 1], the previous balloon burst should have memo[i][k - 1] + memo[k + 1][j].

By doing so, we don't have to worry about element combinations if we start from picking the first balloon...
*/
class SolutionBurstBallons {
public:
	int maxCoins(vector<int>& nums) {
		int len = (int)nums.size(), l = 0;
		nums.push_back(1);
		nums.insert(nums.begin(), 1);
		vector<vector<int>> memo(len + 2, vector<int>(len + 2, 0));
		while (++l <= len) {
			for (int i = 1, j = i + l - 1; j <= len && i <= len; j = ++i + l - 1)
				for (int k = i; k <= j; ++k)
					memo[i][j] = std::max(memo[i][j], nums[k] * nums[i - 1] * nums[j + 1] + memo[i][k - 1] + memo[k + 1][j]);
		}
		return memo[1][len];
	}
};
/*
Test cases:

[3,1,5,8]
[]
[1]
[2,3]
[2,3,1,5,0,2,7,8,12,9,0,0,1]

Outputs:

167
0
1
9
2053
*/