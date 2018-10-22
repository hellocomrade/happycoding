#include <vector>
#include <bitset>

using namespace std;

//https://leetcode.com/problems/sudoku-solver/
/*
37. Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

- Each of the digits 1-9 must occur exactly once in each row.
- Each of the digits 1-9 must occur exactly once in each column.
- Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
- Empty cells are indicated by the character '.'.

Note:

- The given board contain only digits 1-9 and the character '.'.
- You may assume that the given Sudoku puzzle will have a single unique solution.
- The given board size is always 9x9.

Observations:

If one had a warm up on leetcode 36 (Valid Sudoku), completing this would be much easier.
Since a single unique solution is guaranteed and the Sudoku must be completed,
Back tracing appears to the be best choice.

The question is the construction for the recursion so BT can proceed:

1. First, we populate the bitsets arrays (row-based, column-based and sector-based) for memorization and
pay attention on how this can be done in one loop, especially for sector-based indexing: (j / 3 + i / 3 * 3)
2. During back tracing, all 81 cells will be looked at. Therefore, a counter is sufficient. i and j can always
be extracted by i = counter / 9, j = counter % 9.
3. When a cell is examined, the following situation can be met:
- Counter is greater than 80, which means all cells have been examined, the unique solution has been found, return true;
- Cell has a pre-populated value, it will depends on the next cell's result to decide if current BT operation is valid.
Therefore, return BT on counter + 1;
- Cell is empty, try all possible numbers based upon the status of current memorization arrays. True is returned if and only
if BT on counter + 1 is true;
- If the end of the funtion is reached, reset current cell to empty, no possible solution can be found using current BT arrangement, return False;
*/
class SolutionSudokuSolver {
public:
	void solveSudoku(vector<vector<char>>& board) {
		vector<bitset<9>> rowmap(9), colmap(9), secmap(9);
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j) {
				if ('.' == board[i][j]) continue;
				rowmap[i].set(board[i][j] - '1'), colmap[j].set(board[i][j] - '1'), secmap[j / 3 + i / 3 * 3].set(board[i][j] - '1');
			}
		auto bt = [&](int cnt, const auto& fun) -> bool {
			int i = cnt / 9, j = cnt % 9;
			if (80 < cnt) return true;
			else if ('.' != board[i][j]) return fun(cnt + 1, fun);
			for (int k = 0; k < 9; ++k)
				if (false == rowmap[i].test(k) && false == colmap[j].test(k) && false == secmap[j / 3 + i / 3 * 3].test(k)) {
					board[i][j] = k + '1';
					rowmap[i].set(k), colmap[j].set(k), secmap[j / 3 + i / 3 * 3].set(k);//cout << i<<','<<j<<','<<k+1<<endl;
					if (true == fun(cnt + 1, fun)) return true;
					rowmap[i].set(k, 0), colmap[j].set(k, 0), secmap[j / 3 + i / 3 * 3].set(k, 0);
				}
			board[i][j] = '.';
			return false;
		};
		bt(0, bt);
	}
};