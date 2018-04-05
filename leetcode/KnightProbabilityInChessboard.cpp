#include <cmath>
#include <vector>

using namespace std;

//https://leetcode.com/problems/knight-probability-in-chessboard/
/*
688. Knight Probability in Chessboard

On an NxN chessboard, a knight starts at the r-th row and c-th column and attempts to make exactly K moves. The rows and columns are 0 indexed, so the top-left square is (0, 0), and the bottom-right square is (N-1, N-1).

A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.


Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly K moves or has moved off the chessboard. Return the probability that the knight remains on the board after it has stopped moving.

Example:

Input: 3, 2, 0, 0

Output: 0.0625

Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.

Note:
- N will be between 1 and 25.
- K will be between 0 and 100.

The knight always initially starts on the board.

Observations:

If you do place Chess, take a look here:

https://en.wikipedia.org/wiki/Knight_(chess)

Then pay extra attention on the SVG labled with "Distance from the f5-square, counted in knight moves"

The naive approach would be: try every direction for each moves till K moves. But the trouble is the size of the problem:

Since each move will lead to 8 possibilities in the next round, if max(K) = 100, we may end up doing 8^K checks! It's a huge number!

2.0370359763344860862684456884094e+90

You may also notice that max(N) = 25, less than K, which means the knight will probablly move backward in a repeating fasion once the boundary is reached.

So, if we go this route, the amount of memory we need will be out of control, no matter iteratively or recursively.

If we tackle from a different angle, say at the M move at position [i, j], given M in [0, K] and i, j in [0, N),
For the possible P moves, given P in [0, 8], if we define the amount of possible moves as Memo[M][i][j],

Memo[M][i][j] = Memo[M - 1][i1][j1] + Memo[M - 1][i2][j2] + ... + Memo[M - 1][in][jn], n = P;

When M = 0, Memo[M][i][j] = 1, which means without any move, the move count is 1, which is staying.

So, what's that? Looks familiar, huh? That's a DP! It doesn't involve any optimization but still, the result at step i is decided
by the results at step i - 1, so memorization at least...

Given a N X N grid, we can easily test the knight's L shape move on each cell,  then save it in a 2D array. On the next round, we scan
every cell to find all possible cells that the knight can move to, but the total possible move count at round 2 will be the summary of all possible cells'
move count for the last round.

Therefore, we can memorize everything in a 3D grid: memo[K][N][N].

The fact is that we only care the previous round, then we can simplify the space to memo[2][N][N].

Also, due to the massive amount of counts, even long long is not big enough to hold the count, double has to be used. This's kind of ugly for
storing integer using double. Therefore, there is an alternative by storing only the possibility for each cell at each round. This guarantee
the value is between 0 to 1 cross the grid.

Memo[M][i][j] = Memo[M - 1][i1][j1] / 8 + Memo[M - 1][i2][j2] / 8 + ... + Memo[M - 1][in][jn] / 8, n = P;

When M = 0, Memo[M][i][j] = 1, which means without any move, the possibility for being on the board is 100%;

This is more elegant for M = 0 as well, however this approach may take a penalty on performance coz there are 8*K*N^2 extra divisions.

Total time complexity is O(KN^2), space is O(N^2).

Official soluation is at:

https://leetcode.com/problems/knight-probability-in-chessboard/solution/
*/
class SolutionKnightProbabilityInChessboard {
public:
	//less space
	double knightProbability(int N, int K, int r, int c) {
		vector<vector<vector<double> > > memo(2, vector<vector<double> >(N, vector<double>(N, 1.0)));
		for (int m = 1; m <= K; ++m) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					memo[1 & m][i][j] = 0;
					if (i - 2 > -1) {
						if (j - 1 > -1) memo[1 & m][i][j] += memo[1 & (m - 1)][i - 2][j - 1] / 8.0;
						if (j + 1 < N) memo[1 & m][i][j] += memo[1 & (m - 1)][i - 2][j + 1] / 8.0;
					}
					if (i + 2 < N) {
						if (j - 1 > -1) memo[1 & m][i][j] += memo[1 & (m - 1)][i + 2][j - 1] / 8.0;
						if (j + 1 < N) memo[1 & m][i][j] += memo[1 & (m - 1)][i + 2][j + 1] / 8.0;
					}
					if (i - 1 > -1) {
						if (j - 2 > -1) memo[1 & m][i][j] += memo[1 & (m - 1)][i - 1][j - 2] / 8.0;
						if (j + 2 < N) memo[1 & m][i][j] += memo[1 & (m - 1)][i - 1][j + 2] / 8.0;
					}
					if (i + 1 < N) {
						if (j - 2 > -1) memo[1 & m][i][j] += memo[1 & (m - 1)][i + 1][j - 2] / 8.0;
						if (j + 2 < N) memo[1 & m][i][j] += memo[1 & (m - 1)][i + 1][j + 2] / 8.0;
					}
				}
			}
		}
		return memo[1 & K][r][c];
	}
	//Less space
	double knightProbability0(int N, int K, int r, int c) {
		vector<vector<vector<double> > > memo(2, vector<vector<double> >(N, vector<double>(N, 1.0)));
		double cnt = 0.0;
		for (int m = 1; m <= K; ++m) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					cnt = 0.0;
					if (i - 2 > -1) {
						if (j - 1 > -1) cnt += memo[1 & (m - 1)][i - 2][j - 1];
						if (j + 1 < N) cnt += memo[1 & (m - 1)][i - 2][j + 1];
					}
					if (i + 2 < N) {
						if (j - 1 > -1) cnt += memo[1 & (m - 1)][i + 2][j - 1];
						if (j + 1 < N) cnt += memo[1 & (m - 1)][i + 2][j + 1];
					}
					if (i - 1 > -1) {
						if (j - 2 > -1) cnt += memo[1 & (m - 1)][i - 1][j - 2];
						if (j + 2 < N) cnt += memo[1 & (m - 1)][i - 1][j + 2];
					}
					if (i + 1 < N) {
						if (j - 2 > -1) cnt += memo[1 & (m - 1)][i + 1][j - 2];
						if (j + 2 < N) cnt += memo[1 & (m - 1)][i + 1][j + 2];
					}
					memo[1 & m][i][j] = cnt;
				}
			}
		}
		return  memo[1 & K][r][c] / pow(8.0, K);
	}
	//A little bit elegant but a bit slower as well
	double knightProbability1(int N, int K, int r, int c) {
		vector<vector<vector<double> > > memo(K + 1, vector<vector<double> >(N, vector<double>(N, 1.0)));
		for (int m = 1; m <= K; ++m) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					memo[m][i][j] = 0;
					if (i - 2 > -1) {
						if (j - 1 > -1) memo[m][i][j] += memo[m - 1][i - 2][j - 1] / 8.0;
						if (j + 1 < N) memo[m][i][j] += memo[m - 1][i - 2][j + 1] / 8.0;
					}
					if (i + 2 < N) {
						if (j - 1 > -1) memo[m][i][j] += memo[m - 1][i + 2][j - 1] / 8.0;
						if (j + 1 < N) memo[m][i][j] += memo[m - 1][i + 2][j + 1] / 8.0;
					}
					if (i - 1 > -1) {
						if (j - 2 > -1) memo[m][i][j] += memo[m - 1][i - 1][j - 2] / 8.0;
						if (j + 2 < N) memo[m][i][j] += memo[m - 1][i - 1][j + 2] / 8.0;
					}
					if (i + 1 < N) {
						if (j - 2 > -1) memo[m][i][j] += memo[m - 1][i + 1][j - 2] / 8.0;
						if (j + 2 < N) memo[m][i][j] += memo[m - 1][i + 1][j + 2] / 8.0;
					}
				}
			}
		}
		return memo[K][r][c];
	}
	//A little bit faster since there is less division
	double knightProbability2(int N, int K, int r, int c) {
		vector<vector<vector<double> > > memo(K + 1, vector<vector<double> >(N, vector<double>(N, 1.0)));
		double cnt = 0.0;
		for (int m = 1; m <= K; ++m) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					cnt = 0.0;
					if (i - 2 > -1) {
						if (j - 1 > -1) cnt += memo[m - 1][i - 2][j - 1];
						if (j + 1 < N) cnt += memo[m - 1][i - 2][j + 1];
					}
					if (i + 2 < N) {
						if (j - 1 > -1) cnt += memo[m - 1][i + 2][j - 1];
						if (j + 1 < N) cnt += memo[m - 1][i + 2][j + 1];
					}
					if (i - 1 > -1) {
						if (j - 2 > -1) cnt += memo[m - 1][i - 1][j - 2];
						if (j + 2 < N) cnt += memo[m - 1][i - 1][j + 2];
					}
					if (i + 1 < N) {
						if (j - 2 > -1) cnt += memo[m - 1][i + 1][j - 2];
						if (j + 2 < N) cnt += memo[m - 1][i + 1][j + 2];
					}
					memo[m][i][j] = cnt;
				}
			}
		}
		return memo[K][r][c] / pow(8.0, K);
	}
};