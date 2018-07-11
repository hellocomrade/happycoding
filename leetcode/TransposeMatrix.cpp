#include <vector>

using namespace std;

//https://leetcode.com/problems/transpose-matrix
/*
868. Transpose Matrix

Given a matrix A, return the transpose of A.

The transpose of a matrix is the matrix flipped over it's main diagonal, switching the row and column indices of the matrix.



Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]

Output: [[1,4,7],[2,5,8],[3,6,9]]

Example 2:

Input: [[1,2,3],[4,5,6]]

Output: [[1,4],[2,5],[3,6]]


Note:

- 1 <= A.length <= 1000
- 1 <= A[0].length <= 1000

Observations:

This is a really trivial problem, but it reminds me leetcode 48 (Rotate Image), which introduces a very clear way to transpose
N by N mattrix in place.

for(int i = 0; i < N; ++i)
for(int j = i + 1; j < N; ++j)
std::swap(M[i][j], M[j][i]);

However, we can't do in place transpose here coz the matrix could be in any dimension...
*/
class SolutionTransposeMatrix {
public:
	vector<vector<int>> transpose(vector<vector<int>>& A) {
		int lenr = (int)A.size(), lenc = (int)A[0].size();
		vector<vector<int> > ans(lenc, vector<int>(lenr, 0));
		for (int i = 0; i < lenc; ++i)
			for (int j = 0; j < lenr; ++j)
				ans[i][j] = A[j][i];
		return ans;
	}
};