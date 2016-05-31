#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/3sum-closest/
/*
16. 3Sum Closest

Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

Observation:
Variation of 3sum. Since no need to return the result without duplicates, we could simply remove all checks
for preventing duplicates, which makes the codes shorter.
*/
class Solution3SumClosest {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int len = nums.size();
		if (len < 4)
			return accumulate(nums.begin(), nums.end(), 0);
		sort(nums.begin(), nums.end());
		long long sum3 = 0, sum = 0;
		long long diff = numeric_limits<int>::max();
		int i = 0, j = 0;
		for (int m = 0; m < len - 2; ++m)
		{
			i = m + 1;
			j = len - 1;
			while (i < j)
			{
				sum = (long long)nums[i] + (long long)nums[j] + (long long)nums[m];
				if (abs(sum - (long long)target) < diff)
				{
					if (sum == target)
						return sum;
					sum3 = sum;
					diff = abs(sum3 - target);
				}
				sum < target ? ++i : --j;
			}
		}
		return sum3;
	}
};
void Test3SumClosest()
{
	Solution3SumClosest so;
	//Two test cases with exact matches.
	vector<int> vals1{ 1, 2, 4, 8, 16, 32, 64, 128 };
	cout << "Expect 82: " << so.threeSumClosest(vals1, 82) << endl;
	vector<int> vals2{ 1, 2, 4, 8, -16, 32, -64, 128 };
	cout << "Expect 24: " << so.threeSumClosest(vals2, 24) << endl;
}