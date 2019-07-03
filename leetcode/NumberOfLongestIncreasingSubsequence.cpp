#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/number-of-longest-increasing-subsequence/
/*
673. Number of Longest Increasing Subsequence

Given an unsorted array of integers, find the number of longest increasing subsequence.

Example 1:


Input: [1,3,5,4,7]

Output: 2

Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].

Example 2:


Input: [2,2,2,2,2]

Output: 5

Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.

Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int.

Observations:

This is a variation of leetcode 300 (Longest Increasing Subsequence, LIS). Since it only asks the number of LIS, it could
potentially solved by DP.

One thing is not clear is whether or not duplicates LIS are counted? By feeding [1,6,3,3,5,7] to OJ, 2 is returned for
LIS = 4, so we know both [1, 3, 5, 7]s are counted. Duplicates count here! If not, this problem could be ranked as Hard?

Use the same DP approach for LIS, a 2-level loop, locks in O(N^2). Given memo as an array of std::pair, at index i,
memo[i].first is the length of LIS ends at nums[i], memo[i].second is the count of the LISs end at nums[i].

Given outer loop i from 0 to len(nums) - 1, Inner loop j looks back from i - 1 to 0. memo is only updated if and only if
nums[j] < nums[i] and memo[j].first + 1 >= memo[i].first. The latter one means by adding nums[i] onto LIS ends at nums[j],
the new LIS ends at nums[i] is longer than or equal to current LIS ends at nums[i].

If memo[j].first + 1 > memo[i].first, a longer LIS is founded, both memo[i].first and memo[j] should be updated to as same
as memo[j]. Note: memo[i].first is NOT equal to memo[j].first + 1, nor memo[j].second!

If memo[j].first + 1 == memo[i].first, there is another path to reach LIS ends at nums[i], which means more count. Therefore,
in this case, only memo[i].second is updated with += memo[j].second.

My first submission, findNumberOfLIS1, only track longest LIS in nums in the loop, then collect count of this LIS in a
separate loop, which is OK since the overall time complexity is O(N^2).

It's actually possible to track the count inside the 2-level loop: once memo[i] is decided, update longest LIS length and
count accordingly.

Official solution has a much more clear explanation for DP and also introduced the segment tree solution, which boosts
the performance to O(NlogN).

https://leetcode.com/problems/number-of-longest-increasing-subsequence/solution/

"

Suppose for sequences ending at nums[i], we knew the length length[i] of the longest sequence, and the number count[i] of such sequences with that length.

For every i < j with A[i] < A[j], we might append A[j] to a longest subsequence ending at A[i]. It means that we have demonstrated count[i] subsequences of length length[i] + 1.

Now, if those sequences are longer than length[j], then we know we have count[i] sequences of this length. If these sequences are equal in length to length[j],
then we know that there are now count[i] additional sequences to be counted of that length (ie. count[j] += count[i]).

"
*/
class SolutionNumberOfLongestIncreasingSubsequence {
public:
	int findNumberOfLIS(const vector<int>& nums) {
		int len = (int)nums.size(), ans = 0, maxlen = 1;
		vector<std::pair<int, int>> memo(len, std::make_pair(1, 1));
		for (int i = 0; i < len; ++i) {
			for (int j = i - 1; j > -1; --j) {
				if (nums[i] > nums[j] && memo[j].first + 1 >= memo[i].first) {
					if (memo[j].first + 1 == memo[i].first) memo[i].second += memo[j].second;
					else {
						memo[i].first = memo[j].first + 1;
						memo[i].second = memo[j].second;
					}
				}
			}
			if (memo[i].first > maxlen) maxlen = memo[i].first, ans = memo[i].second;
			else if (memo[i].first == maxlen) ans += memo[i].second;
		}
		return ans;
	}
	int findNumberOfLIS1(const vector<int>& nums) {
		int len = (int)nums.size(), ans = 0, maxlen = 1;
		vector<std::pair<int, int>> memo(len, std::make_pair(1, 1));
		for (int i = 0; i < len; ++i) {
			for (int j = i - 1; j > -1; --j) {
				if (nums[i] > nums[j] && memo[j].first + 1 >= memo[i].first) {
					if (memo[j].first + 1 == memo[i].first) memo[i].second += memo[j].second;
					else {
						memo[i].first = memo[j].first + 1;
						memo[i].second = memo[j].second;
						maxlen = std::max(maxlen, memo[i].first);
					}
				}
			}
		}
		for (auto p : memo) if (p.first == maxlen) ans += p.second;
		return ans;
	}
};
void TestNumberOfLongestIncreasingSubsequence() {
	SolutionNumberOfLongestIncreasingSubsequence so;
	so.findNumberOfLIS(vector<int> {1, 3, 5, 4, 7});
}
/*
Test cases:

[1,3,5,4,7]
[2,2,2,2,2]
[2,3,4,6,8,2,1]
[2,8,7]
[11,12,13,10,10,10,1,2,3]
[4,5,5,2,1,6,2,1,1,7,8,0,2,3,7,1,3,4,9,1,2,2,5]
[]
[1]
[2,1]
[1,2]
[1,6,3,3,5,7]
[7,3,1,6,3,3,2,3,3,21,5,7,7,7,9,6,7,9,5,4,1,2,3,6,7]
[2,3,4,1,6,7,2,3,3,2,2,5,5,55,8,1,2,0,8,6,5,4,2,1,2,9,4,3,3,4,4,4,6,7,8]

Outputs:

2
5
1
2
2
2
0
1
2
1
2
2
6
*/