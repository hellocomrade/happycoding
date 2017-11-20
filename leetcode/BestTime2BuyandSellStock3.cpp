#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
/*
123. Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Observations:
If you follow the notes offered by leetcode on "122. Best Time to Buy and Sell Stock II", you would fail on this one.
Instead, since the last one I did in this series is "714. Best Time to Buy and Sell Stock with Transaction Fee",
The approach I took there can be applied on this one as well. Actually, it works on 122 too.

If I apply my bestBuy idea on this one, the difference here is that you are allowed to take at most 2 transactions.
This means the max could come out of either 1 transaction or 2 transactions.

Also, instead of tracking one bestBuy value, we now probably have to track two, which are the bestBuy for the first
transaction and the bestBuy for the second one.

For given array prices, on each index, we examine the bestBuy[2] values if we sell on this prices[i] as the first transaction
or the second transaction.

Calculating the bestBuy[0] is easy: since it's the first buy, the cost is prices[i].

bestBuy[1] at index i is prices[i] - max1, which max1 is the max profit you can get from the first transaction based upon the
previous bestBuy[0],

max1 is calculated by max(max1, prices[i] - prev_bestBuy[0]), try to examine if the max profit is possible at index i based upon
the previous bestBuy[0], first transaction.

The final answer is max(ans, max(max1, prices[i] - prev_bestBuy[1]), prices[i] - prev_bestBuy[1] represents the possible max profit
after two transactions.

The over complexity is still O(N) time and O(1) space.

Update on 11/20/2017
Based upon the new comment on leetcode 122, we know variable t1 and t2 can be avoided.
*/
class SolutionBestTime2BuyandSellStock3 {
public:
	int maxProfit(vector<int>& prices) {
		int ans = 0, maxHere = 0, bestBuy[] = { numeric_limits<int>::max(), numeric_limits<int>::max() };
		for (int p : prices) {
			bestBuy[0] = std::min(bestBuy[0], p);
			bestBuy[1] = std::min(bestBuy[1], p - maxHere);
			maxHere = std::max(maxHere, p - bestBuy[0]);
			ans = std::max(ans, std::max(maxHere, p - bestBuy[1]));
		}
		return ans;
	}
	int maxProfit1(const vector<int>& prices) {
		int ans = 0, max1 = 0, t1 = 0, t2 = 0, bestBuy[] = { numeric_limits<int>::max(), numeric_limits<int>::max() };
		for (int p : prices) {
			t1 = bestBuy[0], t2 = bestBuy[1];
			bestBuy[0] = std::min(t1, p);
			bestBuy[1] = std::min(t2, p - max1);
			max1 = std::max(max1, p - t1);
			ans = std::max(ans, std::max(max1, p - t2));
		}
		return ans;
	}
};