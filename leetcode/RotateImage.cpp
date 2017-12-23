#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/rotate-image/
/*
48. Rotate Image

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:
You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Given input matrix =
[
[1,2,3],
[4,5,6],
[7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
[7,4,1],
[8,5,2],
[9,6,3]
]
Example 2:

Given input matrix =
[
[ 5, 1, 9,11],
[ 2, 4, 8,10],
[13, 3, 6, 7],
[15,14,12,16]
],

rotate the input matrix in-place such that it becomes:
[
[15,13, 2, 5],
[14, 3, 4, 1],
[12, 6, 8, 9],
[16, 7,10,11]
]

Observations:
If you are familiar with the algorithm for transpose of a matrix, you could appy the same
approach with a tweak. See the gif animation on wiki:

https://en.wikipedia.org/wiki/Transpose

That's how you do it for transpose: reflecting the elements along its main diagonal.

For this case, requiring in place coz matrix here is NxN.

The tweak: we have to reverse the matrix on row base then apply transpose with two layers
loops:

for (int i = 0; i < n; ++i)
for (int j = i + 1; j < n; ++j)
std::swap(matrix[i][j], matrix[j][i]);

In case you don't know the trick of transpose, you could do this directly layer by layer like
peeling a onion.
*/
class SolutionRotateImage {
public:
	void rotate(vector<vector<int>>& matrix) {
		std::reverse(matrix.begin(), matrix.end());
		int n = matrix.size();
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				std::swap(matrix[i][j], matrix[j][i]);
	}
	void rotate1(vector<vector<int>>& matrix) {
		int n = matrix.size();
		if (0 == n)return;
		int ul = 0, lr = n - 1, i = 0, t = 0;
		while (ul < lr) {
			i = -1;
			while (++i + ul < lr) {
				t = matrix[ul][ul + i];
				matrix[ul][ul + i] = matrix[lr - i][ul];
				matrix[lr - i][ul] = matrix[lr][lr - i];
				matrix[lr][lr - i] = matrix[ul + i][lr];
				matrix[ul + i][lr] = t;
			}
			++ul, --lr;
		}
	}
};