#include <vector>

using namespace std;

//https://leetcode.com/problems/spiral-matrix-ii/
/*
59. Spiral Matrix II

Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:

Input: 3
Output:
[
[ 1, 2, 3 ],
[ 8, 9, 4 ],
[ 7, 6, 5 ]
]

Observations:

My solution is not fancy at all. Simply simulate the sprial path inward to fill in correct number at each side (4 sides total).
I use 2 variables to track the change of this square path:

- m is the starting point and it's always on the diagonal of the square. From [0, 0] to [1, 1] to [2, 2]...well if necessary

- k is supposed to be the length of this square path in each iteration. It starts from n and is decreased by 2 each iteration. That has been said,
since m will be increased by 1 during each iteration and k is actually for marking the first exclusive index, k is only needed to be
decreased by 1. k means the index on the 2 corners at right that the sprial should turn. ans[k - 1] is the last element to fill.
*/
class SolutionSpiralMatrix2 {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int> > ans(n, vector<int>(n, 0));
		int k = n, m = 0, cnt = 0;
		while (k > 0) {
			for (int i = m; i < k; ++i) ans[m][i] = ++cnt;
			for (int i = m + 1; i < k; ++i) ans[i][k - 1] = ++cnt;
			for (int i = k - 2; i > m; --i) ans[k - 1][i] = ++cnt;
			for (int i = k - 1; i > m; --i) ans[i][m] = ++cnt;
			--k, ++m;
		}
		return ans;
	}
};