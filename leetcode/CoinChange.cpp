#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

//https://leetcode.com/problems/coin-change/
/*
322. Coin Change

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.

Observations:

This is a question widely used as DP 101. Below is my answer, I thought I shouldn't have any issue to implement it,
an O(N^2) DP...

But see what I missed? `infinity`, which (amount + 1) is sufficient, given all coins are integers, but I use numeric_limits<long long>::max()
and long long is an overkill as well, coz you will need at most `amount` coins given all coins are integers.

The solution below though, didn't consider the fact that `amount` could be negative though.

https://leetcode.com/problems/coin-change/solution/
*/
class SolutionCoinChange {
public:
	int coinChange(vector<int>& coins, int amount) {
		if (amount < 0)return -1;
		int len = (int)coins.size();
		long long infinity = numeric_limits<long long>::max();
		vector<long long> memo(amount + 1, infinity);memo[0] = 0;
		for (int i = 1; i <= amount; ++i)
			for (int j = 0; j < len; ++j)
				if (i - coins[j] >= 0 && infinity != memo[i - coins[j]]) memo[i] = std::min(memo[i], memo[i - coins[j]] + 1LL);
		return (infinity == memo[amount]) ? -1 : static_cast<int>(memo[amount]);
	}
};
/*
Test cases:

[1]
0
[1,2,5]
11
[2]
3
[]
10
[3,2,1,6,7,8,9,4]
1001
[76,34,15,7,9,0,21,18]
2345

Output:

0
3
-1
-1
112
34
*/