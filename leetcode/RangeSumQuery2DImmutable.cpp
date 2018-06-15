#include <vector>

using namespace std;

//https://leetcode.com/problems/range-sum-query-2d-immutable/
/*
304. Range Sum Query 2D - Immutable

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:

Given matrix = [
[3, 0, 1, 4, 2],
[5, 6, 3, 2, 1],
[1, 2, 0, 1, 5],
[4, 1, 0, 1, 7],
[1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8


sumRegion(1, 1, 2, 2) -> 11

sumRegion(1, 2, 2, 4) -> 12

Note:

1.You may assume that the matrix does not change.
2.There are many calls to sumRegion function.
3.You may assume that row1 ≤ row2 and col1 ≤ col2.

Observations:

If you did leetcode 303, RSQ on 1D array, you probably know using prefix sum. It can bed considered as memorization algorithm or caching.

Now, we face 2D, what if we try the same approach by pre-calculating sums? We could do row based prefix sum using a memo[m][n] to store
the sum from [i][0] to [i][j] on each row, given m = len(matrix), n = len(matrix[0]), i in [0, m), j in [0, n).

Doing so requires O(mn) time and each query needs O(m) time.

Can we do a better job? What if we cache sub-matrix?

If we define memo as memo[m + 1][n + 1], with one extra row and column filling with 0, we could have:

memo[i][j] = memo[i - 1][j] + memo[i][j - 1] + matrix[i - 1][j - 1] - memo[i - 1][j - 1];

Starting from i = 1 and j = 1;

memo[i + 1][j + 1] represents the sum from matrix[0][0] to matrix[i][j]. Pay attention on the possible overlap by adding memo[i - 1][j] + memo[i][j - 1] + matrix[i - 1][j - 1].
Therefore, we have to substract memo[i - 1][j - 1]. In the edge case, when i < 1 and/or j < 1, we hit memo[i][j] which is full of zero. With this buffer, we don't have to
check if i and j are valid for overlap substraction. This takes O(mn) time and O(mn) space.

With memo avaiable, we can conduct query in O(1). Again, we might face overlap situation again. But this time, the possible overlap matrix is substracted twice. Therefore,
we have to add it once as compensation.

leetcode thinks this is DP, so be it...

And I also want to argue on the edge test case: matrix is empty. This should definitely be ruled out coz leetcode doesn't attempt to try query function when the matrix is
empty then why you have such a test case set up specifically for constructing memo?
*/
class NumMatrix {
private:
	vector<vector<int> > memo;
	int m, n;
public:
	NumMatrix(vector<vector<int>> matrix) : memo(matrix.size() + 1, vector<int>(matrix.size() > 0 ? matrix[0].size() + 1 : 0, 0)) {
		m = (int)matrix.size() + 1;
		n = m > 1 ? (int)matrix[0].size() + 1 : 0;
		if (n < 1) return;
		for (int i = 1; i < m; ++i)
			for (int j = 1; j < n; ++j)
				memo[i][j] = memo[i - 1][j] + memo[i][j - 1] + matrix[i - 1][j - 1] - memo[i - 1][j - 1];
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return memo[row2 + 1][col2 + 1] - memo[row2 + 1][col1] - memo[row1][col2 + 1] + memo[row1][col1];
	}
};

/**
* Your NumMatrix object will be instantiated and called as such:
* NumMatrix obj = new NumMatrix(matrix);
* int param_1 = obj.sumRegion(row1,col1,row2,col2);
*/
/*
Test cases:

["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[0,1,2,3],[0,0,3,4],[1,2,1,2]]
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[0,0,0,0],[0,1,0,4],[4,2,4,2]]
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[0,4,0,4],[4,0,4,0],[4,4,4,4]]
["NumMatrix"]
[[[]]]

Outputs:

[null,8,11,12]
[null,19,49,3]
[null,3,7,3]
[null,2,1,5]
[null]
*/