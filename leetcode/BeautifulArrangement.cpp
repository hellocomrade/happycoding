#include <vector>

using namespace std;

//https://leetcode.com/problems/beautiful-arrangement
/*
526. Beautiful Arrangement

Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 <= i <= N) in this array:

The number at the ith position is divisible by i.
i is divisible by the number at the ith position.
Now given N, how many beautiful arrangements can you construct?

Example 1:

Input: 2

Output: 2

Explanation:

The first beautiful arrangement is [1, 2]:

Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).

Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).

The second beautiful arrangement is [2, 1]:

Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).

Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.

Note:

N is a positive integer and will not exceed 15.

Observations:

One can recognize this easily as backtracing. Moreover, since the answer it asks is the total count, complete search might
not be necessary, just like CombinationSum4, turns out to be a DP.

That has been said, after an exhausted searching and trying, BT appears to be the solution...
*/
class SolutionBeautifulArrangement {
public:
	int countArrangement(int N) {
		int ans = 0;
		vector<bool> memo(N + 1, false);
		auto bt = [&memo, &ans, N](int i, auto& fun) {
			if (i > N) {
				++ans;
				return;
			}
			for (int j = 1; j <= N; ++j) {
				if (false == memo[j] && (0 == j % i || 0 == i % j)) {
					memo[j] = true;
					fun(i + 1, fun);
					memo[j] = false;
				}
			}
		};
		bt(1, bt);
		return ans;
	}
};