#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
/*
121. Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Observation:
Since you can only make one transaction, the best bet is obviously sell low and buy high. All you need to
do is to find the lowest price so far and track the max profit from following prices, if there is an even
lower price, let's set the new low as the lowest price.

This problem is actually equivalent to max subarray problem. If you process the original array a bit and put the
difference between i - 1 and i: prices[i] - prices[i - 1] in the array and then apply the max subarray algorithm. It
will be slower than the first approach, since it involves two scan, but it's still a linear algorithm.

On the other hand, you actually could slove max subarray problem using approach 1. Simply find the smallest
element, probably a negative number, and make a prices[0] big enough, which could guarantee there is no negative
number in the array, then you have a Best Time to Buy and Sell Stock...
*/
class SolutionBestTime2BuyandSellStock {
public:
	int maxProfit1(vector<int>& prices) {
		int len = prices.size();
		if (len < 2)return 0;
		for (int i = 1; i < len; ++i)
			prices[i - 1] = prices[i] - prices[i - 1];
		--len;
		long long maxendhere = prices[0], maxsofar = prices[0];
		for (int i = 1; i < len; ++i)
		{
			maxendhere = std::max((long long)prices[i], maxendhere + prices[i]);
			maxsofar = std::max(maxendhere, maxsofar);
		}
		return maxsofar < 0 ? 0 : maxsofar;
	}
	int maxProfit(vector<int>& prices) {
		int len = prices.size();
		if (len < 2)return 0;
		int minPriceSofar = prices[0];
		long long maxProfit = 0;
		for (int i = 1; i < len; ++i)
		{
			minPriceSofar = std::min(minPriceSofar, prices[i]);
			maxProfit = std::max(maxProfit, (long long)prices[i] - (long long)minPriceSofar);
		}
		return maxProfit;
	}
};