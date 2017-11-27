#include <bitset>
#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/valid-sudoku/
/*
36. Valid Sudoku

Determine if a Sudoku is valid, according to: http://sudoku.com.au/TheRules.aspx.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.


A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.

Observations:
Thought hard to find a better solution but failed. It appears unordered_set(hashset) is the best one in terms of performance.
Typical trading space for speed idea. An optmization I could make is to replace hashset with bitset, so we only need 9X9X3 bits.

Also, since input is in char, in order to put them in bitset, has to do board[i][j] - 49. 49 is the ascii value for digit 1.
*/
class SolutionValidSudoku {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		vector<bitset<9>> rowMap(9), colMap(9), secMap(9);
		for (int i = 0, idx = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if ('.' == board[i][j])continue;
				idx = j / 3 + i / 3 * 3;
				if (true == rowMap[i].test(board[i][j] - 49) || true == colMap[j].test(board[i][j] - 49) || true == secMap[idx].test(board[i][j] - 49))
					return false;
				rowMap[i].set(board[i][j] - 49);
				colMap[j].set(board[i][j] - 49);
				secMap[idx].set(board[i][j] - 49);
			}
		}
		return true;
	}
};