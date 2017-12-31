#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/subsets-ii/
/*
90. Subsets II

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

Observations:
Still backtracing, comparing with Subsets (leetcode 78), this one introduced the duplicates, which can be handled by sorting the input array
first then skip the duplicates by comparing with the previous elements. Therefore, for a given size combination, we can be sure that no
duplicate can be positioned with the same index.

I use i + size - cnt <= len as the exit condition in function aux to achieve a slightly faster algorithm. Also, I use a vector vec with a
predefined size, which is as long as input nums. By doing so, the dynmaic allocation part of vec is not necessary. No push_back and pop_back.

Of course, as Subsets, there should be an interation version of Subsets2. I will try to finish that in Python.
*/
class SolutionSubsets2 {
private:
    void aux(const vector<int> &nums, vector<vector<int>> &ans, vector<int> &vec, int size, int idx, int cnt) {
        if(cnt == size) {
            ans.push_back(vector<int>(vec.begin(), vec.begin() + size));
            return;
        }
        int len = nums.size();
        for(int i = idx; i + size - cnt <= len; ++i) {
            if(i != idx && nums[i] == nums[i - 1])continue;
            vec[cnt] = nums[i];
            this->aux(nums, ans, vec, size, i + 1, cnt + 1);
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int len = nums.size();
        vector<vector<int>> ans;
        vector<int> vec(len, 0);
        for(int i = 0; i <= len; ++i)this->aux(nums, ans, vec, i, 0, 0);
        return ans;
    }
};
