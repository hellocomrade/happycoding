#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//https://leetcode.com/problems/perfect-squares
/*
279. Perfect Squares

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12

Output: 3

Explanation: 12 = 4 + 4 + 4.

Example 2:

Input: n = 13

Output: 2

Explanation: 13 = 4 + 9.

Observations:

I didn't expect DP solution could be passed considering the fact n could be any positive integer.
Time complexity is O(N^1.5) since it runs:

sqrt(1) + sqrt(2) + ... + sqrt(N) <= N*sqrt(N) = N^1.5

There is a faster mathematical solution based upon Lagrange's Four Square Theorem, that only
4 possible outcome for any positive integer: 1, 2, 3, 4:

https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem

https://leetcode.com/problems/perfect-squares/discuss/71488/Summary-of-4-different-solutions-(BFS-DP-static-DP-and-mathematics)
*/
class SolutionPerfectSquares {
public:
	int numSquares(int n) {
		vector<long long> memo(n + 1L, n + 1L);
		memo[0] = 0L;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j * j <= i; ++j)
				memo[i] = std::min(memo[i], memo[i - j * j] + 1L);
		return static_cast<int>(memo[n]);
	}
};