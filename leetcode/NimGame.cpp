#include <vector>

using namespace std;

//https://leetcode.com/problems/nim-game/
/*
292. Nim Game

You are playing the following Nim Game with your friend: There is a heap of stones on the table,
each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner.
You will take the first turn to remove the stones.

Both of you are very clever and have optimal strategies for the game. Write a function to determine
whether you can win the game given the number of stones in the heap.

Example:

Input: 4

Output: false

Explanation: If there are 4 stones in the heap, then you will never win the game;
			 No matter 1, 2, or 3 stones you remove, the last stone will always be
			 removed by your friend.

Observations:

It's not hard to figure out a linear algorithm (since a player can only pick up to 4 stones) using memorization.
But you will guarantee to get a TLE (see canWinNim1) coz this is a brainteaser question...

0 false
1 true
2 true
3 true
4 false
5 true
6 true
7 true
8 false
9 true
10 true

The player who takes the first turn will win all games execpt the number of stone can be divded by 4.

So the acceptd solution is as simple as 0 != n % 4;
*/
class SolutionNimGame {
public:
	bool canWinNim(int n) {
		return 0 != n % 4;
	}
	//TLE
	bool canWinNim1(int n) {
		if (1 > n) return false;
		vector<bool> memo(n, false);
		memo[0] = memo[1] = memo[2] = true;
		for (int i = 4; i <= n; ++i) {
			for (int j = 1; false == memo[i - 1] && j < 4; ++j)
				if (i - j > 0) memo[i - 1] = !memo[i - j - 1];
		}
		return memo[n - 1];
	}
};