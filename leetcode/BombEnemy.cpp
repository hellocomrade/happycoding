#include <vector>
#include <algorithm>

using namespace std;

//https://www.lintcode.com/problem/bomb-enemy/description
/*
361. Bomb Enemy

Description
Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.

You can only put the bomb at an empty cell.

Example

Given a grid:

0 E 0 0
E 0 W E
0 E 0 0

return 3. (Placing a bomb at (1,1) kills 3 enemies)

Observations:

First of all, this is a problem at leetcode requiring subscription. I don't have it but lintcode offers the same problem for free.
I put this problem under the folder of leetcode simply for consistency.

The naive approach will search one row and one column for any given cell with '0'. If there are total K '0' in the matrix, this approach
results in O(KMN), given M is the row count and N is the column count of the matrix.

One can improve the performance by using memorization. Considering the following row:

0E0EE0W00EE

Before 'W' is reached all '0's left to the wall can kill 3 'E's and all '0's right to the wall can score 2 'E's. The same pattern can be
found for column as well. Therefore, if a memo[M][N] is given, one can scan the matrix first at row base to count number of 'E's for any '0'
in the same row using two pointers; Then, scan again at column base. The sum of 'E's from 2 scans for a given '0' is the total 'E' a bomb can
reach. One simply picks the max there. Overall time complexity O(MN), space complexity O(MN).

I have seen a better solution by cutting the space uage to O(N) through a more subtle scanning approach.
*/
class SolutionBombEnemy {
public:
	/**
	* @param grid: Given a 2D grid, each cell is either 'W', 'E' or '0'
	* @return: an integer, the maximum enemies you can kill using one bomb
	*/
	int maxKilledEnemies(vector<vector<char>> &grid) {
		if (true == grid.empty() || true == grid[0].empty()) return 0;
		int rcnt = grid.size(), ccnt = grid[0].size(), ans = 0;
		vector<vector<int>> memo(rcnt, vector<int>(ccnt, 0));
		for (int i = 0, cnt = 0; i < rcnt; cnt = 0, ++i)
			for (int j = 0, p = 0; j <= ccnt; ++j) {
				if (ccnt == j || 'W' == grid[i][j]) {
					for (int k = p; k < j; ++k) if ('0' == grid[i][k]) memo[i][k] = cnt;
					cnt = 0, p = j + 1;
				}
				else if ('E' == grid[i][j]) ++cnt;
			}
		for (int i = 0, cnt = 0; i < ccnt; cnt = 0, ++i)
			for (int j = 0, p = 0; j <= rcnt; ++j) {
				if (rcnt == j || 'W' == grid[j][i]) {
					for (int k = p; k < j; ++k)
						if ('0' == grid[k][i]) {
							memo[k][i] += cnt;
							ans = std::max(ans, memo[k][i]);
						}
					cnt = 0, p = j + 1;
				}
				else if ('E' == grid[j][i]) ++cnt;
			}
		return ans;
	}
};