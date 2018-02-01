#include <vector>

using namespace std;

//https://leetcode.com/problems/number-of-islands/
/*
200. Number of Islands

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3

Observations:
DFS is always the safe choice by my experience. I recalled there is a similar question that you would fall into the trap if
you go with BFS. But, this one actually can be done by BFS.

Also, I should try Disjoint Set!

https://leetcode.com/problems/number-of-islands/solution/
*/
class SolutionNumberOfIslands {
private:
	void dfs(vector<vector<char>>& grid, int i, int j, int m, int n) {
		if (i < 0 || j < 0 || i > m || j > n || '0' == grid[i][j])return;
		grid[i][j] = '0';
		dfs(grid, i - 1, j, m, n), dfs(grid, i + 1, j, m, n), dfs(grid, i, j - 1, m, n), dfs(grid, i, j + 1, m, n);
	}
public:
	int numIslands(vector<vector<char>>& grid) {
		int ans = 0, m = (int)grid.size();
		if (m < 1)return ans;
		int n = (int)grid[0].size();
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)if ('1' == grid[i][j])this->dfs(grid, i, j, m - 1, n - 1), ++ans;
		return ans;
	}
};
/*
Test cases:
[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]
[["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]
[[]]
[]
[["1"]]
[["0"]]
[["0","0"],["0","1"]]
[["0","0"],["0","0"]]
[["1","0"],["0","1"]]
[["1","0"],["1","0"]]
[["1","0"],["1","1"]]

Results:
1
3
0
0
1
0
1
0
2
1
1
*/