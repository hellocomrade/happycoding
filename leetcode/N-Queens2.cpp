#include <string>
#include <vector>

using namespace std;

//https://leetcode.com/problems/n-queens-ii/
/*
52. N-Queens II

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.

Example:

Input: 4

Output: 2

Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.

[
[".Q..",  // Solution 1
"...Q",
"Q...",
"..Q."],

["..Q.",  // Solution 2
"Q...",
"...Q",
".Q.."]
]

Observations:

This question only asks the number of valid solutions, not solutions themselves. Ususally, it means an algorithm
better than backtracing, say DP. But for this particular one, it appears the algorithm using 3 tracking arrays in
leetcode 51 (N-Queens) is the best solution for this so far.

O(N!) time and O(N) space.

The algorithm using the exactly same implementation in leetcode 51 is given in totalNQueens1, which is slower
due to the O(N) checking inside the loop.
*/
class SolutionNQueens2 {
public:
	//0ms
	int totalNQueens(int n) {
		int ans = 0;
		vector<bool> col(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
		auto bt = [&ans, &col, &diag1, &diag2, n](int rowIdx, const auto& fun) {
			if (rowIdx == n) {
				++ans;
				return;
			}
			for (int i = 0; i < n; ++i) {
				if (true == col[i] || true == diag1[rowIdx + i] || true == diag2[n - 1 - rowIdx + i]) continue;
				col[i] = diag1[rowIdx + i] = diag2[n - 1 - rowIdx + i] = true;
				fun(rowIdx + 1, fun);
				col[i] = diag1[rowIdx + i] = diag2[n - 1 - rowIdx + i] = false;
			}
		};
		bt(0, bt);
		return ans;
	}
	//4ms
	int totalNQueens1(int n) {
		int ans = 0;
		vector<string> memo(n, string(n, '.'));
		auto bt = [&ans, &memo, n](int rowIdx, const auto& fun) {
			if (rowIdx == n) {
				++ans;
				return;
			}
			for (int i = 0, j = 0; i < n; ++i) {
				for (j = 0; j < rowIdx && '.' == memo[j][i]; ++j) {
					if (i - j - 1 > -1 && '.' != memo[rowIdx - j - 1][i - j - 1]) break;
					if (i + j + 1 < n && '.' != memo[rowIdx - j - 1][i + j + 1]) break;
				}
				if (j < rowIdx) continue;
				memo[rowIdx][i] = 'Q';
				fun(rowIdx + 1, fun);
				memo[rowIdx][i] = '.';
			}
		};
		bt(0, bt);
		return ans;
	}
};