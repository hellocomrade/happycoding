#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

//https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
/*
329. Longest Increasing Path in a Matrix

Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

Input: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]

Output: 4

Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2:

Input: nums =
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
]

Output: 4

Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

Observations:

This problem may appear to be scarying but after a second look, it's actually pretty hard to get wrong as long as one can pick the right approach, which
is DFS + memorization. I would hardly consider this as DP.

The reason I said it's hard to get this done wrong is: finding an increasing sequence rules out a very tricky case: cyclic visit. DFS will never make this mistake
since it only follows the increasing order and previously visited nodes are guaranteed less than current node. So the edge from current node to previous visited node
is not considerd as a valid route since the previous one is smaller which breaks the rule: an increasing path.

longestIncreasingPath1 is my first attempt. I doesn't like the fact "1 + std::max({ fn(i + 1, j, matrix[i][j]), fn(i - 1, j, matrix[i][j]), fn(i, j - 1, matrix[i][j]), fn(i, j + 1, matrix[i][j]) });"
was outside function fn itself.

longestIncreasingPath is an attempt to make the code looks more elegant by introducing INT_MIN as a pseudo node. However, leetcode's test case doesn't include [[-2147483648]].
If no safeguard is given at return and "[[-2147483648]]" is used, 0 instead of 1 will return and leetcode is OK with it...
*/
class SolutionLongestIncreasingPathInMatrix {
public:
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int ans = 0, rcnt = (int)matrix.size(), int_min = numeric_limits<int>::min();
		if (0 == rcnt) return ans;
		int ccnt = (int)matrix[0].size();
		if (0 == ccnt) return ans;
		vector<vector<int>> memo(rcnt, vector<int>(ccnt, 0));
		function<int(int, int, int)> fn = [&](int i, int j, int val) {
			if (0 > i || 0 > j || i == rcnt || j == ccnt || matrix[i][j] <= val) return 0;
			if (0 == memo[i][j])
				memo[i][j] = 1 + std::max({ fn(i + 1, j, matrix[i][j]), fn(i - 1, j, matrix[i][j]), fn(i, j - 1, matrix[i][j]), fn(i, j + 1, matrix[i][j]) });
			return memo[i][j];
		};
		for (int i = 0; i < rcnt; ++i)
			for (int j = 0; j < ccnt; ++j)
				ans = std::max(ans, fn(i, j, int_min));
		return std::max(1, ans);
	}
	int longestIncreasingPath1(vector<vector<int>>& matrix) {
		int ans = 0, rcnt = (int)matrix.size();
		if (0 == rcnt) return ans;
		int ccnt = (int)matrix[0].size();
		if (0 == ccnt) return ans;
		vector<vector<int>> memo(rcnt, vector<int>(ccnt, 0));
		function<int(int, int, int)> fn = [&](int i, int j, int val) {
			if (0 > i || 0 > j || i == rcnt || j == ccnt || matrix[i][j] <= val) return 0;
			if (0 == memo[i][j])
				memo[i][j] = 1 + std::max({ fn(i + 1, j, matrix[i][j]), fn(i - 1, j, matrix[i][j]), fn(i, j - 1, matrix[i][j]), fn(i, j + 1, matrix[i][j]) });
			return memo[i][j];
		};
		for (int i = 0; i < rcnt; ++i)
			for (int j = 0; j < ccnt; ++j) {
				memo[i][j] = 1 + std::max({ fn(i + 1, j, matrix[i][j]), fn(i - 1, j, matrix[i][j]), fn(i, j - 1, matrix[i][j]), fn(i, j + 1, matrix[i][j]) });
				ans = std::max(ans, memo[i][j]);
			}
		return ans;
	}
};
/*
Test cases:
1
4
4
140

Outputs:
[[-2147483648]]
[[9,9,4],[6,6,8],[2,1,1]]
[[3,4,5],[3,2,6],[2,2,1]]
[[0,1,2,3,4,5,6,7,8,9],[19,18,17,16,15,14,13,12,11,10],[20,21,22,23,24,25,26,27,28,29],[39,38,37,36,35,34,33,32,31,30],[40,41,42,43,44,45,46,47,48,49],[59,58,57,56,55,54,53,52,51,50],[60,61,62,63,64,65,66,67,68,69],[79,78,77,76,75,74,73,72,71,70],[80,81,82,83,84,85,86,87,88,89],[99,98,97,96,95,94,93,92,91,90],[100,101,102,103,104,105,106,107,108,109],[119,118,117,116,115,114,113,112,111,110],[120,121,122,123,124,125,126,127,128,129],[139,138,137,136,135,134,133,132,131,130],[0,0,0,0,0,0,0,0,0,0]]
*/