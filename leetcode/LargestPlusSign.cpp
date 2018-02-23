#include <cassert>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

//
/*
764. Largest Plus Sign

In a 2D grid from (0, 0) to (N-1, N-1), every cell contains a 1, except those cells in the given list mines which are 0. What is the largest axis-aligned plus sign of 1s contained in the grid? Return the order of the plus sign. If there is none, return 0.

An "axis-aligned plus sign of 1s of order k" has some center grid[x][y] = 1 along with 4 arms of length k-1 going up, down, left, and right, and made of 1s. This is demonstrated in the diagrams below. Note that there could be 0s or 1s beyond the arms of the plus sign, only the relevant area of the plus sign is checked for 1s.

Examples of Axis-Aligned Plus Signs of Order k:

Order 1:
000
010
000

Order 2:
00000
00100
01110
00100
00000

Order 3:
0000000
0001000
0001000
0111110
0001000
0001000
0000000
Example 1:

Input: N = 5, mines = [[4, 2]]

Output: 2

Explanation:

11111
11111
11111
11111
11011

In the above grid, the largest plus sign can only be order 2.  One of them is marked in bold.

Example 2:

Input: N = 2, mines = []

Output: 1

Explanation:

There is no plus sign of order 2, but there is of order 1.

Example 3:

Input: N = 1, mines = [[0, 0]]

Output: 0

Explanation:

There is no plus sign, so return 0.

Note:

- N will be an integer in the range [1, 500].

- mines will have length at most 5000.

- mines[i] will be length 2 and consist of integers in the range [0, N-1].

(Additionally, programs submitted in C, C++, or C# will be judged with a slightly smaller time limit.)

Observations:

This is an interesting question under the lable of DP, I just don't agree with it. It requires memorization but it's not a DP.

What's the sub optimal solution? For any given cell (i, j), max_plus_sign(grid[i][j]) = min(left_ones, right_ones, top_ones, bottom_ones).

That is the fact, but it's static, no influence from one cell to the other at all!

My first try is TLE, coz I used too much space and potentially had an impact on performance.

orderOfLargestPlusSign2 is very well self-explained:

- Populate grids with zeros;

- Scan grids in row first then column style, get right_ones for each row first then get left_ones, pick min(left_ones, right_ones) as value Tmp for now;

- Scan grids in column first then row style, get bottom_ones for each column first then get top_ones, pick min(Tmp, top_ones, bottom_ones) as final value;

- Keep track max(final_value);

Then you realize you have two very similar 2 level loops, can we combine them? That gives you orderOfLargestPlusSign1.
See here you will have to pay attention on overwritting, std::min() has to be applied on each grid value assignment.

Then you figure why we have to have 2 inner loops? Can we merge them together? Yes, that gives you the final version: orderOfLargestPlusSign.

O(N^2) for sure.
*/
class SolutionLargestPlusSign {
public:
	int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
		int ans = 0;
		vector<vector<int> > memo(N, vector<int>(N, N));
		for (auto vec : mines)memo[vec[0]][vec[1]] = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0, l = 0, r = 0, t = 0, b = 0; j < N; ++j) {
				memo[i][j] = std::min(memo[i][j], l = 0 == memo[i][j] ? 0 : l + 1);
				memo[j][i] = std::min(memo[j][i], t = 0 == memo[j][i] ? 0 : t + 1);
				memo[i][N - j - 1] = std::min(memo[i][N - j - 1], r = 0 == memo[i][N - j - 1] ? 0 : r + 1);
				memo[N - j - 1][i] = std::min(memo[N - j - 1][i], b = 0 == memo[N - j - 1][i] ? 0 : b + 1);
			}
		}
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				ans = std::max(ans, memo[i][j]);
		return ans;
	}
	int orderOfLargestPlusSign1(int N, vector<vector<int>>& mines) {
		int ans = 0;
		vector<vector<int> > memo(N, vector<int>(N, N));
		for (auto vec : mines)memo[vec[0]][vec[1]] = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = N - 1, cnt = 0, cnt1 = 0; j > -1; --j) {
				cnt = 0 == memo[i][j] ? 0 : cnt + 1;
				memo[i][j] = std::min(memo[i][j], cnt);
				cnt1 = 0 == memo[j][i] ? 0 : cnt1 + 1;
				memo[j][i] = std::min(memo[j][i], cnt1);
			}
			for (int j = 0, cnt = 0, cnt1 = 0; j < N; ++j) {
				cnt = 0 == memo[i][j] ? 0 : cnt + 1;
				memo[i][j] = std::min(memo[i][j], cnt);
				cnt1 = 0 == memo[j][i] ? 0 : cnt1 + 1;
				memo[j][i] = std::min(memo[j][i], cnt1);
			}
		}
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				ans = std::max(ans, memo[i][j]);
		return ans;
	}
	int orderOfLargestPlusSign2(int N, vector<vector<int>>& mines) {
		int ans = 0;
		vector<vector<int> > memo(N, vector<int>(N, N));
		for (auto vec : mines)memo[vec[0]][vec[1]] = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = N - 1, cnt = 0; j > -1; --j) {
				cnt = 0 == memo[i][j] ? 0 : cnt + 1;
				memo[i][j] = 0 == memo[i][j] ? 0 : cnt;
			}
			for (int j = 0, cnt = 0; j < N; ++j) {
				cnt = 0 == memo[i][j] ? 0 : cnt + 1;
				memo[i][i] = 0 == memo[i][j] ? 0 : std::min(memo[i][j], cnt);
			}
		}
		for (int i = 0; i < N; ++i) {
			for (int j = N - 1, cnt = 0; j > -1; --j) {
				cnt = 0 == memo[j][i] ? 0 : cnt + 1;
				memo[j][i] = 0 == memo[j][i] ? 0 : std::min(memo[j][i], cnt);
			}
			for (int j = 0, cnt = 0; j < N; ++j) {
				cnt = 0 == memo[j][i] ? 0 : cnt + 1;
				memo[j][i] = 0 == memo[j][i] ? 0 : std::min(memo[j][i], cnt);
				ans = std::max(ans, memo[j][i]);
			}
		}
		return ans;
	}
	//TLE
	int orderOfLargestPlusSign3(int N, const vector<vector<int>>& mines) {
		int ans = 0;
		vector<vector<vector<int> > > memo(N, vector<vector<int> >(N, vector<int>(2, 0)));
		unordered_map<int, unordered_set<int> > zeros;
		for (auto vec : mines) {
			if (0 == zeros.count(vec[0]))zeros.emplace(vec[0], unordered_set<int>());
			zeros[vec[0]].emplace(vec[1]);
		}
		for (int i = 0; i < N; ++i) {
			for (int j = N - 1, cnt = 0; j > -1; --j) {
				memo[i][j][0] = cnt;
				cnt = (0 == zeros.count(i) || 0 == zeros[i].count(j)) ? cnt + 1 : 0;
			}
			for (int j = 0, cnt = 0; j < N; ++j) {
				memo[i][j][0] = std::min(memo[i][j][0], cnt);
				if (0 == zeros.count(i) || 0 == zeros[i].count(j)) {
					if (i < N - 1) memo[i + 1][j][1] = memo[i][j][1] + 1;
					cnt++;
				}
				else
					cnt = 0;
			}
		}
		for (int i = 0; i < N; ++i) {
			for (int j = N - 1, cnt = 0; j > -1; --j) {
				memo[j][i][1] = std::min(memo[j][i][1], cnt);
				if (0 == zeros.count(j) || 0 == zeros[j].count(i)) {
					++cnt;
					ans = std::max(ans, std::min(memo[j][i][0], memo[j][i][1]) + 1);
				}
				else
					cnt = 0;
			}
		}
		return ans;
	}
};
void TestLargestPlusSign() {
	SolutionLargestPlusSign so;
	assert(2 == so.orderOfLargestPlusSign(5, vector<vector<int> >{ {4, 2} }));
	assert(1 == so.orderOfLargestPlusSign(2, vector<vector<int> >{}));
	assert(0 == so.orderOfLargestPlusSign(1, vector<vector<int> >{ {0, 0} }));
}
/*
Test cases:

5
[[0,0],[0,1],[0,4],[1,0],[1,1],[1,2],[2,0],[2,1],[2,2],[2,3],[2,4],[3,0],[4,0],[4,1],[4,3],[4,4]]
5
[[4,2]]
6
[[4,2]]
6
[[4,2],[1,2],[0,1],[4,1],[4,3],[2,2],[1,1],[1,3],[2,3],[2,1]]
1
[[0,0]]
2
[]
5
[[0,0],[0,1],[0,2],[0,3],[0,4],[1,0],[1,1],[1,3],[1,4],[2,0],[2,4],[3,0],[3,1],[3,3],[3,4]]
6
[[0,0],[0,1],[0,2],[0,3],[1,2],[1,1],[1,5],[1,4],[2,1],[2,3],[3,0],[3,1],[3,3],[3,4]]
7
[[0,0],[0,1],[0,2],[0,3],[0,4],[1,0],[1,1],[1,3],[1,4],[2,0],[2,4],[3,0],[3,1],[3,3],[3,4]]

Outputs:

1
2
3
2
0
1
2
2
3
*/