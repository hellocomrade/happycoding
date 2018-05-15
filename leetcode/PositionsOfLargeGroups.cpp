#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/positions-of-large-groups
/*
830. Positions of Large Groups

In a string S of lowercase letters, these letters form consecutive groups of the same character.

For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z" and "yy".

Call a group large if it has 3 or more characters.  We would like the starting and ending positions of every large group.

The final answer should be in lexicographic order.



Example 1:

Input: "abbxxxxzzy"

Output: [[3,6]]

Explanation: "xxxx" is the single large group with starting  3 and ending positions 6.

Example 2:

Input: "abc"

Output: []

Explanation: We have "a","b" and "c" but no large group.

Example 3:

Input: "abcdddeeeeaabbbcd"

Output: [[3,5],[6,9],[12,14]]


Note:  1 <= S.length <= 1000

Observations:

An easy question. But I failed the first time :) Why? Forgot to check the edge case that the large group is at the end of the array.
For example "abcaaa". So either do a separate check outside the loop or allow i to be equal to len.

Official solution is at: https://leetcode.com/problems/positions-of-large-groups/solution/
*/
class SolutionPositionsOfLargeGroups {
public:
	vector<vector<int>> largeGroupPositions(string S) {
		vector<vector<int> > ans;
		int len = (int)S.size();
		char ch = S[0];
		for (int i = 1, j = 0; i <= len; ++i) {
			if (len == i || S[i] != ch) {
				if (i - j >= 3) ans.emplace_back(vector<int>{j, i - 1});
				ch = S[i], j = i;
			}
		}
		return ans;
	}
};
/*
Test cases:

"abbxxxxzzy"
"abc"
"abcdddeeeeaabbbcd"
"a"
"aaa"

Outputs:

[[3,6]]
[]
[[3,5],[6,9],[12,14]]
[]
[[0,2]]
*/