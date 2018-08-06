#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/combination-sum-iv
/*
377. Combination Sum IV

Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:

(1, 1, 1, 1)

(1, 1, 2)

(1, 2, 1)

(1, 3)

(2, 1, 1)

(2, 2)

(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.

Follow up:
- What if negative numbers are allowed in the given array?
- How does it change the problem?
- What limitation we need to add to the question to allow negative numbers?

Observations:

The discovery of all possible combinations is back tracing. However, that is not what this prblem asks! It only asks the total count.

The naive approach, which is implemented in combinationSum4_Naive will do complete search on all 2^N possibilities. It's a TLE even with
early exit included.

A memorization/DP is needed.

combinationSum4_memo demonstrates the top-down DP. It actually does the complete search but can return earlier if the remaining number has
been calculated already.

A more elegant solution is bottom-up DP, in combinationSum4. This approach builds up from 1 to target. Sorting is not really necessary.
*/
class SolutionCombinationSum4 {
private:
	void aux_memo(const vector<int>& nums, unordered_map<long long, long long>& memo, long long remaining, long long& ans) {
		if (0 < remaining) {
			if (1 == memo.count(remaining)) ans += memo[remaining];
			else {
				for (int i : nums) {
					if (0 == remaining - i) ++ans;
					else if (remaining - i < 0) break;
					else this->aux_memo(nums, memo, remaining - i, ans);
				}
			}
		}
	}
	void aux_naive(const vector<int>& nums, long long remaining, long long& ans) {
		if (0 < remaining) {
			for (int i : nums) {
				if (0 == remaining - i) ++ans;
				else if (remaining - i < 0) break;
				else this->aux_naive(nums, remaining - i, ans);
			}
		}
	}
public:
	/*
	Bottom-up DP O(target*N) time (sorting can be ignored) and O(target) space
	Since all numbers can be used as many times as possible,
	memo[target] = memo[target - nums[0]] + memo[target - nums[1]] ... + memo[target - nums[len(nums) - 1]]
	memo can be populated in a bottom up fashion starting from target = 1

	memo[0] = 1 is equivalent to:
	memo[i] += (0 == i - j) ? 1 : memo[i - j].
	*/
	int combinationSum4(vector<int>& nums, int target) {
		std::sort(nums.begin(), nums.end());
		vector<long long> memo(target + 1, 0);
		memo[0] = 1LL;
		for (int i = 1; i <= target; ++i) {
			for (int j : nums) {
				if (j > i) break;
				memo[i] += memo[i - j];
			}
		}
		return target < 0 ? 0 : static_cast<int>(memo[target]);
	}
	//Top down memorization/DP
	int combinationSum4_memo(vector<int>& nums, int target) {
		long long ans = 0;
		std::sort(nums.begin(), nums.end());
		unordered_map<long long, long long> memo;
		for (int i = 1; i <= target; memo[i++] = ans, ans = 0LL) this->aux_memo(nums, memo, i, ans);
		return static_cast<int>(memo[target]);
	}
	//Naive 2^N, got TLE, too good to be true
	int combinationSum4_Naive(vector<int>& nums, int target) {
		long long ans = 0;
		std::sort(nums.begin(), nums.end());
		this->aux_naive(nums, target, ans);
		return static_cast<int>(ans);
	}
};