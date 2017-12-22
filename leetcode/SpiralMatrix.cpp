#include <vector>

using namespace std;

//https://leetcode.com/problems/spiral-matrix/
/*
54. Spiral Matrix

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
[ 1, 2, 3 ],
[ 4, 5, 6 ],
[ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].

Observations:
Detail, detail and detail, I am sure the one I have below is the not the best solution in terms of coding...

Official solutions are at: https://leetcode.com/problems/spiral-matrix/solution/

I like that simulation idea.
*/
class SolutionSpiralMatrix {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> ans;
		int n = matrix.size();
		if (n > 0) {
			int m = matrix[0].size();
			if (m < 1)return ans;
			int x = 0, y = 0, lenx = m, leny = n, i = 0, j = 0;
			while (x < lenx && y < leny) {
				j = x, i = y;
				while (i + 1 < leny || j < lenx) {
					if (j < lenx)ans.push_back(matrix[i][j++]);
					else if (i + 1 < leny)ans.push_back(matrix[++i][j - 1]);
				}
				j -= 1;//cout << i << ',' << j << endl;
				if (i > y && j > x) {//[[1,2,3]], [[7],[9],[6]]
					while (i - 1 > y || j > x) {
						if (j > x)ans.push_back(matrix[i][--j]);
						else if (i - 1 > y)ans.push_back(matrix[--i][j]);
					}
				}
				++x, ++y, --lenx, --leny;
			}
		}
		return ans;
	}
};
/*
Test cases:

[[1,2,3],[4,5,6],[7,8,9]]
[[1,2,3]] <---
[[7],[9],[6]] <---
[[1,2],[3,4]]
[[1]]
[[1,2,3],[4,5,6]]
[[1],[2]]
[[1,2,3,4],[5,6,7,8],[9,10,11,12]]
[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
*/