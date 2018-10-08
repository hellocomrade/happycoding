#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

//https://www.lintcode.com/problem/take-coins
/*
1399. Take Coins

Description
There aren coins in a row, each time you want to take a coin from the left or the right side. Take a total of k times to write an algorithm to maximize the value of coins.

1 <= k <= n <= 100000.

The value of the coin is not greater than 10000

Example

Given list = [5,4,3,2,1], k = 2, return 9.

Explanation:

Take two coins from the left.

Given list = [5,4,3,2,1,6], k = 3, return 15.


Explanation:

Take two coins from the left and one from the right.

Observations:

I thought this can be done using DP by the following state transformation:

F[i][j][cnt] = MAX(F[i + 1][j][cnt - 1], F[i][j - 1][cnt - 1])

This will work using a 3D memo array, which gave me a MLE; Then I replaced vector with hash table,
but still get a TLE. So, that clearly indicates that there is an alternative that requires way less
space and time.

Given an array [5, 4, 2, 1, 1, 1, 3, 6], and k = 6, since one can only take element from two ends sequentially:

- From left, one may take [5], [5, 4], [5, 4, 2], [5, 4, 2, 1], [5, 4, 2, 1, 1], [5, 4, 2, 1, 1, 1];

- From right, respectively, one will take [6, 3, 1, 1, 1, 2], [6, 3, 1, 1, 1], [6, 3, 1, 1], [6, 3, 1], [6, 3], [6];

They are actually one to one mapping, say if you pick [5, 4] from left, then definitely, on the right end, [6, 3, 1, 1] will be picked.

Then the question is transformed to:

Finding the max sum of: FromLeft[0 to i] + FromRight[0, k - i - 2], i in [0, k - 2], FromLeft and FromRight are prefix sums from left and right.

and finally comparing the max above with max(FromLeft[k - 1], FromRight[k - 1]), the latter two are the situation that the max
may come entirely from left or right

This is a two pointers with prefix sum, which can be done in linear time and O(K) space.
*/
class SolutionTakeCoins {
public:
	/**
	* @param list: The coins
	* @param k: The k
	* @return: The answer
	*/
	int takeCoins(vector<int> &list, int k) {
		int len = (int)list.size(), ans = 0;
		vector<int> prefixSumLeft(k, 0), prefixSumRight(k, 0);
		std::partial_sum(list.begin(), list.begin() + k, prefixSumLeft.begin());
		std::partial_sum(list.rbegin(), list.rbegin() + k, prefixSumRight.begin());
		for (int i = 0; i < k - 1; ++i) ans = std::max(ans, prefixSumLeft[i] + prefixSumRight[k - i - 2]);
		return std::max(ans, std::max(prefixSumLeft[k - 1], prefixSumRight[k - 1]));
	}
};
