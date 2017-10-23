#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/max-area-of-island/
/*
695. Max Area of Island

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

Example 1:
[[0,0,1,0,0,0,0,1,0,0,0,0,0],
[0,0,0,0,0,0,0,1,1,1,0,0,0],
[0,1,1,0,1,0,0,0,0,0,0,0,0],
[0,1,0,0,1,1,0,0,1,0,1,0,0],
[0,1,0,0,1,1,0,0,1,1,1,0,0],
[0,0,0,0,0,0,0,0,0,0,1,0,0],
[0,0,0,0,0,0,0,1,1,1,0,0,0],
[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
Example 2:
[[0,0,0,0,0,0,0,0]]
Given the above grid, return 0.
Note: The length of each dimension in the given grid does not exceed 50.

Observations:
I am comfortable with DFS and mark visited cell so there won't be double count.

Greedy through DFS.
*/
class SolutionMaxAreaOfIsland {
private:
	int _aux(vector<vector<int>>& grid, int i, int j, int rcnt, int ccnt) {
		if (i < 0 || i > rcnt - 1 || j < 0 || j > ccnt - 1 || 0 == grid[i][j])return 0;
		grid[i][j] = 0;
		return 1 + _aux(grid, i - 1, j, rcnt, ccnt) + _aux(grid, i + 1, j, rcnt, ccnt) + _aux(grid, i, j + 1, rcnt, ccnt) + _aux(grid, i, j - 1, rcnt, ccnt);
	}
public:
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		int rcnt = grid.size(), ccnt = grid[0].size(), ans = 0;
		for (int i = 0; i < rcnt; ++i)
			for (int j = 0; j < ccnt; ++j)
				ans = std::max(ans, _aux(grid, i, j, rcnt, ccnt));
		return ans;
	}
};
