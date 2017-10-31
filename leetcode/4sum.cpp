#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/4sum/
/*
18. 4Sum

Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
[-1,  0, 0, 1],
[-2, -1, 1, 2],
[-2,  0, 0, 2]
]

Observations:
Following the same idea of 3sum, sort the array first, then pick 2 (1 for 3sum) elements first, and use a sliding window to pick the remaining two
candidates based upon its relation with target - nums[i] - nums[j], if positive, sliding to left, otherwise, right.

Most of time/error on ruling out the duplicates. Rule of thumb is: if any element in a legit answer get a duplicate, skip it. This applies
on all four element picking. The first two is done by comparing nums[i] with nums[i - 1] and nums[j] with nums[j - 1]. The two in the sliding
window is done by while loops.

Overall time complexity O(N^3).

Also, didn't consider integer overflow at all...
*/
class Solution4Sum {
public:
	/*
	Your input

	[1,0,-1,0,-2,2]
	0
	[0,0,0,0]
	0
	[1,0,-1,0,-2,2]
	0
	[1,0,-1,0,-2,0,1,1,2,2,2,2]
	0
	[]
	0
	[1,2,3]
	0
	Your answer

	[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
	[[0,0,0,0]]
	[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
	[[-2,-1,1,2],[-2,0,0,2],[-2,0,1,1],[-1,0,0,1]]
	[]
	[]
	*/
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int>> ans;
		int len = nums.size();
		if (len < 4) return ans;
		std::sort(nums.begin(), nums.end());
		int t1 = 0, t2 = 0, l = 0, r = 0, m = 0, n = 0;
		for (int i = 0; i < len - 3; ++i) {
			if (i > 0 && nums[i - 1] == nums[i])continue;
			for (int j = i + 1; j < len - 2; ++j) {
				if (j > i + 1 && nums[j - 1] == nums[j])continue;
				t1 = target - nums[i] - nums[j];
				l = j + 1, r = len - 1;
				while (l < r) {
					m = nums[l], n = nums[r], t2 = m + n;
					if (t1 == t2) {
						//cout << nums[i] << ',' << nums[j] << ',' << m << ',' << n << endl;
						ans.push_back(vector<int>{nums[i], nums[j], m, n});
						while (l < r && m == nums[l])++l;
						while (r > l && n == nums[r])--r;
					}
					else if (t1 > t2)
						++l;
					else
						--r;
				}
			}
		}
		return ans;
	}
};