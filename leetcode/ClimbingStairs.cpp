#include <vector>

using namespace std;

//https://leetcode.com/problems/climbing-stairs/
/*
70. Climbing Stairs

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Observations:
Seems to be confusing, but you really look at a situation for a given n steps, Count(n) = Count(n - 1) + Count(n - 2) since
you are only allowed to move 1 or 2 step each time. What it looks like? Fibonacci... Yeap!

You could memorize all previous counts, but you really, only need is the last 2 steps. So, this needs O(1), const space.
*/
class SolutionClimbingStairs {
public:
	int climbStairs(int n) {
		if (n < 1)return 1;
		vector<int> memo(n, 1);
		memo[1] = 2;
		for (int i = 2; i < n; ++i) {
			memo[i] = memo[i - 1] + memo[i - 2];
		}
		return memo[n - 1];
	}
};