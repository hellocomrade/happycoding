#include <vector>
#include <algorithm>
#include <iostream>

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
*/
class SolutionBestTime2BuyandSellStock2 {
public:
	int maxProfit1(const vector<int>& prices) {
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
