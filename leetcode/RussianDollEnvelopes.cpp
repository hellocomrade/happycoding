#include <cassert>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

//https://leetcode.com/problems/russian-doll-envelopes/
/*
354. Russian Doll Envelopes

You have a number of envelopes with widths and heights given as a pair of integers (w, h).
One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Note:

- Rotation is not allowed.

Example:

Input: [[5,4],[6,4],[6,7],[2,3]]

Output: 3

Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).

Observations:

This question was mentioned in:

https://leetcode.com/discuss/interview-experience/479413/nda-google-facebook-amazon-l5-e5-l5-london-dec-2019-offer

Like any other problem involving intervals, sorting by their x or y is always good to try first.

If sorting by width (by x, in the case w1 = w2, smaller h is considered smaller), a plain DP can be applied. On any given index i,
check all intervals in [0, i - 1] to see whose height is narrower than envelopes[i][1]. Assuming max values for [0, i - 1] have been
calculated and stored in memo[0, i - 1]. It's straightforward to find out the max for i and therefore the max for the problem.

This "naive" DP solution takes O(N^2) time and O(N) space, see maxEnvelopes1.

I always think there could be a better DP solution ends up taking O(nlogN) time. Since envelopes was sorted
by width already, it's possible BS can be applied to find the envelopes in [0, i - 1] that fit in i in klogN time.
But it appears there are lots of edge cases to cover...

The fact is the trick applies on LIS works here! You may call it BS + BP, but I prefer BS + Memorization or BS + Greedy.
Anyway, let's sorting envelopes by width first. In this sorting, for the case w1 == w2, taller h is considered smaller.
For exampe: [3, 1], [3, 4], [2, 2] will be sorted as [2, 2], [3, 4], [3, 1].

Then, using BS on height for an array that is maintained in an increasing order. The length of this array is the
max value of the problem. See maxEnvelopes.

This algorithm was introduced in leetcode 300 (Longest Increasing Subsequence) at: https://leetcode.com/problems/longest-increasing-subsequence/solution/

As same as leetcode 300, array lisy does not result in longest increasing subsequence on height. But length
of lisy will give you correct length of LIS on height.

Last but not least, why sorting is different for the case of [3, 1], [3, 4], [2, 2]? If the same comp in maxEnvelopes1
is used here, the result will be [2, 2], [3, 1], [3, 4]. The do LIS BS, the result will be [1, 2, 4]! Length is 3.
But the correct answer is 2! This is due to the cases that multiple envelopes with same width but differnt height sorted
in height ASC. This can be corrected for case [3, 1], [3, 4], the sorting result should be [3, 4], [3, 1].
This will give us correct LIS array [1]. Don't ask me why, there is no "logical" answer... it just works :)

Actually, if comparing the solutions for this problem with LIS, this problem is simply an extention of LIS on 2D!
*/
class SolutionRussianDollEnvelopes {
public:
	int maxEnvelopes(vector<vector<int>>& envelopes) {
		std::sort(envelopes.begin(), envelopes.end(), [](const vector<int>& e1, const vector<int>& e2) { return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]); });
		vector<int> lisy;
		vector<int>::iterator itor;
		for (const vector<int>& e : envelopes) {
			itor = std::lower_bound(lisy.begin(), lisy.end(), e[1]);
			if (lisy.end() == itor) lisy.push_back(e[1]);
			else *itor = e[1];
		}
		return lisy.size();
	}
	int maxEnvelopes1(vector<vector<int>>& envelopes) {
		int ans = 1, len = (int)envelopes.size();
		vector<int> memo(len, 1);
		function<bool(const vector<int>&, const vector<int>&)> comp = [](const vector<int>& e1, const vector<int>& e2) -> bool {
			return (e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] < e2[1]));
		};
		std::sort(envelopes.begin(), envelopes.end(), comp);
		for (int i = 0; i < len; ++i)
			for (int j = 0; j < i; ++j)
				if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1]) {
					memo[i] = std::max(memo[i], memo[j] + 1);
					ans = std::max(ans, memo[i]);
				}
		return 0 == len ? 0 : ans;
	}
};
void TestRussianDollEnvelopes() {
	SolutionRussianDollEnvelopes so;
	vector<vector<int>> vec1{ {5, 4}, {6, 4}, {6, 7}, {2, 3} };
	assert(3 == so.maxEnvelopes(vec1));
}
/*
Test cases:

[[4,5],[4,6],[6,7],[2,3],[1,1]]
[[5,4],[6,4],[6,7],[2,3]]
[[5,4],[6,4],[6,7],[2,3],[2,4]]
[[3,1],[2,2],[4,2]]
[[3,1],[2,2],[4,3]]
[[3,5],[3,1],[2,2],[1,7]]
[[3,5],[3,1],[2,2],[1,7],[4,5],[4,9],[2,8],[7,7]]
[[1,1],[1,1]]
[[1,1]]
[]
[[1,3],[3,1],[2,2],[7,7],[8,2],[9,1],[3,7],[2,4],[2,1],[3,7],[3,4],[10,1]]
[[15,8],[2,20],[2,14],[4,17],[8,19],[8,9],[5,7],[11,19],[8,11],[13,11],[2,13],[11,19],[8,11],[13,11],[2,13],[11,19],[16,1],[18,13],[14,17],[18,19]]

Outputs:

4
3
3
2
2
2
3
1
1
0
3
5
*/