#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/search-a-2d-matrix/
/*
74. Search a 2D Matrix

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
[1,   3,  5,  7],
[10, 11, 16, 20],
[23, 30, 34, 50]
]
Given target = 3, return true.

//Observations:
Require O(logM + LogN), search the matrix[i][0] to find the right row, then conducat the second BS on that row
*/
class SolutionSearch2DMatrix {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int n = matrix.size();
		if (n > 0) {
			int m = matrix[0].size();
			if (m > 0) {
				int l = 0, r = n - 1, mid = 0;
				while (l <= r) {
					mid = l + (r - l) / 2;
					if (target == matrix[mid][0])return true;
					else if (target < matrix[mid][0])r = mid - 1;
					else l = mid + 1;
				}
				r = std::max(0, r);
				return binary_search(matrix[r].begin(), matrix[r].end(), target);
			}
		}
		return false;
	}
	bool searchMatrix1(vector<vector<int>>& matrix, int target) {
		int m = matrix.size();
		if (m < 1)return false;
		int n = matrix[0].size();
		if (n == 0)return false;
		int l = 0, h = m - 1, mid = 0, mid1 = 0;
		while (l <= h)
		{
			mid = l + (h - l) / 2;
			if (matrix[mid][0] <= target)
			{
				if (target == matrix[mid][0])return true;
				mid1 = mid;
				l = mid + 1;
			}
			else
				h = mid - 1;
		}
		if ((mid1 == 0 && matrix[0][0] > target) || (mid1 == m - 1 && matrix[m - 1][n - 1] < target))return false;
		/*
		//You could make the code shorter by using lower_bound
		auto k = std::lower_bound(matrix[mid1].begin(), matrix[mid1].end(), target);
		return *k == target;
		*/
		l = 0, h = n - 1;
		while (l <= h)
		{
			mid = l + (h - l) / 2;
			if (matrix[mid1][mid] == target)return true;
			else if (matrix[mid1][mid] < target)
				l = mid + 1;
			else
				h = mid - 1;
		}
		return false;
	}
};