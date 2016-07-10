#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/combination-sum/
/*
39. Combination Sum

Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7,
A solution set is:
[
[7],
[2, 2, 3]
]

Observations:
Be aware that the element inside the array can be reused unlimited times. Therefore, if the element is 1 and the target is 5,
you will see [1,1,1,1,1] along with other solutions using 1 to fill the gaps...

Backtrace through recursion. It sounds a wise idea to sort the array first then we can safely ignore all elements that are greater
than the target considering the fact that all elements are positive.

By choosing an element K, we decrease the target to target - K before making the next choice. We recognize a valid solution
only if target is equal to 0 at certain point.

Comparing with the solution for combination, we allow duplicates here. Therefore, for any given elements K in the array that is no
greater than the target, it will be chosen  target / K times. So, we have to resume the status of the vector by a range remove.
*/
class SolutionCombinationSum {
private:
	void aux(vector<vector<int> > &ans, vector<int> &vec, vector<int>::iterator begin, vector<int>::iterator end, int target) {
		if (target == 0) {
			ans.push_back(vector<int>(vec));
			return;
		}
		for (auto i = begin; i <= end && *i <= target; ++i) {
			int s = vec.size();
			for (int j = *i; j <= target; j += *i) {
				vec.push_back(*i);
				aux(ans, vec, i + 1, end, target - j);
			}
			//remove all elements added at this recursion
			vec.erase(vec.begin() + s, vec.end());
		}
	}
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int> > ans;
		if (candidates.size() > 0 && target > 0) {
			std::sort(candidates.begin(), candidates.end());
			if (candidates[0] > target)return ans;
			//using lower_bound to find the first element in the array that is no less than target
			//if nothing found, the return is end. So we have to decrease it by 1 if it occurs.
			auto end = std::lower_bound(candidates.begin(), candidates.end(), target);
			if (end == candidates.end())--end;
			vector<int> vec;
			aux(ans, vec, candidates.begin(), end, target);
		}
		return ans;
	}
};