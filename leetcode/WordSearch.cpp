#include <string>
#include <unordered_set>

using namespace std;

//https://leetcode.com/problems/word-search
/*
79. Word Search

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once.

Example:

board =
[
['A','B','C','E'],
['S','F','C','S'],
['A','D','E','E']
]

Given word = "ABCCED", return true.

Given word = "SEE", return true.

Given word = "ABCB", return false.

Observation:

Looks like a graph DFS, however, since the possible neighboors are all at known locations, up/down/left/right 4 directions, we don't need to
set up a data structure for depicting relations. But we do have to mark visited nodes.

Instead, this can be consdiered as a backtracing problem coz the visited node list is dynamic based upon previous search result. Originally,
I use an unordered_set, but turned out it's not necessary coz we can directly mark visited node on vector<vector<char>> board.

The first ACCEPT was extremely slow, not because I used an extra unordered_set<int>, it's because I forgot the '&' on the first argument of aux1.
Therefore, copy contructor is called for each recursion for memoset...
*/
class Solution {
private:
	bool aux(vector<vector<char>>& board, const string& word, int i, int j, int idx) {
		int ilen = (int)board.size(), jlen = (int)board[0].size(), slen = (int)word.length();
		if (idx == slen) return true;
		bool ans = false;
		if (i < 0 || i > ilen - 1 || j < 0 || j > jlen - 1 || 0 == board[i][j]) return false;
		if (word[idx] == board[i][j]) {
			board[i][j] = 0;
			ans = this->aux(board, word, i - 1, j, idx + 1) || this->aux(board, word, i + 1, j, idx + 1) || this->aux(board, word, i, j - 1, idx + 1) || this->aux(board, word, i, j + 1, idx + 1);
			board[i][j] = word[idx];
		}
		return ans;
	}
	bool aux1(unordered_set<int>& memoset, const vector<vector<char>>& board, const string& word, int i, int j, int idx) {
		int ilen = (int)board.size(), jlen = (int)board[0].size(), slen = (int)word.length();
		if (idx == slen) return true;
		bool ans = false;
		if (i < 0 || i > ilen - 1 || j < 0 || j > jlen - 1 || 1 == memoset.count(i * jlen + j)) return false;
		if (word[idx] == board[i][j]) {
			memoset.insert(i * jlen + j);
			ans = this->aux1(memoset, board, word, i - 1, j, idx + 1) || this->aux1(memoset, board, word, i + 1, j, idx + 1) || this->aux1(memoset, board, word, i, j - 1, idx + 1) || this->aux1(memoset, board, word, i, j + 1, idx + 1);
			memoset.erase(i * jlen + j);
		}
		return ans;
	}
public:
	bool exist(vector<vector<char>>& board, string word) {
		int ilen = (int)board.size(), slen = (int)word.length();
		if (ilen < 1 || slen < 1) return false;
		int jlen = (int)board[0].size();
		if (jlen < 1) return false;
		for (int i = 0; i < ilen; ++i)
			for (int j = 0; j < jlen; ++j)
				if (board[i][j] == word[0] && true == this->aux(board, word, i, j, 0))
					return true;
		return false;
	}
	bool exist1(vector<vector<char>>& board, string word) {
		int ilen = (int)board.size(), slen = (int)word.length();
		if (ilen < 1 || slen < 1) return false;
		int jlen = (int)board[0].size();
		if (jlen < 1) return false;
		unordered_set<int> memoset;
		for (int i = 0; i < ilen; ++i)
			for (int j = 0; j < jlen; ++j)
				if (board[i][j] == word[0] && true == this->aux1(memoset, board, word, i, j, 0))
					return true;
		return false;
	}
};
/*
Test cases:
[["A","B","C","E"],["S","F","E","S"],["A","D","E","E"]]
"ABCESEEEFS"
[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
"ABCCED"
[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
"SEE"
[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
"ABCB"
[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
"BCCEDFB"
[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
"FCSEC"
[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
"FCSECC"

Outputs:

true
true
true
false
false
true
false
*/