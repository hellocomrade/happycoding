#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

//https://leetcode.com/problems/maximal-rectangle/
/*
85. Maximal Rectangle

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example:

Input:

[
["1","0","1","0","0"],
["1","0","1","1","1"],
["1","1","1","1","1"],
["1","0","0","1","0"]
]

Output: 6

Observations:

What's methodolgy to solve this? DFS? DP? Bitwise? After monkeying around for a bit, one may notice
that this is a variation of leetcode 84 (Largest Rectangle in Histogram). This problem extends the leetcode 84
in two dimensions. In other words, at each row, the algorithm in leetcode 84 will be applied. It's not hard to
find the way to track the height of bars at each row. See heightMemo.

A stack is necessary at each row level to track the previous visited cells in a way that all elements on the stack,
from bottom to the top, are in a non-descending order. This is maintained through the following logic:

Every cell on the row will be pushed onto the stack with one condition: all elements on the stack whose height is greater
than the current cell shall be poped.

During this poping process, the are of rectangles can be calculated. The edge case is when the last element on the stack is
reached. This is actually the tricky part: due to the non desecnding order on the stack, newly added elements are guaranteed no greater
than the removed elements. Therefore, it's safe to say that the last element on the stack shall have the width of j.

Be aware: at the end of each iteration, the stack might not be empty. The 0-height bar will be trapped on the stack. Therefore,
one shall either empty the stack at the end of the iteration for reuse or create a new stack for each row.

This is an O(N^2) solution. It appears whether or not to reuse the stack influences a lot on the performance. This is probably
due to the fact that there are too many sparse matrix in test cases.
*/
class SolutionMaximalRectangle {
public:
	int maximalRectangle(const vector<vector<char>>& matrix) {
		int ans = 0, rlen = (int)matrix.size();
		if (rlen < 1) return ans;
		int clen = (int)matrix[0].size();
		if (clen < 1) return ans;
		vector<int> heightMemo(clen, 0);
		for (int i = 0; i < rlen; ++i) {
			stack<int> stk;
			for (int j = 0, k = 0, h = 0; j <= clen; stk.push(j++)) {
				if (j < clen) heightMemo[j] = ('1' == matrix[i][j]) ? heightMemo[j] + 1 : 0;
				k = j < clen ? heightMemo[j] : 0;
				while (false == stk.empty() && heightMemo[stk.top()] > k) {
					h = stk.top(), stk.pop();
					ans = std::max(ans, (j - 1 - (false == stk.empty() ? stk.top() : -1)) * heightMemo[h]);
				}
			}
		}
		return ans;
	}
};
void TestMaximalRectangle() {
	SolutionMaximalRectangle so;
	so.maximalRectangle(vector<vector<char> >{ { '1', '0', '1', '0', '0' }, { '1','0','1','1','1' }, { '1','1','1','1','1' }, { '1','0','0','1','0' } });
}
/*
Test cases:

[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
[["1","1"],["1","1"]]
[["1","1","1"],["1","1","1"],["1","1","1"]]
[["0","1","1"],["1","1","1"],["1","1","1"]]
[["1"]]
[["0"]]
[["1","1","1","0","0"],["1","1","1","1","1"],["1","1","1","1","1"],["1","1","0","1","1"],["0","0","1","0","1"]]
[["0","1"],["1","0"]]
[["1","1"],["1","0"]]
[["0","1"],["1","1"]]
[["1","0"],["1","0"]]
[["0","0","0","1","0","1","1","1"],["0","1","1","0","0","1","0","1"],["1","0","1","1","1","1","0","1"]]
[["0","0","0","1","0","1","1","1"],["0","1","1","0","0","1","0","1"],["1","0","1","1","1","1","0","1"],["0","0","0","1","0","0","0","0"],["0","0","1","0","0","0","1","0"],["1","1","1","0","0","1","1","1"],["1","0","0","1","1","0","0","1"],["0","1","0","0","1","1","0","0"],["1","0","0","1","0","0","0","0"]]

Outputs:

6
4
9
6
1
0
10
1
2
2
2
4
4
*/