#include <vector>

using namespace std;

//https://leetcode.com/problems/surrounded-regions/
/*
130. Surrounded Regions

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

Explanation:

Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.

Observations:

DFS appears to be very intuitive. My first attempt failed coz I didn't realize the fact that cell can not be flipped until
the entire DFS path is discovered and all cells's neighbors are checked. This means the entire DFS path has to be kept somehow and updated
accordingly based upon the boolean return value from DFS at root. If it's confirmed as "surrounded region", flip all of them in a loop.

This naive approach requires a status array to track the visit status and also an extra array for DFS path, which doesn't work very well
with the test cases leetcode assigned. See solve1.

Since this is a solution requires Complete Search anyway, one may have two choices:

1. Generating;
2. Filtering;

The naive solve1 generates all valid cells for flip. One may try filtering: start from cells with 'O' at the boundary and then filtering out
all neighbor cells whoes value is 'O'. In such an approach, all visited cells with 'O' can be safely flipped to a temp value, say 'Y'.

Once all 'Y's are identified, loop the board, cell with 'X' no change. Cell with 'O'->'X'; Cell with 'Y'->'O'.

See solve. In this solution, no need to track neither visit status nor DFS full path for update. furthermore, DFS is only
conducted on cells with 'O' at boundary line.
*/
class SolutionSurroundedRegions {
public:
	void solve(vector<vector<char>>& board) {
		int rlen = board.size();
		if (1 > rlen) return;
		int clen = board[0].size();
		if (1 > clen) return;
		auto dfs = [&board, rlen, clen](int i, int j, const auto& f) {
			if (rlen <= i || clen <= j || 0 > i || 0 > j || 'X' == board[i][j] || 'Y' == board[i][j]) return;
			if ('O' == board[i][j]) board[i][j] = 'Y';
			f(i - 1, j, f), f(i + 1, j, f), f(i, j - 1, f), f(i, j + 1, f);
		};
		for (int i = 0; i < rlen; ++i) {
			if ('O' == board[i][0]) dfs(i, 0, dfs);
			if ('O' == board[i][clen - 1]) dfs(i, clen - 1, dfs);
		}
		for (int i = 0; i < clen; ++i) {
			if ('O' == board[0][i]) dfs(0, i, dfs);
			if ('O' == board[rlen - 1][i]) dfs(rlen - 1, i, dfs);
		}
		for (int i = 0; i < rlen; ++i) for (int j = 0; j < clen; ++j) board[i][j] = 'X' == board[i][j] ? 'X' : ('Y' == board[i][j] ? 'O' : 'X');
	}
	void solve1(vector<vector<char>>& board) {
		int rlen = board.size();
		if (1 > rlen) return;
		int clen = board[0].size();
		if (1 > clen) return;
		vector<int> status(rlen * clen, 0);
		auto dfs = [&status, &board, rlen, clen](int i, int j, auto& v, const auto& f) -> bool {
			if (rlen <= i || clen <= j || 0 > i || 0 > j || 2 == status[i * clen + j]) return false;
			if ('X' == board[i][j] || 1 == status[i * clen + j]) return true;
			status[i * clen + j] = 1;
			v.push_back(std::make_pair(i, j));
			return true == f(i - 1, j, v, f) && true == f(i + 1, j, v, f) && true == f(i, j - 1, v, f) && true == f(i, j + 1, v, f);
		};
		for (int i = 0; i < rlen; ++i)
			for (int j = 0; j < clen; ++j) {
				vector<std::pair<int, int> > memo;
				if ('O' == board[i][j] && 0 == status[i * clen + j]) {
					if (true == dfs(i, j, memo, dfs)) for (const auto& p : memo) board[p.first][p.second] = 'X';
					else for (const auto& p : memo) status[p.first * clen + p.second] = 2;
				}
			}
	}
};
/*
Test cases:

[["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
[["X","X","O","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
[["X","X","O","X"],["X","O","O","X"],["X","X","O","X"],["X","O","O","X"]]
[["X","O"],["O","X"],["X","X"]]
[["X"],["O"],["X"]]
[[]]
[["X"]]
[["O"]]
[["X","X","X"],["X","O","X"],["X","X","X"]]
[["X","X","X","O","X"],["X","O","X","X","O"],["X","O","O","X","O"],["X","O","X","O","X"],["O","X","O","O","X"],["O","O","X","X","X"]]
[["O","X","O","O","O","X"],["O","O","X","X","X","O"],["X","X","X","X","X","O"],["O","O","O","O","X","X"],["X","X","O","O","X","O"],["O","O","X","X","X","X"]]

Outputs:

[["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
[["X","X","O","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
[["X","X","O","X"],["X","O","O","X"],["X","X","O","X"],["X","O","O","X"]]
[["X","O"],["O","X"],["X","X"]]
[["X"],["O"],["X"]]
[[]]
[["X"]]
[["O"]]
[["X","X","X"],["X","X","X"],["X","X","X"]]
[["X","X","X","O","X"],["X","X","X","X","O"],["X","X","X","X","O"],["X","X","X","X","X"],["O","X","X","X","X"],["O","O","X","X","X"]]
[["O","X","O","O","O","X"],["O","O","X","X","X","O"],["X","X","X","X","X","O"],["O","O","O","O","X","X"],["X","X","O","O","X","O"],["O","O","X","X","X","X"]]
*/