#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
/*
309. Best Time to Buy and Sell Stock with Cooldown

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]

Observation:
DP for sure. There are three statuses: buy, sell and cooldown. You can buy and sell at any index, after sell,
you will have to wait for at least one day.

First intutive idea:

S[i] = Min(P[i] - P[k] + Cooldown[k - 1]), given k in [0, i - 1]
Cooldown[i] = Max(S[i - 1], Cooldown[i - 1])

Doing so will results in an O(N^2) DP, Oops, too slow

Second thought:
Chase for linear DP, what if we could have a bestbuy value, which is the min(P[i] - Cooldown[i - 1]).
We will keep using this bestbuy value until we find a new one P[k] - Cooldown[k - 1] that is less than the current one
Therefore, we remove the inner loop and only needs O(1) space.

Third try:
Inspired by justinj656 on leetcode: https://leetcode.com/discuss/90786/dp-c-solution-8-lines-of-code
There is a even more elegant solution.

He's code tracks the last two maxProfit[i], maxProfit[i-1] and coolDown[i-2]
at k = i + 1
coolDown[k] = max(maxProfit[k - 1], price[k] - price[k - 1] + coolDown[k - 2])

maxProfit[k] = max(maxProfit[k - 1], coolDown[k])

Update on 11/22/2017, based up the new comment for leetcode 122 and 714, I come with the latest one that only requires
3 variable and run in O(N) time. Surprisingly, no dicussion on top list is close to this. Even in this "most consistent"
tutorial: https://discuss.leetcode.com/topic/107998/most-consistent-ways-of-dealing-with-the-series-of-stock-problems

The idea is: bestBuy at index i can only be taken from ans_prev, which is i - 2. Why? If there is a best sell at i - 1,
there would not be any bestBuy or best sell at index i due to cool down. Therefore, if we want to examine if a bestBuy or
best sell at index i, we have to look back to i - 2. Of course, if there is no best sell at i - 1, ans_prev will be as
same as ans.
*/
class SolutionBestTime2BuyandSellStockWithCooldown {
public:
	int maxProfit(const vector<int>& prices) {
		int ans = 0, bestBuy = numeric_limits<int>::max(), ans_prev = 0;
		for (int p : prices) {
			bestBuy = std::min(bestBuy, p - ans_prev);
			ans_prev = ans;
			ans = std::max(ans, p - bestBuy);
		}
		return ans;
	}
	int maxProfit1(const vector<int>& prices) {
		int len = prices.size();
		if (len < 2)return 0;
		vector<int> profitEndHere(len, 0);
		vector<int> coolDownAtHere(len, 0);
		int tmp = 0;
		for (int i = 1; i < len; ++i)
		{
			for (int j = i - 1; j > -1; --j)
			{
				tmp = j > 0 ? coolDownAtHere[j - 1] : 0;
				profitEndHere[i] = std::max(profitEndHere[i], prices[i] - prices[j] + tmp);
			}
			coolDownAtHere[i] = std::max(profitEndHere[i - 1], coolDownAtHere[i - 1]);
		}
		return std::max(profitEndHere[len - 1], coolDownAtHere[len - 1]);
	}
	int maxProfit2(const vector<int>& prices) {
		int len = prices.size();
		if (len < 2)return 0;
		int profitEndHere = 0, poriftEndPrev = 0;
		int bestBuy = prices[0];
		int prevCoolDown = 0;
		for (int i = 1; i < len; ++i)
		{
			poriftEndPrev = profitEndHere;
			profitEndHere = std::max(profitEndHere, prices[i] - bestBuy);
			bestBuy = std::min(bestBuy, prices[i] - prevCoolDown);
			prevCoolDown = std::max(poriftEndPrev, prevCoolDown);
		}
		return std::max(profitEndHere, prevCoolDown);
	}
	int maxProfit3(const vector<int>& prices) {
		int len = prices.size();
		if (len < 2)return 0;
		int maxProfit = 0;
		int maxProfitPrev = 0;
		int maxProfitPrev2 = 0; //cooldown
		for (int i = 1; i < len; ++i)
		{
			maxProfitPrev2 = std::max(maxProfitPrev, prices[i] - prices[i - 1] + maxProfitPrev2);
			maxProfitPrev = maxProfit;
			maxProfit = std::max(maxProfit, maxProfitPrev2);
		}
		return maxProfit;
	}
};
void TestBestTime2BuyandSellStockWithCooldown()
{
	SolutionBestTime2BuyandSellStockWithCooldown so;
	cout << "Expect 0: " << so.maxProfit(vector<int>{}) << endl;
	cout << "Expect 0: " << so.maxProfit(vector<int>{1}) << endl;
	cout << "Expect 0: " << so.maxProfit(vector<int>{1, 1, 1, 1, 1}) << endl;
	cout << "Expect 1: " << so.maxProfit(vector<int>{1, 2}) << endl;
	cout << "Expect 3: " << so.maxProfit(vector<int>{1, 2, 3, 0, 2}) << endl;
	cout << "Expect 7: " << so.maxProfit(vector<int>{3, 2, 4, 1, 5, 6, 8, 6}) << endl;
	cout << "Expect 6: " << so.maxProfit(vector<int>{1, 2, 3, 4, 5, 6, 7}) << endl;
	cout << "Expect 0: " << so.maxProfit(vector<int>{7, 6, 5, 4, 3, 2, 1}) << endl;
	cout << "Expect 119: " << so.maxProfit(vector<int>{23, 56, 36, 76, 12, 0, 45, 28, 66}) << endl;
}