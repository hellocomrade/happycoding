#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/combination-sum-ii/
/*
40. Combination Sum II

Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8,
A solution set is:
[
[1, 7],
[1, 2, 5],
[2, 6],
[1, 1, 6]
]

Observations:
Again, backtracing. Comparing with Combination Sum (39), this one doesn't allow take element for more than one time.
That has been said, the duplicates in the array will play a big role here. In fact, by having this one done, I found
a flow in 39: the AC solutions can't handle the case like: [1,1,2], 3

The "correct" answer is: [[1,1,1],[1,1,1],[1,1,1],[1,2],[1,1,1],[1,2]], which contains a lot of repeated answers! More
clarification is necessary like: no duplicates in the array.

This one, however, does have duplicates in array for sure. The question is: if we follow the same approach for 39, how
could we rule out the duplicates?

For a test case: [7,1,2,5,1,6,10], 8; without considering the extra duplicates, you will get:

[[1,1,6],[1,2,5],[1,2,5],[1,7],[1,7],[2,6]]

But the correct answer should be: [[1,1,6],[1,2,5],[1,7],[2,6]].

How could this happen? Well, backtracing can be considered as making a choice level by level through recursion. Say, we pick
1 (the first element in the array) on level 1, then we could pick 1 (the second element) on level 2 and 6 on level 3, then
we form [1,1,6]. This is the same for [1,2,5]. But, when we move to the second choice on level 1, we get 1 (the second element).
we could still pick 2 on level 2 and 5 on level 3! Duplicated combination occurs!

How could we avoid this? We will have to remove the possibility of choosing the same number at the same level. We are not talking about
removing the duplicates from the array. That's wrong, coz you will miss [1,1,6]! We just want to make sure we won't choose the same number
more than once at each level!

The implementation is fairly easy: since we sort the array already, we can easily tell if the currrent candidate is as same as the last one.
If so, we simply skip it and move on. This is actually the only difference between 39 and 40 in terms of implementation :)

Subtle but important.
*/
class SolutionCombinationSum2 {
private:
	void aux(vector<vector<int> > &ans, vector<int> &vec, vector<int>::iterator start, vector<int>::iterator end, int target) {
		if (target == 0) {
			ans.push_back(vector<int>(vec));
			return;
		}
		int last = -1;
		for (auto i = start; i <= end && target >= *i; ++i) {
			//if duplicates found at the same level, just skip it.
			if (last == *i)continue;
			last = *i;
			vec.push_back(*i);
			aux(ans, vec, i + 1, end, target - *i);
			vec.pop_back();
		}
	}
public:
	/**
	* @param num: Given the candidate numbers
	* @param target: Given the target number
	* @return: All the combinations that sum to target
	*/
	vector<vector<int> > combinationSum2(vector<int> &num, int target) {
		int len = num.size();
		vector<vector<int> > ans;
		if (len > 0 && target > 0) {
			std::sort(num.begin(), num.end());
			if (num[0] > target)return ans;
			auto end = std::lower_bound(num.begin(), num.end(), target);
			while (end == num.end() || *end > target)--end;
			vector<int> vec;
			aux(ans, vec, num.begin(), end, target);
		}
		return ans;
	}
};
void TestCombinationSum2() {
	vector<int> vec{ 10, 1, 6, 7, 2, 1, 5 };
	SolutionCombinationSum2 so;
	vector<vector<int> > ans = so.combinationSum2(vec, 8);
	assert(ans.size() == 4);
}