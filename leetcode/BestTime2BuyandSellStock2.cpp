#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

//122. Best Time to Buy and Sell Stock II
/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times).
However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Observation:
Try greedy, my approach is:
Find the "lowest" price at index k, then from k + 1 to m, keep tracking the maxsofar
Update the "lowest" price if any of the following two scenarios is met:

1. There is an even lower price
2. Price[i] is lower than price[i - 1]

Obviously, someone on leetcode posted a more elegant solution. It's very simple, it's actually too simple to
make sense to me... but it works! The idea is: as long as prices[i] > prices[i-1], we add the difference to
the final result and totally ignore the fact: "you must sell the stock before you buy again"
So for [1,2,3,4], it will give you 2-1 + 3-2 + 4-3 = 3, which is the correct answer, but that means you can
sell and buy the stock at the same day...

Update on 11/20/2017
With the experience I gained at leetcde 714, the "bestBuy pattern". I first came with maxProfit2, which tracks the best buying
moment before reaching current index then examine if it's possible to get a higher profit by selling at current index price based upon
the best buying price it tracks. At each iteration, both possible max profit and best buying are checked at current index.

Since we need to know the previous best buy before current index and we have to examine possible best buying at current index as well, a temp
variable will have to be introduced to keep the previous best buy before best buying is recalculated on current index.

This turns out to be not necessary:

- If current index is the best buy place, it will NOT be the best selling place guaranteed. This can be explained by proof by contradiction:

1. Current price has to meet the following inequality in order to be the best buying price:

max_profit_before_current_index - price_at_current_index > previous_bestBuy

2. If current price is also the best selling price, it has to meet:

price_at_current_index + previous_bestBuy > max_profit_before_current_index

--> max_profit_before_current_index - price_at_current_index < previous_bestBuy

This is not possible since the inequality in step 1.

You may argue if above statement is true, ans = std::max(ans, p + bestBuy) may accidentally revise the max profit if
the price at current index is the best buy. It's NOT, coz

current_bestBuy = ans - price_at_current_index, therefore:

price_at_current_index + current_bestBuy = price_at_current_index + (ans - price_at_current_index) = ans

So, even current index is best buy, price_at_current_index + current_bestBuy won't exceed previous max profit.

We have maxProfit1 which has temp variable t removed safely.
*/
class SolutionBestTime2BuyandSellStock2 {
public:
	int maxProfit1(const vector<int> &prices) {
		int bestBuy = numeric_limits<int>::min(), ans = 0;
		for (int p : prices) {
			bestBuy = std::max(bestBuy, ans - p);
			ans = std::max(ans, p + bestBuy);
		}
		return ans;
	}
	int maxProfit2(const vector<int> &prices) {
		int bestBuy = numeric_limits<int>::min(), ans = 0, t = 0;
		for (int p : prices) {
			t = bestBuy;
			bestBuy = std::max(bestBuy, ans - p);
			ans = std::max(ans, p + t);
		}
		return ans;
	}
	int maxProfit3(const vector<int>& prices) {
		int len = prices.size();
		if (len < 2)return 0;
		int minPriceSofar = prices[0];
		int maxSofar = 0;
		long long maxProfit = 0;
		for (int i = 1; i < len; ++i)
		{
			if (prices[i] < minPriceSofar || prices[i] < prices[i - 1])
			{
				minPriceSofar = prices[i];
				maxProfit += maxSofar;
				maxSofar = 0;
			}
			else
				maxSofar = std::max(maxSofar, prices[i] - minPriceSofar);
		}
		return maxProfit + maxSofar;
	}
	int maxProfit(const vector<int>& prices) {
		int maxProfit = 0;
		for (int i = 1; i < prices.size(); i++) {
			if (prices[i] > prices[i - 1]) maxProfit += (prices[i] - prices[i - 1]);
		}
		return maxProfit;
	}
};
void TestBestTime2BuyandSellStock2()
{
	SolutionBestTime2BuyandSellStock2 so;
	cout << "Expect 0: " << so.maxProfit(vector<int>{}) << endl;
	cout << "Expect 0: " << so.maxProfit(vector<int>{1}) << endl;
	cout << "Expect 1: " << so.maxProfit(vector<int>{1, 2}) << endl;
	cout << "Expect 2: " << so.maxProfit(vector<int>{1, 2, 3}) << endl;
	cout << "Expect 3: " << so.maxProfit(vector<int>{1, 2, 3, 4}) << endl;
	cout << "Expect 9: " << so.maxProfit(vector<int>{3, 2, 4, 1, 5, 6, 8, 6}) << endl;
	cout << "Expect 7: " << so.maxProfit(vector<int>{6, 1, 3, 2, 4, 7}) << endl;
	cout << "Expect 8: " << so.maxProfit(vector<int>{4, 1, 8, 6, 5, 6}) << endl;
	cout << "Expect 9: " << so.maxProfit(vector<int>{4, 1, 2, 3, 4, 10}) << endl;
	cout << "Expect 10: " << so.maxProfit(vector<int>{4, 1, 3, 2, 4, 10}) << endl;
}