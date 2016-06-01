#include <vector>
#include <iostream>

using namespace std;
//http://articles.leetcode.com/searching-2d-sorted-matrix-part-ii
//https://leetcode.com/problems/search-a-2d-matrix-ii/
/*
240. Search a 2D Matrix II

Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.
For example,

Consider the following matrix:

[
[1,   4,  7, 11, 15],
[2,   5,  8, 12, 19],
[3,   6,  9, 16, 22],
[10, 13, 14, 17, 24],
[18, 21, 23, 26, 30]
]
Given target = 5, return true.

Given target = 20, return false.
*/
class SolutionSearch2DMatrix2 {
private:
	bool aux(vector<vector<int>>& matrix, int target, int x1, int x2, int y1, int y2, int m, int n)
	{
		if (x1 > x2 || y1 > y2 || x1 < 0 || y1 < 0 || x2 >= m || y2 >= n)return false;
		if (matrix[x1][y1] == target)return true;
		std::pair<int, int> lp = std::make_pair(x1, y1);
		std::pair<int, int> hp = std::make_pair(x2, y2);
		std::pair<int, int> mp = std::make_pair(x1, y1);
		int x = 0, y = 0;
		while (lp.first <= hp.first && lp.second <= hp.second)
		{
			x = lp.first + (hp.first - lp.first) / 2;
			y = lp.second + (hp.second - lp.second) / 2;
			if (matrix[x][y] <= target)
			{
				if (matrix[x][y] == target)return true;
				mp.first = x;
				mp.second = y;
				lp.first = x + 1;
				lp.second = y + 1;
			}
			else
			{
				hp.first = x - 1;
				hp.second = y - 1;
			}
		}
		if (mp.first == x1 && mp.second == y1 && matrix[x1][y1]> target)return false;
		else if (mp.first == x2 && mp.second == y2 && matrix[x2][y2] < target) return false;
		return aux(matrix, target, mp.first + 1, x2, y1, mp.second, m, n) || aux(matrix, target, x1, mp.first, mp.second + 1, y2, m, n);

	}
public:
	//Slow BS and Divide and Conquer
	bool searchMatrixSlow(vector<vector<int>>& matrix, int target) {
		int m = matrix.size();
		if (m < 1)return false;
		int n = matrix[0].size();
		if (n < 1)return false;
		return this->aux(matrix, target, 0, m - 1, 0, n - 1, m, n);
	}
	//Zigzag Trick... O(m + n)
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size();
		if (m < 1)return false;
		int n = matrix[0].size();
		if (n < 1)return false;
		if (target < matrix[0][0] || target > matrix[m - 1][n - 1])return false;
		int i = 0, j = n - 1;
		while (i < m && j > -1)
		{
			if (target == matrix[i][j])return true;
			else if (target < matrix[i][j])
				--j;
			else
				++i;
		}
		return false;
	}

};
void TestSearch2DMatrix2()
{
	SolutionSearch2DMatrix2 so;
	vector<vector<int>> vec;
	vec.push_back({ 1, 4, 7, 11 });
	vec.push_back({ 2, 5, 8, 12 });
	vec.push_back({ 3, 6, 9, 15 });
	vec.push_back({ 10, 13, 14, 17 });
	vec.push_back({ 18, 21, 23, 26 });
	cout << "Expect 1 :" << so.searchMatrix(vec, 13) << endl;
	cout << "Expect 1 :" << so.searchMatrix(vec, 21) << endl;
	cout << "Expect 1 :" << so.searchMatrix(vec, 8) << endl;
	cout << "Expect 0 :" << so.searchMatrix(vec, 19) << endl;
	cout << "Expect 0 :" << so.searchMatrix(vec, -10) << endl;
	cout << "Expect 0 :" << so.searchMatrix(vec, 30) << endl;

	vector<vector<int>> vec1;
	vec1.push_back({ 1, 4, 7, 11 });
	cout << "Expect 0: " << so.searchMatrix(vec1, 0) << endl;
	cout << "Expect 0: " << so.searchMatrix(vec1, 12) << endl;
	cout << "Expect 0: " << so.searchMatrix(vec1, 5) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec1, 1) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec1, 11) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec1, 4) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec1, 7) << endl;

	vector<vector<int>> vec2;
	vec2.push_back({ 1 });
	vec2.push_back({ 4 });
	vec2.push_back({ 7 });
	vec2.push_back({ 11 });
	cout << "Expect 0: " << so.searchMatrix(vec2, 0) << endl;
	cout << "Expect 0: " << so.searchMatrix(vec2, 12) << endl;
	cout << "Expect 0: " << so.searchMatrix(vec2, 5) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec2, 1) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec2, 11) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec2, 4) << endl;
	cout << "Expect 1: " << so.searchMatrix(vec2, 7) << endl;

	vector<vector<int>> vec3;
	vec3.push_back({ 1 });
	cout << "Expect 1: " << so.searchMatrix(vec3, 1) << endl;
	cout << "Expect 0: " << so.searchMatrix(vec3, 12) << endl;
	cout << "Expect 0: " << so.searchMatrix(vec3, 5) << endl;

	vector<vector<int>> vec4;
	vec4.push_back({ 1, 4, 7, 11, 15 });
	vec4.push_back({ 2, 5, 8, 12, 19 });
	vec4.push_back({ 3, 6, 9, 15, 22 });
	vec4.push_back({ 10, 13, 14, 17, 24 });
	vec4.push_back({ 18, 21, 23, 26, 30 });
	cout << "Expect 1 :" << so.searchMatrix(vec4, 13) << endl;
	cout << "Expect 1 :" << so.searchMatrix(vec4, 21) << endl;
	cout << "Expect 1 :" << so.searchMatrix(vec4, 8) << endl;
	cout << "Expect 1 :" << so.searchMatrix(vec4, 19) << endl;
	cout << "Expect 0 :" << so.searchMatrix(vec4, -10) << endl;
	cout << "Expect 1 :" << so.searchMatrix(vec4, 30) << endl;
	cout << "Expect 0 :" << so.searchMatrix(vec4, 0) << endl;
	cout << "Expect 0 :" << so.searchMatrix(vec4, 32) << endl;
}