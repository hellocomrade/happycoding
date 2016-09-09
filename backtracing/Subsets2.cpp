#include <algorithm>
#include <vector>

using namespace std;

//http://www.lintcode.com/en/problem/subsets-ii/
/*
Given a list of numbers that may has duplicate numbers, return all possible subsets

Notice

Each element in a subset must be in non-descending order.
The ordering between two subsets is free.
The solution set must not contain duplicate subsets.

Example
If S = [1,2,2], a solution is:

[
[2],
[1],
[1,2,2],
[2,2],
[1,2],
[]
]

Observations:
Comparing with Subsets, this one, of course, allow duplicates in given array. Again, during the backtracing on each stage,
leve, whatever you call it, duplicated elements can only be considered. The same trick we use in other similar algorithm,
for example: CombinationSum2.

In order to identify such duplicates, we will have to sort the input array in a non decreasing order first.

Again, the backtracing can exit earlier if we apply the extra constraint:

Given the required combination size, if we know from current index i, there will not have sufficient elements left to form
such a combination, there is no need to move forward: i + size - n <= len, "len" is the size of the input array, "n" is the
base index in the current combination at current backtracing stage and "size" is total number of elements that is supposed
to be put in current combination. (size - n) tells how many more we need in the current combination (I know, I know, it's off
by 1 since n is an index, but you know what I mean here:)

By doing so we could eliminate a lot of nopass ends.
*/
class Solution {
private:
	void aux(vector<vector<int> > &ans, const vector<int> &S, vector<int> &vec, int idx, int n, int size) {
		if (idx == size) {
			ans.push_back(vector<int>(vec.begin(), vec.begin() + size));
			return;
		}
		int len = S.size(), prev = 0;
		for (int i = n; i < len && i + size - n <= len; ++i) {
			if (i > n && prev == S[i])continue;
			vec[idx] = S[i];
			this->aux(ans, S, vec, idx + 1, i + 1, size);
			prev = S[i];
		}
	}
public:
	/**
	* @param S: A set of numbers.
	* @return: A list of lists. All valid subsets.
	*/
	vector<vector<int> > subsetsWithDup(vector<int> &S) {
		int len = S.size();
		vector<vector<int> > ans;
		if (len > 0) {
			std::sort(S.begin(), S.end());
			vector<int> vec(len, 0);
			for (int i = 0; i <= len; ++i)
				this->aux(ans, S, vec, 0, 0, i);
		}
		return ans;
	}
};