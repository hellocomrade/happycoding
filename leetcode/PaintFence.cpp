//https://www.lintcode.com/problem/paint-fence/description
/*
276. Paint Fence

Description

There is a fence with n posts, each post can be painted with one of the k colors.
You have to paint all the posts such that no more than two adjacent fence posts have the same color.
Return the total number of ways you can paint the fence.

n and k are non-negative integers.

Example:

Given n=3, k=2 return 6

post 1, post 2, post 3
way1	0       0       1
way2    0       1       0
way3    0       1       1
way4    1       0       0
way5    1       0       1
way6    1       1       0

Observations:

This is not a free problem on leetcode. Again, fortunately, lintcode offers it for free.

Since only the total number of ways is asked, definitely not backtracing. It's probably similar to leetcode 377 (Combination Sum IV),
which is solved by BP instead.

At any given post m, assuming the total number at post (m - 1) is N. Among these N combinations so far, one can always do different colors
at post m, which is

N * (k - 1)

How about the number of combinations that same color can be applied? According to the problem statement, "no more than two adjacent fence posts have the same color",
which means the same color can only be applied onto the post (m + 1) if and only if the different colors were applied on post m comparing with post (m - 1).

Given P as the number of combinations that apply different color at post m, the same color can be applied on post (m + 1).

Therefore, the overall number at post (m + 1) is:

N * (k - 1) + P

in which, P = N' * (k - 1), N' is the total number at post (m - 1).

So, in order to solve this problem, at each post, one has to track the number of combinations that apply the different colors at the previous post along with
the total number so far, which is used to compute the number for applying different color at current post.

As for the initial state, post 1 always have k possiblities. It's not hard to figure out that at post 2:
the previous different color (post 1) is k.
*/
class SolutionPaintFence {
public:
	/**
	* @param n: non-negative integer, n posts
	* @param k: non-negative integer, k colors
	* @return: an integer, the total number of ways
	*/
	int numWays(int n, int k) {
		long long ans = k, sameColor = 0, diffColor = k;
		for (int i = 2; i <= n; ++i) {
			sameColor = diffColor;
			diffColor = 1LL * ans * (k - 1);
			ans = diffColor + sameColor;
		}
		return 1 > n ? 0 : static_cast<int>(ans);
	}
};