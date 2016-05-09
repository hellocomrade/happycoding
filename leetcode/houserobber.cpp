#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
//https://leetcode.com/problems/house-robber/
/*
*You are a professional robber planning to rob houses along a street. Each house has a certain amount of
money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have
security system connected and it will automatically contact the police if two adjacent houses were broken
into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the
maximum amount of money you can rob tonight without alerting the police.

Observation:
Since no adjancent houses can be robbed on the same night,
at house i:
you can either rob maxVal[i - 2] + ValAtHouse[i] or skip house i, that is maxVal[i - 1]
f(i) = max(Houses[i] + f(i - 2), f(i - 1))

Considering the fact that f(k) is in non decreasing order, there is no need to check any previous f(k)
other than f(i - 2) and f(i - 1). Also, we only need to scan the sequence once.

Therefore, this is a linear DP with O(1) extra space
*/
class SolutionHouseRobber
{
public:
	//O(N^2)
	//you can't watch TV while doing algorithm...
	/*
	DP, selection constraint is that no two continuous houses are allowed to be picked together.
	init memo value at index i:
	memo[i] = std::max(nums[i], memo[i - 1]);

	Branch:
	1. if j + 1 < i, then all previous memo[j] can be picked to get max(memo[j] + nums[i])
	2. if j + 1 == i, we can only pick max(memo[i], memo[i - 1]).
	*/
	int rob1(const vector<int>& nums)
	{
		int len = nums.size();
		if (0 == len)return 0;
		vector<long long> memo(len, 0);
		memo[0] = nums[0];
		long long tmp = 0;
		for (int i = 1; i < len; ++i)
		{
			tmp = nums[i];
			memo[i] = std::max(tmp, memo[i - 1]);
			for (int j = i - 2; j > -1; --j)
				memo[i] = std::max(memo[i], memo[j] + tmp);
		}
		return memo[len - 1];
	}
	//O(N)
	//Only the last two results at i -1 and i - 2 are necessary to be kept
	int rob(const vector<int>& nums)
	{
		int len = nums.size();
		if (0 == len)return 0;
		long long last1 = nums[0], last2 = 0LL, maxVal = nums[0];
		for (int i = 1; i < len; ++i, last2 = last1, last1 = maxVal)
			maxVal = std::max(last1, last2 + nums[i]);
		return maxVal;
	}
};
void testHouseRobber()
{
	SolutionHouseRobber robber;
	cout << "Expect 0: " << robber.rob(vector<int>{}) << endl;
	cout << "Expect 1: " << robber.rob(vector<int>{1}) << endl;
	cout << "Expect 9: " << robber.rob(vector<int>{ 1, 2, 3, 4, 5 }) << endl;
	cout << "Expect 2: " << robber.rob(vector<int>{ 1, 2 }) << endl;
	cout << "Expect 3: " << robber.rob(vector<int>{ 3, 2 }) << endl;
	cout << "Expect 4: " << robber.rob(vector<int>{ 3, 2, 1 }) << endl;
	cout << "Expect 100: " << robber.rob(vector<int>{ 3, 100, 1 }) << endl;
	cout << "Expect 14: " << robber.rob(vector<int>{ 3, 4, 1, 1, 2, 9 }) << endl;
	cout << "Expect 104: " << robber.rob(vector<int>{ 2, 2, 100, 2, 2, 2 }) << endl;
	cout << "Expect 190: " << robber.rob(vector<int>{ 2, 99, 100, 2, 72, 88 }) << endl;
	cout << "Expect 194: " << robber.rob(vector<int>{ 1, 99, 2, 3, 7, 1, 88 }) << endl;
}