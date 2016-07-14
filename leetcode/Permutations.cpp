#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/permutations/
/*
46. Permutations

Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
[1,2,3],
[1,3,2],
[2,1,3],
[2,3,1],
[3,1,2],
[3,2,1]
]

Observations:
Classic backtracing. On each level i, we decide the element at level i by swapping elements from i to len - 1, given
len is the size of the array. We then move on and reverse the swap when the recursion in deeper levels are done
*/
class SolutionPermutations {
private:
	void aux(vector<vector<int> > &ans, vector<int> &nums, int idx) {
		int len = nums.size();
		if (idx == len - 1) {
			ans.push_back(vector<int>(nums));
			return;
		}
		for (int i = idx; i < len; ++i) {
			//in order to simplify the coding, we intentionally leave swap nums[idx] and nums[idx]
			std::swap(nums[idx], nums[i]);
			this->aux(ans, nums, idx + 1);
			std::swap(nums[idx], nums[i]);
		}
	}
public:
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int> > ans;
		int len = nums.size();
		if (len > 0)
			this->aux(ans, nums, 0);
		return ans;
	}
};