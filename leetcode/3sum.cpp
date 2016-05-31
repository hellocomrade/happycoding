#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/3sum/
/*
15. 3Sum

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
The solution set must not contain duplicate triplets.
For example, given array S = {-1 0 1 2 -1 -4},

A solution set is:
(-1, 0, 1)
(-1, -1, 2)

Observations:
It's on wiki, https://en.wikipedia.org/wiki/3SUM
O(N^2) with O(1) space (without considering returning array)

Having a number iterating from index i: 0 to (len - 3), and put two pointers at index j = i + 1 and k = len - 1.
We check the sum of nums[i] + nums[j] + nums[k], if equal to zero, add to the result, otherwise,

if sum >= 0, --k, move k to a smaller number and scan the numbers between j and k again;
if sum <= 0, ++j, move j to a greater number and scan the numbers between j and k again;

It doesn't matter sum == 0 falls into any of the branches, either of them will work.

In order to remove duplicates in the result, everytime we move i, j, k, we moave them to an index having a
value that is different than the previous.

*/
class Solution3Sum{
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		int len = nums.size();
		vector<vector<int> > ans;
		if (len < 3)return ans;
		sort(nums.begin(), nums.end());
		int j = 0, k = 0, prevj = 0, prevk = 0;
		long long sum = 0;
		for (int i = 0; i < len - 2; ++i)
		{
			if (i > 0 && nums[i] == nums[i - 1])continue;
			j = i + 1;
			k = len - 1;
			while (j < k)
			{
				sum = (long long)nums[i] + (long long)nums[j] + (long long)nums[k];
				if (sum == 0)
					ans.push_back({ nums[i], nums[j], nums[k] });
				prevj = nums[j], prevk = nums[k];
				if (sum > 0)
				{
					while (j < k && nums[k] == prevk)
						--k;
				}
				else
				{
					while (j < k && nums[j] == prevj)
						++j;
				}
			}
		}
		return ans;
	}
};
void Test3Sum()
{
	Solution3Sum so;
	vector<int> vals{ 1, -2, 4, -7, 1, 3 };
	vector<vector<int> > ret = so.threeSum(vals);
	vector<int> vals3{ -1, -1, -1, -1, 0, 0, 1, 1, 1, 1 };
	vector<vector<int> > ret3 = so.threeSum(vals3);
	vector<int> vals4{ -2, -3, 5, -1, -4, 5, -11, 7, 1, 2, 3, 4, -7, -1, -2, -3, -4, -5 };
	vector<vector<int> > ret4 = so.threeSum(vals4);
}