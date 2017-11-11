#include <cassert>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
/*
714. Best Time to Buy and Sell Stock with Transaction Fee

Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i; and a non-negative integer fee representing a transaction fee.

You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction. You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

Example 1:
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
Note:

0 < prices.length <= 50000.
0 < prices[i] < 50000.
0 <= fee < 50000.

Observations:
I noticed this is one of the series of max profit problems that are rooted from the classic Maximum subarray problem.

So, I did think for a second that I should following the same approach, but then I was destracted by DP since that's how I
get to this problem. Naive DP is pretty straightforward:

At any index i, we check prices[i] - prices[j] - fee + memo[j - 1], which 0 <=j < i and memo is for tracking the max profit at
each index. So, (prices[i] - prices[j] - fee + memo[j - 1]) means if we buy at index j, we will make profit as much as
(prices[i] - prices[j] - fee) plus the profit we've already made before index j, which is memo[j - 1].

This DP requires O(N^2) time and O(N) space, which will TLE.

Then I know there probably is a linear solution. Let's try the classic, which will be combining two max/max together on two variables somehow.
I won't even call it DP, it's greedy.

We have two variables: ans is for the current max profix, bestBuy is for the best buying so far. Best buying means the combination of low
buying price plus previous profit. The current max profix always comes from the max of current prices minus bestBuy minus fee because bestBuy
has already been rolled in the previous max profit:

ans = max(ans, price - fee - bestBuy)

bestBuy, on the other hand is: min(bestBuy, price - prev_ans)

Why prev_ans? coz ans could be overwritten on any given price, when that happens, the max profit for bestBuy should be the previous one. You
can not sell and buy at the same time.
*/
class SolutionBestTime2BuySellStockWithFee {
public:
	//we can calculate bestBuy at first
	int maxProfit(const vector<int>& prices, int fee) {
            int ans = 0, t = 0, bestBuy = numeric_limits<int>::max();
	    for (int p : prices) {
		t = bestBuy;
                bestBuy = std::min(bestBuy, p + fee - ans);
		ans = std::max(ans, p - t);	
	    }
	    return ans;
    	}
	int maxProfit1(const vector<int>& prices, int fee) {
            int ans = 0, t = 0, bestBuy = numeric_limits<int>::min();
	    for (int p : prices) {
		t = bestBuy;
                bestBuy = std::max(bestBuy, ans - p - fee);
		ans = std::max(ans, p + t);	
	    }
	    return ans;
        }
	//Greedy, fee is charged when buy
	int maxProfit2(const vector<int>& prices, int fee) {
		int ans = 0, t = 0, bestBuy = numeric_limits<int>::min();
		for (int p : prices) {
			t = ans;
			ans = std::max(ans, p + bestBuy);
			bestBuy = std::max(bestBuy, t - p - fee);
		}
		return ans;
	}
	//Greedy with overflow possibility if fee is charged on sale (p - fee - numeric_limits<int>::max())
	int maxProfit3(const vector<int>& prices, int fee) {
		long long ans = 0, t = 0, bestBuy = numeric_limits<int>::max();
		for (int p : prices) {
			t = ans;
			ans = std::max(ans, p - fee - bestBuy);
			bestBuy = std::min(bestBuy, p - t);
		}
		return static_cast<int>(ans);
	}
	//DP, naive, O(N^2), TLE
	int maxProfit4(const vector<int>& prices, int fee) {
		int len = static_cast<int>(prices.size()), ans = 0;
		vector<int> memo(len + 1, numeric_limits<int>::min());
		memo[0] = memo[1] = 0;
		for (int i = 1; i < len; ++i) {
			memo[i + 1] = memo[i];
			for (int j = i - 1; j > -1; --j)
				memo[i + 1] = std::max(memo[i + 1], prices[i] - prices[j] - fee + memo[j]);
			ans = std::max(ans, memo[i + 1]);
		}
		return ans;
	}
};
void TestBestTime2BuySellStockWithFee() {
	SolutionBestTime2BuySellStockWithFee so;
	assert(8 == so.maxProfit(vector<int>{1, 3, 2, 8, 4, 9}, 2));
	assert(2 == so.maxProfit(vector<int>{1, 3, 3, 6, 2, 7, 5, 5, 4, 2, 1, 3, 4}, 4));
}
