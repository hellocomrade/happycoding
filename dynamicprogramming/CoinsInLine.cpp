//http://www.lintcode.com/en/problem/coins-in-a-line/
/*
394. Coins in a Line

There are n coins in a line. Two players take turns to take one or two coins from right side until there are no more coins left. The player who take the last coin wins.

Could you please decide the first play will win or lose?

Example
n = 1, return true.

n = 2, return true.

n = 3, return false.

n = 4, return true.

n = 5, return true.

Challenge
O(n) time and O(1) memory

Observation:
O(N) time and O(1) space can be done using DP.

Given array memo for storing whether current player on this turn is able to win, say current turn has X coins,
we want to know if memo(X - 1) and memo(X - 2) are both true. If so, no matter current player takes 1 coin or 2 coins, the other player
will always win. Therefore, current player is going to lose. In other word, in order for current player to win, either memo(X - 1) or memo(X - 2)
will have to be false, which means the next player will not be able to take all remaining coins with either X - 1 and X - 2 left.

Take a second look, we don't need the memo array since we only care the status of X - 1 and X - 2. Therefore only O(1) space is needed. The whole algorithm
scans the number from 0 to n, O(N) time.

Actually, if you try a really large int like 2147483647 on lintcode, you will get a TLE! Why? coz this is a brainteaser question!

0 != n % (max_allowed_number_coin + 1)

*/
class SolutionCoinsInLine {
public:
	/**
	* @param n: an integer
	* @return: a boolean which equals to true if the first player will win
	*/
	bool firstWillWin(int n) {
		return 0 != n % 3;
	}
	bool firstWillWin1(int n) {
		bool m1 = true, m2 = true, m = true;
		for (int i = 3; i <= n; ++i) {
			m = !(m1 && m2);
			m2 = m1;
			m1 = m;
		}
		return n > 0 ? m : false;
	}
};