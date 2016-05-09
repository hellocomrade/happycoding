#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
//https://leetcode.com/problems/house-robber-ii/
/*
Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so 
that he will not get too much attention. This time, all houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the 
maximum amount of money you can rob tonight without alerting the police.

Observations:
Since this is an extension of houserobber, it's intutive to apply the same approach on this one. However, since
all houses are in a circle, there is one more constraint: the house at index 0 and index len - 1 can not be robbed
together.

After a closer look, this is what you can try:
House with index len - 1 will not be robbed, therefore DP from index 0 to index len - 2 to get the maxVal1;
House wih index 0 will not be robbed, therefore DP from index 1 to index len - 1 to get the maxVal2;
Finally, we pick the greater one between maxVal1 and maxVal2;
*/
using LL_Pair = std::pair<long long, bool>;
class SolutionHouseRobber2
{
public:
	//O(N^2), watching TV is banned while doing algorithm!
	int rob1(const vector<int>& nums)
	{
		int len = nums.size();
		if (0 == len)return 0;
		vector<LL_Pair> memo;
		vector<long long> memo1(len, 0);
		memo.emplace_back(nums[0], true);
		memo1[0] = 0;
		for (int i = 1; i < len; ++i)
		{
			if (memo[i - 1].first > nums[i])
				memo.push_back(memo[i - 1]);
			else
				memo.emplace_back(nums[i], false);
			memo1[i] = std::max(memo1[i - 1], (long long)nums[i]);

			for (int j = i - 2; j > -1; --j)
			{
				if (memo[j].first + nums[i] > memo[i].first)
				{
					if (i != len - 1 || false == memo[j].second)
						memo[i] = std::make_pair(memo[j].first + nums[i], memo[j].second);
				}
				memo1[i] = std::max(memo1[i], memo1[j] + nums[i]);
			}

		}
		for (int i = len - 3; i > 0; --i)
			memo[len - 1].first = std::max(memo1[i] + nums[len - 1], memo[len - 1].first);
		return memo[len - 1].first;
	}
	int rob2(const vector<int>& nums)
	{
		int len = nums.size();
		if (0 == len)return 0;
		LL_Pair last1 = std::make_pair(nums[0], true);
		LL_Pair maxVal1 = last1;
		LL_Pair last2 = std::make_pair(0, false);
		long long prev1 = 0LL, prev2 = 0LL, maxVal2 = 0LL;
		long long maxVal = nums[0];
		for (int i = 1; i < len; ++i, last2 = last1, last1 = maxVal1, prev2 = prev1, prev1 = maxVal2)
		{
			if (i != len - 1)
			{
				if (last1.first > last2.first + nums[i])
					maxVal1 = std::make_pair(last1.first, last1.second);
				else
					maxVal1 = std::make_pair(last2.first + nums[i], last2.second);
				maxVal2 = std::max(prev1, prev2 + nums[i]);
			}
			else
			{
				if (false == last2.second)
					maxVal = std::max(last1.first, last2.first + nums[i]);
				else
					maxVal = last1.first;
				maxVal = std::max(std::max(prev1, prev2 + nums[i]), maxVal);
			}
		}
		return maxVal;
	}
	int rob(const vector<int>& nums)
	{
		int len = nums.size();
		if (0 == len)return 0;
		long long last1 = nums[0], last2 = 0LL;
		long long maxVal1 = nums[0], maxVal2 = 0LL;
		for (int i = 1; i < len - 1; last2 = last1, last1 = maxVal1, ++i)
			maxVal1 = std::max(last2 + nums[i], last1);
		if (len > 1)
		{
			last1 = nums[1], last2 = 0LL, maxVal2 = nums[1];
			for (int i = 2; i < len; last2 = last1, last1 = maxVal2, ++i)
				maxVal2 = std::max(last2 + nums[i], last1);
		}
		return std::max(maxVal1, maxVal2);
	}
};
void testHouseRobber2()
{
	SolutionHouseRobber2 robber;
	cout << "Expect 0: " << robber.rob(vector<int>{}) << endl;
	cout << "Expect 1: " << robber.rob(vector<int>{ 1 }) << endl;
	cout << "Expect 2: " << robber.rob(vector<int>{ 1, 2 }) << endl;
	cout << "Expect 3: " << robber.rob(vector<int>{ 1, 2, 3 }) << endl;
	cout << "Expect 100: " << robber.rob(vector<int>{ 1, 100, 3 }) << endl;
	cout << "Expect 8: " << robber.rob(vector<int>{ 1, 2, 3, 4, 5 }) << endl;
	cout << "Expect 15: " << robber.rob(vector<int>{ 1, 2, 3, 4, 5, 6, 7 }) << endl;
	cout << "Expect 8: " << robber.rob(vector<int>{ 5, 2, 3, 1 }) << endl;
	cout << "Expect 6: " << robber.rob(vector<int>{ 1, 2, 3, 4 }) << endl;
	cout << "Expect 10: " << robber.rob(vector<int>{ 2, 2, 4, 3, 2, 5 }) << endl;
}