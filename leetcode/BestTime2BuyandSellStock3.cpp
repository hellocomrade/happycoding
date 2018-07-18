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

Update on 7/18/2018

After reading the official solution for leetcode 714, Best Time to Buy and Sell Stock with Transaction Fee at:

https://leetcode.com/articles/best-time-to-buy-and-sell-stock-with-transaction-fee/

I started to buy the idea of using the term hold and cash for representing the two states:

At the end of the i-th day, we maintain cash, the maximum profit we could have if we sell the share of stock
and hold, the maximum profit we buy a share of stock."

The max profit is the max of (cash + hold)

This series of questions have an unique coding style which stacks/embeds couple max(), min() without using any if...else...
So, the order of these calls is cirtical.

1. Get max profit after two transcations;
2. Get max hold based upon the max profit from 1 transcation (buy the second time here);
3. Get max profit for 1st transcation if stock is sold here (for future use);
4. Get max hold for the first transcation (start over as if from beginning);

- ans relies on hold (after the second buy) and curret stock price, p (potential best sell price, the completion of the second transaction);
- hold (after the second buy) is always based upon max_cash_1_trans (after the first sell, the completion of the first transaction);
- max_cash_1_trans (first sell) is always based upon max_hold_1_trans (first buy);
- max_hold_1_trans depends on current stock price, p;
*/
class SolutionBestTime2BuyandSellStock3 {
public:
	int maxProfit(vector<int>& prices) {
		int int_min = numeric_limits<int>::min();
		long long ans = 0LL, max_cash_1_trans = 0LL, max_hold_1_trans = int_min, hold = int_min;
		for (int p : prices) {
			ans = std::max(ans, hold + p);
			hold = std::max(hold, max_cash_1_trans - p);
			max_cash_1_trans = std::max(max_cash_1_trans, max_hold_1_trans + p);
			max_hold_1_trans = std::max(max_hold_1_trans, p * -1LL);
		}
		return static_cast<int>(ans);
	}
	int maxProfit0(vector<int>& prices) {
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
/*
Test cases:

[6,1,3,2,4,7]
[0,3,2,5,2,7]
[0,3,2,5,2,8,2,6,10]
[0,3,2,5,2,7]
[3,3,5,0,0,3,1,4]
[3,3,7,2,2,3,1,4]
[1,2,3,4,5]
[7,6,4,3,1]
[]
[1]
[1,2]
[1,2,3]
[1,0,1]
[1,0,0]
[1,2,2]
[1,2,2,3]
[1,2,2,1]
[1,0,1,2]
[0,1,2,1]
[0,1,2,3]
[18,27,0,23,0,12,35,21,34,25,6,0,0,5,13,15,17,8,7,9,10]
[7,3,2,0,1,1,1,0,3,2,2,1,0,4,5,2,1,1,0,0]

Outputs:

7
10
16
10
6
7
4
0
0
0
1
2
1
0
1
2
1
2
2
3
58
8
*/