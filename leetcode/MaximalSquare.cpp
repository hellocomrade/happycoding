#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/maximal-square/
/*
221. Maximal Square

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4

Obserations:

This problem should be examined by DP first. My first attempt, maximalSquare1, works, but not perfect:
Using a rolling array with size len(matrix[0]), each cell is a vector with 3 elements. They are: the accumulated
'1' count on the row, the accumulated '1' count on the column, the accumulated '1' count on diagonal.

Diagonal count represents the size of square. It's decided by:

memo[j + 1][2] = '1' == matrix[i][j] ? std::min(d, std::min(memo[j][0], memo[j + 1][1])) + 1 : 0;

In other words, at cell [i, j], it's the smallest among column count, row count and diagonal count, which
guarantee forming the largest square with bottom right corner at [i, j].

Official solution though is simpler: https://leetcode.com/problems/maximal-square/solution/

Tracking on row and column counts are not necessary at all. memo[k] represents the linear size of the max
square end at [i, k] as bottom right corner. The above formula still works but with a different meaning:

memo[j + 1] = '1' == matrix[i][j] ? std::min(d, std::min(memo[j], memo[j + 1])) + 1 : 0;

It means the square size at [i, j] is decided by the smallest among the square ends at memo[j - 1] (current line, left),
memo[j] (previous line, top) and memo[j - 1] (previous line, diagonal, top left).
*/
class SolutionMaximalSquare {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int ans = 0, rlen = (int)matrix.size();
		if (1 > rlen) return ans;
		int clen = (int)matrix[0].size();
		vector<int> memo(clen + 1, 0);
		for (int i = 0; i < rlen; ++i)
			for (int j = 0, d = 0, t = 0; j < clen; ++j) {
				t = memo[j + 1];
				memo[j + 1] = '1' == matrix[i][j] ? std::min(d, std::min(memo[j], memo[j + 1])) + 1 : 0;
				ans = std::max(ans, memo[j + 1] * memo[j + 1]);
				d = t;
			}
		return ans;
	}
	int maximalSquare1(vector<vector<char>>& matrix) {
		int ans = 0, rlen = (int)matrix.size();
		if (1 > rlen) return ans;
		int clen = (int)matrix[0].size();
		vector<vector<int>> memo(clen + 1, vector<int> {0, 0, 0});
		for (int i = 0; i < rlen; ++i)
			for (int j = 0, d = 0, t = 0; j < clen; ++j) {
				t = memo[j + 1][2];
				memo[j + 1][2] = '1' == matrix[i][j] ? std::min(d, std::min(memo[j][0], memo[j + 1][1])) + 1 : 0;
				memo[j + 1][0] = '1' == matrix[i][j] ? memo[j][0] + 1 : 0;
				memo[j + 1][1] = '1' == matrix[i][j] ? memo[j + 1][1] + 1 : 0;
				ans = std::max(ans, memo[j + 1][2] * memo[j + 1][2]);
				d = t;
			}
		return ans;
	}
};
/*
Test cases:

[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
[["1"]]
[["0"]]
[["1","1"],["1","1"]]
[["1","0"],["1","1"]]
[["1","1","1"],["1","1","1"],["1","1","1"]]
[["1","0","0"],["0","1","0"],["0","0","1"]]
[["1","0","1","0","0"],["1","1","1","1","1"],["1","1","1","1","1"],["1","1","1","1","0"]]

Outputs:

4
1
0
4
1
9
1
9
*/