#include <vector>
#include <algorithm>
#include <cassert>
//#include <iostream>

using namespace std;

//https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
/*
Connected Cells in a Grid

Consider a matrix with n rows and m columns, where each cell contains either a 0 or a 1 and any cell
containing a 1 is called a filled cell. Two cells are said to be connected if they are adjacent to each other horizontally, vertically, or diagonally;
in other words, cell  is connected to cells [i - 1, j - 1], [i - 1, j], [i - 1, j + 1], [i, j - 1], [i, j + 1], [i + 1, j - 1], [i + 1, j], and [i + 1, j + 1],
provided that the location exists in the matrix for that [i, j].

If one or more filled cells are also connected, they form a region. Note that each cell in a region is connected to zero or more cells in the region but is not necessarily directly connected to all the other cells in the region.

Task
Given an  matrix, find and print the number of cells in the largest region in the matrix. Note that there may be more than one region in the matrix.

Input Format

The first line contains an integer, n, denoting the number of rows in the matrix.
The second line contains an integer, m, denoting the number of columns in the matrix.
Each line i of the n subsequent lines contains m space-separated integers describing the respective values filling each row in the matrix.

Constraints
- 0 < n ,m < 10

Output Format

Print the number of cells in the largest region in the given matrix.

Sample Input

4
4
1 1 0 0
0 1 1 0
0 0 1 0
1 0 0 0
Sample Output

5

Explanation

The diagram below depicts two regions of the matrix; for each region, the component cells forming the region are marked with an X:

X X 0 0     1 1 0 0
0 X X 0     0 1 1 0
0 0 X 0     0 0 1 0
1 0 0 0     X 0 0 0
The first region has five cells and the second region has one cell. Because we want to print the number of cells in the largest region of the matrix, we print .

Observation:
I first tried bredth first search and realized that it won't work coz there is no way to get rid of duplicates.

The depth first search using a memo matrix to mark if the cell is visited.

Since I ignored the fact that dimension is less than 10, I use a more genarl approach to define boundary of the search:
I created a wrap around matrix to mark the boundaries. For example, given a 5X4 matrix:

0, 1, 1, 1
0, 0, 0, 1
1, 1, 0, 1
1, 0, 0, 1
0, 1, 1, 1

With wrap, you will have:
0, 0, 0, 0, 0, 0
0, 0, 1, 1, 1, 0
0, 0, 0, 0, 1, 0
0, 1, 1, 0, 1, 0
0, 1, 0, 0, 1, 0
0, 0, 1, 1, 1, 0
0, 0, 0, 0, 0, 0

Because search will stop whenever a 0 is met or the cell was visited before.

The memo matrix is also (n + 2)X(m + 2)

So, the overvall time complexity should be O(n*m)
*/
class SolutionConnectCellsInGrid {
private:
	size_t dfs(const vector<vector<int> >& matrix, vector<vector<size_t> >& memo, size_t i, size_t j, size_t n, size_t m) {
		if (i < 1 || j < 1 || i > n - 2 || j > m - 2 || 0 == matrix[i][j] || 1 == memo[i][j])return 0;
		memo[i][j] = 1;
		//cout << "visited " << i << "," << j << endl;
		return dfs(matrix, memo, i - 1, j - 1, n, m) + dfs(matrix, memo, i - 1, j, n, m) + dfs(matrix, memo, i - 1, j + 1, n, m) + dfs(matrix, memo, i, j - 1, n, m) + dfs(matrix, memo, i, j + 1, n, m) + dfs(matrix, memo, i + 1, j - 1, n, m) + dfs(matrix, memo, i + 1, j, n, m) + dfs(matrix, memo, i + 1, j + 1, n, m) + 1;
	}
	vector<vector<int> > patch(const vector<vector<int> >& matrix, size_t n, size_t m) {
		vector<vector<int> > vec(n + 2, vector<int>(m + 2, 0));
		size_t i = 1;
		for (auto& v : matrix)
			std::copy(v.begin(), v.end(), vec[i++].begin() + 1);
		return vec;
	}
public:
	size_t solve(const vector<vector<int> >& matrix, size_t n, size_t m) {
		vector<vector<int >> matrix1 = this->patch(matrix, n, m);
		size_t ans = 0;
		n += 2, m += 2;
		if (n > 2) {
			if (m > 2) {
				vector<vector<size_t> > visited(n, vector<size_t>(m, 0));
				std::fill(visited[0].begin(), visited[0].end(), 1);
				std::fill(visited[n - 1].begin(), visited[n - 1].end(), 1);
				for (size_t i = 0; i < n; ++i) {
					visited[i][0] = 1;
					visited[i][m - 1] = 1;
				}
				for (size_t i = 1; i < n - 1; ++i) {
					for (size_t j = 1; j < m - 1; ++j)
						if (0 == visited[i][j])
							ans = std::max(ans, dfs(matrix1, visited, i, j, n, m));
				}
			}
		}
		return ans;
	}
};
void TestConnectCellsInGrid() {
	vector<vector<int >> vec{ { 0, 1, 1, 1 },{ 0, 0, 0, 1 },{ 1, 1, 0, 1 },{ 1, 0, 0, 1 },{ 0, 1, 1, 1 } };
	SolutionConnectCellsInGrid so;
	so.solve(vec, 5, 4);
	assert(12 == so.solve(vec, 5, 4));
}