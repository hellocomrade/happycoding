#include <vector>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/continuous-subarray-sum
/*
523. Continuous Subarray Sum

Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k,
that is, sums up to n*k where n is also an integer.

Example 1:

Input: [23, 2, 4, 6, 7],  k=6

Output: True

Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.

Example 2:

Input: [23, 2, 6, 4, 7],  k=6

Output: True

Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.

Note:

- The length of the array won't exceed 10,000.

- You may assume the sum of all the numbers is in the range of a signed 32-bit integer.

Observations:

Modulo accumulation is not very rare in CP...subarray sum is mentioned, then prefix sum array shall be considered.

It's not hard to find the subarray sums using prefix sum array, however, in order to check k and all nks, it may take up to O(INT_MAX / k)
time per index.

PrefixSum[i] - PrefixSum[j] = -nk, -(n - 1)k,..., 0, k, 2k, ..., nk

Is there a way to simply right side of the equation to a constant so only one comparison is necessary per index?

Given PrefixSum as the prefix sum array for nums, the problem can be translated to look for a subarray that satisfies:

PrefixSum[i] - PrefixSum[j] = nk, i - j > 1

or

PrefixSum[i] - 0 = nk, i > 1

If one takes modulo operation on both sides of the equation:

PrefixSum[i] % k - PrefixSum[j] % k = 0;

or

PrefixSum[i] % k - 0 = 0;

Given [3, 7] and k = 2

(3 + 7) % 2 <==> ((3 % 2) + 7) % 2 <-- Modulo accumulation

Therefore, given PrefixSum[i] % k = m, if such a m exists in previous prefix sum, and index diff is more than 1, such a valid subarray is found.

Hashtable can be used to store previous modulos. Such a hashtable shall be fed with (0, -1) at beginning, which represents the empty prefix sum before index 0.
-1 is given to satisfy the contraint (i - j) > 1 for the case PrefixSum[i] - 0 = nk, i > 1.

If a duplicate key shows up, it shall be discarded since the existing pair has a smaller index and is on a better position to satisfy i - j > 1 or i > 1.

Edge case:

0 == k, in this case, modulo operator is now allowed, fortunately, regular sum operation works for this case since all elements are non-negative. One
shall look for 0 in nums;
*/
class SolutionContinuousSubarraySum {
public:
	bool checkSubarraySum(vector<int>& nums, int k) {
		unordered_map<int, int> remainders;
		remainders.emplace(0, -1);
		int sum = 0, len = (int)nums.size();
		for (int i = 0; i < len; ++i) {
			sum = 0 != k ? (sum + nums[i]) % k : sum + nums[i];
			if (1 == remainders.count(sum)) {
				if (i - remainders[sum] > 1) return true;
			}
			else remainders.emplace(sum, i);
		}
		return false;
	}
};
/*
Test cases:

[23,2,4,6,7]
6
[23, 2, 6, 4, 7]
-6
[23, 2, 6, 4, 7]
6
[1,2]
3
[1,2,3]
6
[1,2,3]
-6
[0,0]
0
[0,0,0]
0
[]
1
[1,4,7,8,9,32]
16

Outputs:

true
true
true
true
true
true
true
true
false
false
*/