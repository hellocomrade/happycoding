#include <cassert>
#include <numeric>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/target-sum/
/*
494. Target Sum

You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:

Input: nums is [1, 1, 1, 1, 1], S is 3.

Output: 5

Explanation:

-1+1+1+1+1 = 3

+1-1+1+1+1 = 3

+1+1-1+1+1 = 3

+1+1+1-1+1 = 3

+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.

Note:

- The length of the given array is positive and will not exceed 20.
- The sum of elements in the given array will not exceed 1000.
- Your output answer is guaranteed to be fitted in a 32-bit integer.

Observations:

It's intuitive to construct a top down recursion solution:

Given Fun(K, j) as the function to calculate number of result equal to K on array nums from [0, j]

Fun(S - nums[i], i - 1) + Fun(S + nums[i], i - 1)

is the resusive solution Fun(S, len(nums) - 1);

A catch is when nums[i] = 0, since +0 and -0 are the same, 2 instead of 1 count should be added

See findTargetSumWays2.

The problem of this solution is the space it takes, not to mention the fact this is still a simulation to
exhaust all possibilities with the optimization using memorization to avoid repeated calculation.

Let's discuss space here first:

1. Using bottom up approach to eliminate space for resursion stack, see findTargetSumWays1. The idea is:
at any given index i, all possible sum Si are tracked. At the end, one can find out whether S could be
a sum result at i = len(nums) - 1. See findTargetSumWays1.

2. The memorized results are the number of possibilities given a sum Si at index i. For any given index i,
the number of Si is unknown. Even the problem defines this number is between [-1000, 1000], a hash table
would still be my choice. Therefore, for any given index i, a hash table is required.

It's actually possible to use only 2 hash tables, see findTargetSumWays0. By taking a close look, one shall
discover that only the immediately previous hash table is needed. However, in order to avoid overwriting on
hash table, I takes two of them and swap them at the end of each iteration.

Now, space issue seems to be solved, but it's still slow due to the fact that all solutions so far are based upon
the simulation: a backtracing approach. Ususally, when the problem asks the number only, there should be a solution
better than backtracing. DP is usually the first consideration. The approach here using DP is a bit tricky:

https://leetcode.com/problems/target-sum/discuss/97334/Java-(15-ms)-C%2B%2B-(3-ms)-O(ns)-iterative-DP-solution-using-subset-sum-with-explanation

Given sum1 as the sub sequence in array nums with all '+' sign, and sum2 as the remainig sub sequence that will apply '-' sign,
we will have the following:

sum1 - sum2 = S

sum1 - sum2 + sum1 + sum2 = S + sum1 + sum2

2 * sum1 = S + sum

sum1 = (S + sum) / 2

Surprisingly, at the end, we transform this problem to: find the number of subsets in nums, whose sum is equal to (S + sum(nums)) / 2.
This is a variation of "Subset Sum" problem, see leetcode 416 (Partition Equal Subset Sum) for a taste.

Then, based upon 01 knapsack, one can calculate the number of possibilities to reach (S + sum(nums)) / 2 for a subset in nums.

This algorithm takes O((S + sum(nums)) / 2 * N) time and O((S + sum(nums)) / 2) space, which is way faster
than previous solutions.
*/
class SolutionTopSum {
public:
	//Variation of subset sum
	int findTargetSumWays(const vector<int>& nums, int S) {
		int sum = std::accumulate(nums.begin(), nums.end(), 0);
		if (S > sum || 1 == (1 & (S + sum))) return 0;
		sum = (sum + S) >> 1;
		vector<int> memo(sum + 1, 0);
		memo[0] = 1;
		for (int n : nums)
			for (int i = sum; i >= n; --i)
				memo[i] += memo[i - n];
		return memo[sum];
	}
	//Bottom up memorization with saving space
	int findTargetSumWays0(const vector<int>& nums, int S) {
		int len = (int)nums.size();
		unordered_map<int, int> memo, memo1;
		memo[0] = 1;
		for (int i = 0; i < len; ++i) {
			for (auto p : memo) {
				memo1[p.first + nums[i]] = 0 == memo1.count(p.first + nums[i]) ? p.second : p.second + memo1[p.first + nums[i]];
				memo1[p.first - nums[i]] = 0 == memo1.count(p.first - nums[i]) ? p.second : p.second + memo1[p.first - nums[i]];
			}
			std::swap(memo, memo1);
			memo1.clear();
		}
		return len > 0 && 1 == memo.count(S) ? memo[S] : 0;
	}
	//Bottom up memorization without saving space
	int findTargetSumWays1(vector<int>& nums, int S) {
		int len = (int)nums.size();
		vector<unordered_map<int, int> > memo(len, unordered_map<int, int>());
		auto fun = [&nums, &memo](int r, int idx, const auto& f) {
			if (0 == idx) {
				if (0 == r && 0 == nums[0]) return 2;
				else return std::abs(r) == std::abs(nums[0]) ? 1 : 0;
			}
			int i = 1 == memo[idx - 1].count(r - nums[idx]) ? memo[idx - 1][r - nums[idx]] : f(r - nums[idx], idx - 1, f);
			int j = 1 == memo[idx - 1].count(r + nums[idx]) ? memo[idx - 1][r + nums[idx]] : f(r + nums[idx], idx - 1, f);
			memo[idx - 1][r - nums[idx]] = i;
			memo[idx - 1][r + nums[idx]] = j;
			return i + j;
		};
		return 0 == len ? 0 : fun(S, len - 1, fun);
	}
	//Topdown memorization
	int findTargetSumWays2(vector<int>& nums, int S) {
		int len = (int)nums.size();
		vector<unordered_map<int, int> > memo(len, unordered_map<int, int>());
		auto fun = [&nums, &memo](int r, int idx, const auto& f) {
			if (0 == idx) {
				if (0 == r && 0 == nums[0]) return 2;
				else return std::abs(r) == std::abs(nums[0]) ? 1 : 0;
			}
			int i = 1 == memo[idx - 1].count(r - nums[idx]) ? memo[idx - 1][r - nums[idx]] : f(r - nums[idx], idx - 1, f);
			int j = 1 == memo[idx - 1].count(r + nums[idx]) ? memo[idx - 1][r + nums[idx]] : f(r + nums[idx], idx - 1, f);
			memo[idx - 1][r - nums[idx]] = i;
			memo[idx - 1][r + nums[idx]] = j;
			return i + j;
		};
		return 0 == len ? 0 : fun(S, len - 1, fun);
	}
};
void TestTopSum() {
	SolutionTopSum so;
	assert(5 == so.findTargetSumWays(vector<int>{1, 1, 1, 1, 1}, 3));
	assert(256 == so.findTargetSumWays(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 1}, 1));
}
/*
Test cases:

[0,0,0,0,0,0,0,0,1]
1
[0,1,0,2]
3
[0,0,2]
2
[1,1,1,1,1]
3
[1,1,1,1,1]
2
[1,1,1,1,1]
1
[1,1,1,1,1]
0
[1,1,1,1,1]
4
[1,1,1,1,1]
5
[1,1,1,1,1]
6
[1,1,1,1,1,1]
0
[]
5
[1]
1
[1]
-1
[1]
0
[3,4,5,1,2,6,2,3,4]
10
[1,2,3,4,4,3,2,1]
10

Outputs:

256
4
4
5
0
10
0
0
1
0
20
0
1
1
0
25
12
*/