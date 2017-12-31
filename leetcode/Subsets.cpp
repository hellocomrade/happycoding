#include <vector>

using namespace std;

//https://leetcode.com/problems/subsets/
/*
78. Subsets

Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

Observations:
Classic backtracing...

Also, can be solved using an iteration approach, given [1, 2, 3] as the array, [] as the seed in ans, then appending each element onto the 
existing elements (each element is a vector) in ans. For example,

Given [[]] as ans, then add 1 based upon [] -> [1], ans is now: [[], [1]]
Then add 2 based upon [], [1] -> [2], [1, 2], ans is now: [[], [1], [2], [1, 2]]
Then add 3 based upon [], [1], [2], [1, 2] -> [3], [1, 3], [2, 3], [1, 2, 3], ans is now: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]

*/
class SolutionSubsets {
private:
    void aux(const vector<int>& nums, vector<vector<int>> &ans, vector<int> &vec, int size, int cnt, int idx) {
        if(0 == cnt) {
            ans.push_back(vector<int>(vec.begin(), vec.begin() + size));
            return;
        }
        for(int i = idx; i < nums.size(); ++i) {
            vec[size - cnt] = nums[i];
            this->aux(nums, ans, vec, size, cnt - 1, i + 1);
        }
    }
public:
    //Backtracing
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        int len = (int)nums.size();
        vector<int> vec(len, 0);
        for(int i = 0; i <= len; ++i)
            this->aux(nums, ans, vec, i, i, 0);
        return ans;
    }
    //Iteration
    vector<vector<int>> subsets1(vector<int>& nums) {
        vector<vector<int>> ans;
        ans.push_back(vector<int>());
        int len = (int)nums.size();
        for(int i = 0, lenv = 0; i < len; ++i) {
            lenv = ans.size();
            for(int j = 0; j < lenv; ++j) {
                vector<int> vec(ans[j]);
                vec.push_back(nums[i]);
                ans.push_back(vec);
            }
        }
        return ans;
    }
};
