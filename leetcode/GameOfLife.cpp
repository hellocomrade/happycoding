#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/game-of-life/
/*
289. Game of Life

According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised
by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its
eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

- Any live cell with fewer than two live neighbors dies, as if caused by under-population.
- Any live cell with two or three live neighbors lives on to the next generation.
- Any live cell with more than three live neighbors dies, as if by over-population..
- Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

Write a function to compute the next state (after one update) of the board given its current state.
The next state is created by applying the above rules simultaneously to every cell in the current state,
where births and deaths occur simultaneously.

Example:

Input:

[
  [0,1,0],
  [0,0,1],
  [1,1,1],
  [0,0,0]
]

Output:

[
  [0,0,0],
  [1,0,1],
  [0,1,1],
  [0,1,0]
]

Follow up:

- Could you solve it in-place? Remember that the board needs to be updated at the same time:
  You cannot update some cells first and then use their updated values to update other cells.
- In this question, we represent the board using a 2D array. In principle, the board is infinite,
  which would cause problems when the active area encroaches the border of the array. How would you address
  these problems?

Observations:

This is a straight forward problem as long as you had experience before on how to reuse the input array to
keep the necessary info along with the result in each cell. Fancier version will probably use bitwise operation
to track status. As for the flip cases, 2 is used for "0 to 1" and -1 is for "1 to 0".

Another trick part is to figure out how to visit the surrounding cells safely when the central cell is on the boundary.
gameOfLife1 is my naive version, which simply iterates all 8 cases. Or, you could do:

for (int m = std::max(i - 1, 0); m < std::min(i + 2, rowCnt); ++m)
	for (int n = std::max(j - 1, 0); n < std::min(j + 2, colCnt); ++n)

Using max and min to make sure no out of bound error. See gameOfLife.
*/
class SolutionGameOfLife {
public:
	void gameOfLife(vector<vector<int>>& board) {
		int rowCnt = board.size();
		if (1 > rowCnt) return;
		int colCnt = board[0].size();
		if (1 > colCnt) return;
		for (int i = 0; i < rowCnt; ++i)
			for (int j = 0, cnt = 0; j < colCnt; cnt = 0, ++j) {
				for (int m = std::max(i - 1, 0); m < std::min(i + 2, rowCnt); ++m)
					for (int n = std::max(j - 1, 0); n < std::min(j + 2, colCnt); ++n)
						cnt += (1 == std::abs(board[m][n])) ? 1 : 0;
				if (1 == board[i][j]) --cnt;
				if ((2 > cnt || 3 < cnt) && 1 == board[i][j]) board[i][j] = -1;
				if (3 == cnt && 0 == board[i][j]) board[i][j] = 2;
			}
		for (int i = 0; i < rowCnt; ++i)
			for (int j = 0, cnt = 0; j < colCnt; cnt = 0, ++j)
				if (2 == board[i][j]) board[i][j] = 1;
				else if (-1 == board[i][j]) board[i][j] = 0;
	}
	void gameOfLife1(vector<vector<int>>& board) {
		int rowCnt = board.size();
		if (1 > rowCnt) return;
		int colCnt = board[0].size();
		if (1 > colCnt) return;
		for (int i = 0; i < rowCnt; ++i)
			for (int j = 0, cnt = 0; j < colCnt; cnt = 0, ++j) {
				if (-1 < i - 1 && -1 < j - 1) cnt += (1 == board[i - 1][j - 1] || -1 == board[i - 1][j - 1]) ? 1 : 0;
				if (-1 < i - 1 && colCnt > j + 1) cnt += (1 == board[i - 1][j + 1] || -1 == board[i - 1][j + 1]) ? 1 : 0;
				if (-1 < i - 1) cnt += (1 == board[i - 1][j] || -1 == board[i - 1][j]) ? 1 : 0;
				if (rowCnt > i + 1 && -1 < j - 1) cnt += (1 == board[i + 1][j - 1] || -1 == board[i + 1][j - 1]) ? 1 : 0;
				if (rowCnt > i + 1 && colCnt > j + 1) cnt += (1 == board[i + 1][j + 1] || -1 == board[i + 1][j + 1]) ? 1 : 0;
				if (rowCnt > i + 1) cnt += (1 == board[i + 1][j] || -1 == board[i + 1][j]) ? 1 : 0;
				if (-1 < j - 1) cnt += (1 == board[i][j - 1] || -1 == board[i][j - 1]) ? 1 : 0;
				if (colCnt > j + 1) cnt += (1 == board[i][j + 1] || -1 == board[i][j + 1]) ? 1 : 0;
				if (2 > cnt && 1 == board[i][j]) board[i][j] = -1;
				if (3 < cnt && 1 == board[i][j]) board[i][j] = -1;
				if (3 == cnt && 0 == board[i][j]) board[i][j] = 2;
			}
		for (int i = 0; i < rowCnt; ++i)
			for (int j = 0, cnt = 0; j < colCnt; cnt = 0, ++j)
				if (2 == board[i][j]) board[i][j] = 1;
				else if (-1 == board[i][j]) board[i][j] = 0;
	}
};
/*
Test cases:

[[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
[]
[[1]]
[[0]]
[[1,1]]
[[0,1,0]]
[[1,1,1,0],[0,0,1,1],[1,1,1,1],[1,0,1,0]]
[[1,0,0],[1,1,1],[0,1,1]]

Outputs:

[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
[]
[[0]]
[[0]]
[[0,0]]
[[0,0,0]]
[[0,1,1,1],[0,0,0,0],[1,0,0,0],[1,0,1,1]]
[[1,0,0],[1,0,1],[1,0,1]]
*/