#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/maximum-average-subarray-i
/*
643. Maximum Average Subarray I

Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. And you need to output the maximum average value.

Example 1:

Input: [1,12,-5,-6,50,3], k = 4

Output: 12.75

Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75

Note:
- 1 <= k <= n <= 30,000.
- Elements of the given array will be in the range [-10,000, 10,000].
*/
class SolutionMaximumAverageSubarray1 {
public:
	double findMaxAverage(vector<int>& nums, int k) {
		long long sum = 0LL, ans = 0LL;
		size_t len = nums.size();
		for (int i = 0; i < k; ++i) sum += nums[i];
		ans = sum;
		for (size_t i = k; i < len; ++i) {
			sum += nums[i] - nums[i - k];
			ans = std::max(ans, sum);
		}
		return ans / (double)k;
	}
};
/*
Test cases:

[1,12,-5,-6,50,3]
4
[1,12,-5,-6,50,3]
1
[1,12,-5,-6,50,3]
2
[1,12,-5,-6,50,3]
3
[1,12,-5,-6,50,3]
5
[1,12,-5,-6,50,3]
6
[1,1,1,1,1]
3
[1]
1

Outputs:

12.75
50.0
26.5
15.66667
10.8
9.16667
1.0
1.0
*/