#include <vector>

using namespace std;

//https://leetcode.com/problems/pascals-triangle/
/*
118. Pascal's Triangle

Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
[1],
[1,1],
[1,2,1],
[1,3,3,1],
[1,4,6,4,1]
]

Observations:

Simply follow the annimation, using simulation. Did I do it perfectly at the first attempt?
See generate1. No, no need for that temp variable k. See generate.
*/
class SolutionPascalTriangle {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> ans;
		for (int i = 0; i < numRows; ++i) {
			ans.push_back(vector<int>(i + 1, 1));
			for (int j = 1; j < i; ++j)
				ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
		}
		return ans;
	}
	vector<vector<int>> generate1(int numRows) {
		vector<vector<int>> ans;
		for (int i = 0, k = 1; i < numRows; ++k, ++i) {
			ans.push_back(vector<int>(k, 1));
			for (int j = 1; j < k - 1; ++j)
				ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
		}
		return ans;
	}
};