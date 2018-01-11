#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/set-matrix-zeroes/
/*
73. Set Matrix Zeroes

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?

Observations:
Catch is: by set zeros on current row/column, the clue for reset other rows/colums are gone. Therefore, a duplicate of
the matrix shall be kept, however this will take (MN) space.

Since asking for in place, has to reuse parts of the matrix, ususally this is done through 1 row and 1 column. Then
use two boolean variables to tell if the 1 row and 1 column should be set to zeroes. See setZeroes1

Then, after a quick peek on discussion section, I realize that only 1 boolean variable is necessary. This is based upon the fact
that matrix[0][0] can be used to indicate if the first row or column should be reset to zeroes. Say, if it's used for marking 1 row, then
we only need an extra variable to mark 1st column.

Also, we could simplify the code by scanning the matrix reversely so the 1st row/column, which are used for storing zeroing info will be
touched at the end. Doing so, we could complete the reset in one single 2-level loop.

In this approrach, during the loop, j shall be no less than 1 since the first column now is solely for tracking the rows that should be zeroed out.
Again, matrix[0][j], j = 0 is for the status of first row, not column.
*/
class SolutionSetMatrixZeroes {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		bool col1Zero = false;
		int n = matrix.size();
		if (n > 0) {
			int m = matrix[0].size();
			for (int i = 0; m > 0 && i < n; ++i) {
				if (0 == matrix[i][0])col1Zero = true;
				for (int j = 1; j < m; ++j)
					if (0 == matrix[i][j])matrix[i][0] = matrix[0][j] = 0;
			}
			for (int i = n - 1; i > -1; --i) {
				for (int j = m - 1; j > 0; --j)
					if (0 == matrix[i][0] || 0 == matrix[0][j])matrix[i][j] = 0;
				if (true == col1Zero)matrix[i][0] = 0;
			}
		}
	}
	void setZeroes1(vector<vector<int>>& matrix) {
		bool row1Zero = false, col1Zero = false;
		int n = matrix.size();
		if (n > 0) {
			int m = matrix[0].size();
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j) {
					if (0 == i && 0 == matrix[0][j])row1Zero = true;
					if (0 == j && 0 == matrix[i][0])col1Zero = true;
					if (0 == matrix[i][j])matrix[i][0] = matrix[0][j] = 0;
				}
			for (int i = 1; i < n; ++i)if (0 == matrix[i][0])std::fill(matrix[i].begin(), matrix[i].end(), 0);
			for (int j = 1; j < m; ++j)
				if (0 == matrix[0][j])
					for (int i = 1; i < n; ++i)matrix[i][j] = 0;
			if (true == row1Zero)std::fill(matrix[0].begin(), matrix[0].end(), 0);
			if (true == col1Zero)for (int i = 0; i < n; ++i)matrix[i][0] = 0;
		}
	}
};
/*
Test cases:
[[0]]
[[1]]
[[]]
[]
[[0,1],[1,0]]
[[1,1,0,1],[0,1,1,1],[1,1,1,1],[0,1,0,1]]
[[1,1,0,1],[0,1,1,1],[1,1,1,1]]
[[1,1,1],[0,1,2]]
[[-4,-2147483648,6,-7,0],[-8,6,-8,-6,0],[2147483647,2,-9,-6,-10]]

Results:
[[0]]
[[1]]
[[]]
[]
[[0,0],[0,0]]
[[0,0,0,0],[0,0,0,0],[0,1,0,1],[0,0,0,0]]
[[0,0,0,0],[0,0,0,0],[0,1,0,1]]
[[0,1,1],[0,0,0]]
[[0,0,0,0,0],[0,0,0,0,0],[2147483647,2,-9,-6,0]]
*/