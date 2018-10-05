#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/partition-equal-subset-sum/
/*
416. Partition Equal Subset Sum

Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:
Each of the array element will not exceed 100.
The array size will not exceed 200.

Example 1:

Input: [1, 5, 11, 5]

Output: true

Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:

Input: [1, 2, 3, 5]

Output: false

Explanation: The array cannot be partitioned into equal sum subsets.

Observations:

This is a variation of Subset Sum. In order to get an equal partition, the sum of the subset
has to be sum(nums) / 2. It also indicates that if sum(nums) is an odd number, such a subset sum
doesn't exist.

The implemention here is based upon 0-1 knapsack with a rolling array that is filled backward. If
memo[sum] is ever filled with value sum, a valid equal partition is confirmed.

Time complexity is O(sum(nums)N), space complexity is O(sum(nums))

There is a smarter solution based upon bitset out there:

https://leetcode.com/problems/partition-equal-subset-sum/discuss/90590/Simple-C%2B%2B-4-line-solution-using-a-bitset
*/
class SolutionPartitionEqualSubsetSum {
public:
	bool canPartition(vector<int>& nums) {
		int sum = std::accumulate(nums.begin(), nums.end(), 0), len = (int)nums.size();
		if (1 == (1 & sum)) return false;
		sum >>= 1;
		vector<int> memo(sum + 1, 0);
		for (int i = 0; i < len; ++i) {
			for (int j = sum; j >= nums[i]; --j)
				memo[j] = std::max(memo[j], memo[j - nums[i]] + nums[i]);
			if (i < len - 1 && sum == memo[sum]) return true;
		}
		return 0 == len;
	}
};
/*
Test cases:

[1,5,11,5]
[1,2,3,5]
[]
[1]
[1,1]
[1,2]
[1,2,3]
[1,1,1]
[1,2,1]
[1,2,3,4,5]
[5,7,2,1,7,9,9,0,2,3,7,6,5,1,1,2,0,8,7,5]

Outputs:

true
false
true
false
true
false
true
false
true
false
false
*/