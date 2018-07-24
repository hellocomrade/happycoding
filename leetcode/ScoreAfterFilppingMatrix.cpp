#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/score-after-flipping-matrix
/*
861. Score After Flipping Matrix

We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score.



Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]

Output: 39

Explanation:

Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].

0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39


Note:
- 1 <= A.length <= 20
- 1 <= A[0].length <= 20
- A[i][j] is 0 or 1.

Observations:

Even the size of matrix is as small as 20 by 20, a complete search might be still too much...is DP a way to go? Some facts:

1. A 1 in the ith column, contributes 1 << (A[0].length - 1) to the final result;
2. 2^i > 2^(i - 1) + 2^(i - 2) + ... + 2^0;

If the second fact is discovered, one should realize this problem can be solved using greedy: make sure the bits in first column
are all 1s, then count the 1 bits in other column. This will guarantee the maximum score.

So, the naive approach will be:

1. Flipping all rows that don't have 1 in the first column (O(MN) time);
2. Starting from column 1, make sure each column has more 1s than 0s, this will take (O(MN));
3. O(MN) time to calculate final score;

The step 3 calcuation can be done either by adding integers in decimal together or a smarter way: calculating the score bit by bit (column by column)
using the first fact we have discovered. Do you remember leetcode 477 (Total Hamming Distance)?

Can we further simplify the solution? Is the simulation of flipping really necessary? Considering the fact the matrix is examined column by column and
the values in the first column are known, we could find whether A[i][j] is toggled after step 1. Therefore, the number of bits that is equal to A[i][0] in each column
can be counted in O(M) time. Then MAX(cnt, M - cnt) is the number of 1 bits after step 2. The contribution of this column to the final score is:
MAX(cnt, M - cnt) * (1 << (N - j - 1)), given M is the number of rows in A, N is the number of columns in A, j is the index on N.
*/
class SolutionScoreAfterFilppingMatrix {
public:
	int matrixScore(vector<vector<int>>& A) {
		int rlen = A.size(), clen = A[0].size();
		int ans = rlen * (1 << (clen - 1));
		for (int i = 1, cnt = 0; i < clen; cnt = 0, ++i) {
			for (int j = 0; j < rlen; ++j)
				if (A[j][0] == A[j][i]) ++cnt;
			ans += std::max(cnt, rlen - cnt) * (1 << (clen - i - 1));
		}
		return ans;
	}
};
/*
Test cases:

[[0,0,1,1],[1,0,1,0],[1,1,0,0]]
[[1]]
[[0]]
[[1,0]]
[[0,0,1],[1,1,1],[1,0,0],[0,1,0]]

Outputs:

39
1
1
3
22
*/