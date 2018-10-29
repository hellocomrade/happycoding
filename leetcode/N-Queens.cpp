#include <cassert>
#include <string>
#include <vector>

using namespace std;

//https://leetcode.com/problems/n-queens/
/*
51. N-Queens

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

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
I don't know chess, so had to do a bit research on rules for Queen. Quenn can attack any enemy on the same row, same column
or same diagonals (2 of them, if Queen is not on any edge). According to wiki:

https://en.wikipedia.org/wiki/Eight_queens_puzzle

"The eight queens puzzle is the problem of placing eight chess queens on an 8×8 chessboard so that no two queens threaten each other. Thus, a solution requires that no two queens share the same row, column, or diagonal. The eight queens puzzle is an example of the more general n queens problem of placing n non-attacking queens on an n×n chessboard, for which solutions exist for all natural numbers n with the exception of n=2 and n=3."

It sounds like backtracing fits the logic best! So be it! Here is the intuitive solution:
We put Queen on every position at each row, then move to the next row, try any position on the second row that
will not break the rules defined above. The implicit rule we apply automatically is no Queens on the same row
since we only place a Queen on each row.

Recursion is of course applied since we do backtracing.

The first version runs 12 ms on Leetcode, take a closer look: we could actually combine 3 for loops together in
a single loop, which will potentially boost the performance by 3 times. So came with the second version. But,
the first version is still more understandable. Please refer to the inline comments in aux1.

***Update on 2018-10-29***

solveNQueens0 is a little bit better implementation comparing with aux. The difference is in the for-loop for validating
queens positions:

By nature, both implementations (DFS BT) guarantee the uniqueness of queen on each row. Therefore, only column and two
diagonals need to be checke, up to current row (row index: rowIdx)

for (j = 0; j < rowIdx && '.' == memo[j][i]; ++j) {
if (i - j - 1 > -1 && '.' != memo[rowIdx - j - 1][i - j - 1]) break;
if (i + j + 1 < n && '.' != memo[rowIdx - j - 1][i + j + 1]) break;
}
if (j < rowIdx) continue;

Instead of using three boolean flags and checking their status after the loop, the loop will break immediately if either diagonal check
fails. After the loop, simply checking if j has reached rowIdx will do.

The biggest issue about this implementation is that checking the validity of putting a queen at current cell will have to examine all
related cells (same column, same diagonals) above current row. This will take O(N^3) time. Is there a way that the check can be done
in O(1) without breaking the essense of backtracing?

solveNQueens is such an implementation. It achieves the goal by tracking all columns, diagonals on a N by N grid. One may laugh: wait, does it
look exactly like vector<string> memo(n, string(n, '.')) in solveNQueens0, since it covers N by N grid completely? Well, not exactly.
At any given cell [i, j], one may care only if there is a quene on column[j] or 2 diagonals rooted from [i, j] and go up (as long as in the grid).
Tracking here means if column[j] is occupied already. Therefore, only N space is needed for column tracking. How many diagonals on a N by N grid?
There are (2N - 1) diagonals each direction (45 degree/ 135 degree).

Another concern one may have is: will maintaining these status trackers break the backtracing? Not at all, it exactly fits into BT!
Each tracker only has 2 status and due to the nature of DFS, they can be turned on and off at each iteration during recursion without breaking
anything what so ever.

Now, we have a O(N^2) time solution without sacrificing too much on space, still O(N^2) space.

In terms of mapping between cell index [i, j] to trackers respectively, it's very straightforward for column trackers, j.
As for two diagonals, if one considers the column-base as the X-axis, the 45 degree diagonals (top-left 0 based) has the following mapping
between diagonal and cell on a 4 by 4 grid:

0: [0, 0]
1: [0, 1], [1, 0]
2: [0, 2], [1, 1], [2, 0]
3: [0, 3], [1, 2], [2, 1], [3, 0]
... ...

It's not hard to figure out the mapping from cell indexes to diagonal index is: (i + j)

the 135 degree diagonals (bottom-left 0 based), on the other hand, on a 4 by 4 grid:

0: [3, 0]
1: [3, 1], [2, 0]
2: [3, 2], [2, 1], [1, 0]
3: [3, 3], [2, 2], [1, 1], [0, 0]

It may take a bit time, but eventually, one can figure the mapping is: (n - 1 - i + j)
*/
class SolutionNQueens {
private:
	//8ms
	void aux(vector<vector<string>> &ans, vector<string> &vec, int idx, int n) {
		if (idx == n) {
			ans.push_back(vector<string>(vec));
			return;
		}
		for (int i = 0; i < n; ++i) {
			if (idx > 0) {
				bool bj = false, bk = false, bl = false;
				for (int j = i - 1, k = i + 1, l = idx - 1;l >= 0; --j, ++k, --l) {
					if (j >= 0 && vec[l][j] == 'Q') {
						bj = true;
						break;
					}
					if (k < n && vec[l][k] == 'Q') {
						bk = true;
						break;
					}
					if (vec[l][i] == 'Q') {
						bl = true;
						break;
					}
				}
				if (bj || bk || bl)continue;
			}
			vec[idx][i] = 'Q';
			this->aux(ans, vec, idx + 1, n);
			vec[idx][i] = '.';
		}
	}
	//12ms
	void aux1(vector<vector<string>> &ans, vector<string> &vec, int idx, int n) {
		if (idx == n) {//if we reach here, we have a valid solution
			ans.push_back(vector<string>(vec));
			return;
		}
		for (int i = 0; i < n; ++i) {
			if (idx > 0) { //we allow Queen to be placed on any position on row 0, no check if idx == 0
				int j, k;
				//Check backward diagnal
				for (j = i - 1, k = idx - 1; j >= 0 && k >= 0; --j, --k)
					if (vec[k][j] == 'Q')break;
				//If the exit of loop by the break? k >= 0 means we still have rows to check,
				//if this is the case and j != -1, we have a conflict
				if (j != -1 && k >= 0)continue;
				//Check forward diagnal
				for (j = i + 1, k = idx - 1; j < n && k >= 0; ++j, --k)
					if (vec[k][j] == 'Q')break;
				//If the exit of loop by the break? k >= 0 means we still have rows to check,
				//if this is the case and j != n, we have a conflict
				if (j != n && k >= 0)continue;
				//Check same column
				for (j = 0; j < idx; ++j)
					if (vec[j][i] == 'Q')break;
				//If the exit of loop by the break? k >= 0 means we still have rows to check so a conflict it is
				if (j < idx)continue;
			}
			//We are OK to put 'Q' at row idx with column index i
			vec[idx][i] = 'Q';
			this->aux1(ans, vec, idx + 1, n);
			//reset, bracktracing
			vec[idx][i] = '.';
		}
	}
public:
	//4ms
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> ans;
		vector<string> memo(n, string(n, '.'));
		vector<bool> col(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
		auto bt = [&ans, &memo, &col, &diag1, &diag2, n](int rowIdx, const auto& fun) {
			if (rowIdx == n) {
				ans.push_back(memo);
				return;
			}
			for (int i = 0; i < n; ++i) {
				if (true == col[i] || true == diag1[rowIdx + i] || true == diag2[n - 1 - rowIdx + i]) continue;
				col[i] = diag1[rowIdx + i] = diag2[n - 1 - rowIdx + i] = true;
				memo[rowIdx][i] = 'Q';
				fun(rowIdx + 1, fun);
				memo[rowIdx][i] = '.';
				col[i] = diag1[rowIdx + i] = diag2[n - 1 - rowIdx + i] = false;
			}
		};
		bt(0, bt);
		return ans;
	}
	//4ms
	vector<vector<string>> solveNQueens0(int n) {
		vector<vector<string>> ans;
		vector<string> memo(n, string(n, '.'));
		auto bt = [&ans, &memo, n](int rowIdx, const auto& fun) {
			if (rowIdx == n) {
				ans.push_back(memo);
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
	/**
	* Get all distinct N-Queen solutions
	* @param n: The number of queens
	* @return: All distinct solutions
	* For example, A string '...Q' shows a queen on forth position
	*/
	vector<vector<string> > solveNQueens1(int n) {
		vector<vector<string>> ans = vector<vector<string>>();
		if (n > 0) {
			//Each string with n characters and acts like a row.
			vector<string> vec(n, string(n, '.'));
			this->aux(ans, vec, 0, n);
		}
		return ans;
	}
};
void TestNQueens() {
	SolutionNQueens so;
	vector<vector<string>> ans1 = so.solveNQueens(1);
	assert(1 == ans1.size());
	vector<vector<string>> ans2 = so.solveNQueens(2);
	assert(0 == ans2.size());
	vector<vector<string>> ans3 = so.solveNQueens(3);
	assert(0 == ans3.size());
	vector<vector<string>> ans5 = so.solveNQueens(5);
	assert(10 == ans5.size());
	vector<vector<string>> ans8 = so.solveNQueens(8);
	assert(92 == ans8.size());
}