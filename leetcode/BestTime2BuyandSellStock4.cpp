#include <vector>
#include <algorithm>
#include <limits.h>

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

***Update on 7/20/2018***

Since I was redoing this series and buy the idea from:

https://leetcode.com/articles/best-time-to-buy-and-sell-stock-with-transaction-fee/

and applied it on leetcode 123, it's straightforward to follow the same thought for this one, which
gives me an O(kN) time and O(k) space solution. No temp variable is necessary as usual.

At each given p, we look for the max hold and cash if we have 1, 2, 3,..., k transcations occurred.

we update the cash and hold array from k to 0. Therefore, no temp variable is needed and no
worry for overwrite.

One may ask: how could this work, say, kcash[j], when there is only m prices scanned, given m / 2 < j? Should we restrict
inner loop to an extent that the jth transcation is possible?

Answer is: not necessary at all since kcash array is initialized with 0 and khold array is set with INT_MIN. Therefore, if khold[j]
is not valid yet, there is no way kcash[j] can be updated with a value greater than zero.

```c++
for (int p : prices) {
for (int i = k - 1; i > -1; --i) {
kcash[i] = std::max(kcash[i], khold[i] + p);
khold[i] = std::max(khold[i], 0 == i ? -1LL * p : kcash[i - 1] - p);
}
}
```
Two edge cases I failed:

1. k is extremely huge, bigger than the prices array, for example:

1000000000
[1]

If we don't handle it, Runtime Error will occur: "terminate called after throwing an instance of 'std::bad_alloc' what():  std::bad_alloc".
This is because stack can't allocate a long long array with the given size.
The safeguard here is to check k and make sure k should be no greater than the size of the prices:

k = std::min(k, len)

I know this doesn't "fix" the issue, but will pass all test cases. In fact, there is more generic way, see next.

2. After fixing the case above, we have solution accepted but it's extremely slow, which means there is a bias on given test cases. After reading
the previous implementation, I realize the fact that:

If k > sizeof(prices) / 2, the problem can be transformed to leetcode 122, which is "complete as many transactions as you like".
In this scenario, it can be done in O(N) not O(kN). In given test cases, if k is extremely big, say, close to N, we should experience
poor performance.

So, by adding the check first (k >= len / 2), we have the opportunity to solve this much quick for these cases. In fact, this also
cover the first edge case to eliminate the possible bad_alloc.
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
		int len = (int)prices.size();
		//k = std::min(k, len);
		if (k >= len / 2) {
			long long ans = 0;
			for (int i = 1; i < len; ++i) ans += std::max(prices[i] - prices[i - 1], 0);
			return static_cast<int>(ans);
		}
		vector<long long> khold(k, numeric_limits<int>::min()), kcash(k, 0);
		for (int p : prices) {
			for (int i = k - 1; i > -1; --i) {
				kcash[i] = std::max(kcash[i], khold[i] + p);
				khold[i] = std::max(khold[i], 0 == i ? -1LL * p : kcash[i - 1] - p);
			}
		}
		return k > 0 ? static_cast<int>(kcash[k - 1]) : 0;
	}
	int maxProfit1(int k, vector<int>& prices) {
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
	int maxProfit2(int k, vector<int>& prices) {
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
/*
Test cases:

2
[2,4,1]
2
[3,2,6,5,0,3]
3
[3,2,6,5,0,3]
4
[3,2,6,5,0,3]
0
[1]
1000000000
[1]
3
[1,2]
10
[1]
10
[]
4
[1,3,2,0,0,1,1,2,2,3,4,2,1,1,5,3,2,4,3,4,2,1]
5
[1,1,1,1,1,1,1,1]
2
[1,4,1,5,2,9,8]
6
[1,4,1,5,2,9,8]
6
[32,27,56,13,42,67,88,86,45,29,18,22,44,55,23]
9
[32,27,56,13,42,67,88,86,45,29,18,22,44,55,23]
1
[1,0,1]
1
[3]

Outputs:

2
7
7
7
0
0
1
0
0
12
0
11
14
141
141
1
0
*/