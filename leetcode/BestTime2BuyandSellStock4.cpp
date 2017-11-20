#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
/*
188. Best Time to Buy and Sell Stock IV

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Observations:
This is the first time I'd like to admit the fact this is a DP! All others in best buy series, I think they are greedy...

Anyway, since we are allowed to have up to k transactions, the approach we took on leetcode 123 will not work. We have to
use an array. We can do an array with dimension of k * len(prices) or len(prices) * k.

k * len(prices) means the best buy info at each index is kept from transaction 1 to k. Outter loop is on k;

len(prices) * k means the best buy info from transaction 1 to k at each index is kept. Outter loop is on len;

I go with the first one since it makes more sense in terms of DP. So, we have a bestBuys array with size of len + 1 and
we reuse this array from transaction i to i + 1 considering the fact that we only care the memorized value from last transaction.

Two extra variables are used. maxThere is for tracking the current max profit for current transaction at each price index j. t is for
storing the best buy at price index j - 1 for the previous transaction. Since we have to update both best buy and maxThere on each interation,
we have to save the best buy at this index for previous transaction first. This is different than the case in leetcode 122, which t can be avoided.
Here, t is necessary.

My first attempt got a TLE coz I failed to recognize the fact that k can be a really large number, the extreme case will be like
k = 100000 and len(prices) = 3. It's a O(N^2) in the worst case.

In fact, if k >= len(prices) / 2, it bascially asks to have as many transactions as you can, which turns the problem to leetcode leetcode 122.
So, we could make the time complexity to O(N^2) / 2 in the worst case by applying leetcode 122 when k >= len(prices) / 2.

I took the "official" solution of leetcode 122 here.

Based upon the new comment in leetcode 122, even though we can't eliminate temp variable here, we can make it simpler. The original idea requires
to grab the bestBuy[j - 1] in temp variable so it can be used for the next iteration. This will need two temp variables t and t1.

With the prove in leetcode 122, we can grab bestBuy[j - 1] in temp varaiable t and use it directly to calculate maxThere.
*/
class SolutionBestTime2BuyandSellStock4 {
private:
	int aux(const vector<int>& prices, int len) {
		int ans = 0;
		while (--len > 0)
			ans += std::max(0, prices[len] - prices[len - 1]);
		return ans;
	}
public:
	int maxProfit(int k, vector<int>& prices) {
		int len = static_cast<int>(prices.size()), ans = 0, t = 0, maxThere = 0;
		if (k >= len / 2) return this->aux(prices, len);
		vector<int> bestBuys(len + 1, INT_MAX);
		for (int i = 0; i < k; ++i) {
			maxThere = 0;
			for (int j = 1; j <= len; ++j) {
				ans = std::max(ans, prices[j - 1] - bestBuys[j - 1]);
				t = bestBuys[j];
				bestBuys[j] = std::min(bestBuys[j - 1], prices[j - 1] - maxThere);
				maxThere = std::max(maxThere, prices[j - 1] - t);
			}
		}
		return ans;
	}
	int maxProfit1(int k, vector<int>& prices) {
		int len = static_cast<int>(prices.size()), ans = 0, t = 0, t1 = 0, maxThere = 0;
		if (k >= len / 2) return this->aux(prices, len);
		vector<int> bestBuys(len + 1, INT_MAX);
		for (int i = 0; i < k; ++i) {
			maxThere = 0, t = bestBuys[0];
			for (int j = 1; j <= len; ++j) {
				ans = std::max(ans, prices[j - 1] - bestBuys[j - 1]);
				t1 = bestBuys[j];
				bestBuys[j] = std::min(bestBuys[j - 1], prices[j - 1] - maxThere);
				maxThere = std::max(maxThere, prices[j - 1] - t);
				t = t1;
			}
		}
		return ans;
	}
};