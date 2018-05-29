#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/minimum-path-sum
/*
64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:

[
[1,3,1],
[1,5,1],
[4,2,1]
]

Output: 7

Explanation: Because the path 1→3→1→1→1 minimizes the sum.

Observations:

This is similar to leetcode 62. DP for sure. At each given index (i, k), we choose the MIN(memo[i - 1][k], memo[i][k - 1]) + grid[i][k] as the value.

This will require us to memorize at least the previous row, like minPathSum1 does.

Take a closer look that grid is not declared as const, so we can actually reuse the input vector grid by rewriting its values in a top down approach.
Therefore the space complexity is O(1).

Note that the elements at the first row and the first column shall be treated differently since their previous path comes from either left or top only.
*/
class SolutionMinimumPathSum {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int lenx = (int)grid.size();
		if (0 == lenx) return 0;
		int leny = (int)grid[0].size();
		if (0 == leny) return 0;
		for (int i = 0, k = 0; i < lenx; ++i)
			for (int j = 0; j < leny; ++j) {
				if (0 == i) k = (0 == j) ? 0 : grid[0][j - 1];
				else if (0 == j) k = grid[i - 1][0];
				else k = std::min(grid[i - 1][j], grid[i][j - 1]);
				grid[i][j] = k + grid[i][j];
			}
		return grid[lenx - 1][leny - 1];
	}
	int minPathSum1(vector<vector<int>>& grid) {
		int lenx = (int)grid.size();
		if (0 == lenx) return 0;
		int leny = (int)grid[0].size();
		if (0 == leny) return 0;
		vector<int> memo(leny + 1, 0);
		for (int i = 0; i < leny; ++i) memo[i + 1] += memo[i] + grid[0][i];
		for (int i = 1; i < lenx; ++i)
			for (int j = 0; j < leny; ++j)
				memo[j + 1] = (0 == j ? memo[j + 1] : std::min(memo[j + 1], memo[j])) + grid[i][j];
		return memo[leny];
	}
};