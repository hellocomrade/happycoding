#include <vector>

using namespace std;

//https://leetcode.com/problems/combinations/
/*
77. Combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
[2,4],
[3,4],
[2,3],
[1,2],
[1,3],
[1,4],
]

Observations:
It's intuitive to come out this "back-tracing" type of solution using recursion.
Given finding k from N, we will have k - 1 from N - 1, k -2 from N - 2, until k == 0.

Everytime we pick one element, we exclude it from the next round, then "remove" it from the result set
once a result has been generated.

In terms of performance, this approach is far from optimized. However, it's pretty generic and can deal with
whatever element set, doesn't have to be from 1 to N.
*/
class SolutionCombinations {
private:
	void aux(vector<vector<int>>& ans, vector<int>& vec, int s, int n, int k, int idx) {
		if (idx == k) {
			ans.push_back(vector<int>(vec));
			return;
		}
		for (int i = s; i <= n; ++i) {
			vec[idx] = i;
			aux(ans, vec, i + 1, n, k, idx + 1);
		}
	}
public:
	vector<vector<int>> combine(int n, int k) {
		vector<vector<int>> ans;
		if (n >= k && k >= 0) {
			if (k > 0) {
				for (int i = 1; i <= n - k + 1; ++i) {
					vector<int> vec(k, 0);
					vec[0] = i;
					aux(ans, vec, i + 1, n, k, 1);
				}
			}
			else
				ans.push_back(vector<int>{});
		}
		return ans;
	}
	//This makes the above codes shorter, but not necessary faster.
	//It does have a smaller memory profile since we moved vec out of the loop and reuse it again and again.
	vector<vector<int> > combine(int n, int k) {
		vector<vector<int>> ans;
		if (n >= k && k >= 0) {
			vector<int> vec(k, 0);
			aux(ans, vec, 1, n, k, 0);
		}
		return ans;
	}
};