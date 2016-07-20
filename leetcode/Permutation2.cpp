#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/permutations-ii/
/*
47. Permutations II

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
[1,1,2],
[1,2,1],
[2,1,1]
]

Observations:
Intuitively tried the backtracing "template" for permutation/combination, however had trouble to eliminate
duplicates until I saw the "trick" version of it on leetcode, which do swap once and passing vector nums by
value...Hard to swallow...

Actually, this can be done elegantly through the approach for "next permutation (leetcode 31)". We sort the
array first and then get all next permutation starting from the nondecreasing array. The loop ends if we come
back to nondecreasing order.
*/
class SolutionPermutation2 {
private:
	void nextPermutation(vector<vector<int> > &ans, vector<int> &nums) {
		int len = nums.size();
		while (1) {
			int i = len - 1, j = 0;
			while (nums[i - 1] >= nums[i])--i;
			if (i > 0) {
				j = len - 1;
				while (j >= i && nums[j] <= nums[i - 1])--j;
				std::swap(nums[i - 1], nums[j]);
				std::reverse(nums.begin() + i, nums.end());
				ans.push_back(vector<int>(nums));
			}
			else break;
		}
	}
	//be aware of the tricky argument (second one), nums is passing by value
	void aux(vector<vector<int> > &ans, vector<int> nums, int start, int len) {
		if (start == len - 1) {
			ans.push_back(nums);
			return;
		}
		for (int i = start; i < len; ++i) {
			//duplicate elements detection: if nums[i] == nums[start] and i is greater than start
			//when i == start, it's actually going into the next level without swap, which is necessary
			if (i != start && nums[start] == nums[i])continue;
			//only swap once since nums is passing by value
			std::swap(nums[start], nums[i]);
			this->aux(ans, nums, start + 1, len);
		}
	}
public:
	vector<vector<int> > permuteUnique(vector<int> &nums) {
		vector<vector<int> > ans;
		std::sort(nums.begin(), nums.end());
		//next permutation of nondecreasing order of nums, therefore, we have to manually
		//push it on the ans first
		ans.push_back(vector<int>(nums));
		this->nextPermutation(ans, nums);
		return ans;
	}
	vector<vector<int> > permuteUnique1(vector<int> &nums) {
		vector<vector<int> > ans;
		int len = nums.size();
		if (len > 0) {
			std::sort(nums.begin(), nums.end());
			this->aux(ans, nums, 0, len);
		}
		return ans;
	}
};