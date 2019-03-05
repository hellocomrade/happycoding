#include <vector>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/dynamic-programming-classics-the-longest-common-subsequence/
/*
The Longest Common Subsequence


A subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. Longest common subsequence (LCS) of 2 sequences is a subsequence, with maximal length, which is common to both the sequences.

Given two sequences of integers, A = [a[1], a[2],... ,a[n]] and B = [b[1], b[2],... , b[m]], find the longest common subsequence and print it as a line of space-separated integers. If there are multiple common subsequences with the same maximum length, print any one of them.

In case multiple solutions exist, print any of them. It is guaranteed that at least one non-empty common subsequence will exist.

Recommended References: https://youtu.be/V5hZoJ6uK-s

This Youtube video tutorial explains the problem and its solution quite well.

Function Description

Complete the longestCommonSubsequence function in the editor below. It should return an integer array of a longest common subsequence.

longestCommonSubsequence has the following parameter(s):

- a: an array of integers
- b: an array of integers

Input Format

The first line contains two space separated integers n and m, the sizes of sequences A and B.
The next line contains n space-separated integers A[i].
The next line contains m space-separated integers B[j].

Constraints

- 1 <= n <= 100
- 1 <= m <= 100
- 0 <= a[i] < 1000, where i in [1, n]
- 0 <= b[j] < 1000, where j in [1, m]

Constraints

- 1 <=n, m <= 100
- 0 <= a[i], b[j] < 1000

Output Format

Print the longest common subsequence as a series of space-separated integers on one line. In case of multiple valid answers, print any one of them.

Sample Input

5 6
1 2 3 4 1
3 4 1 2 1 3

Sample Output

1 2 3

Explanation

There is no common subsequence with length larger than 3. And "1 2 3", "1 2 1", "3 4 1" are all correct answers.

Observations:

LCS is such a classic DP that it has a wiki page: https://en.wikipedia.org/wiki/Longest_common_subsequence_problem

Hackerranker brougt this up with full LCS, which means the LCS sequence has to be returned.

In a naive implmentation, one can keep tracking the LCS so far at each cell (using a 2D matrix as memorization). However,
it's costly for long sequences.

A smarter way would be only tracking the necessary info during DP and then use these info to "back track" LCS. Therefore,
one can't play the memory-saving approach (rolling 1D array).

Track back is done in the following approach starting from memo[len(a)][len(b)]

- If at memo[i][j], a[i] == b[j], such a digit must be on LCS. This is due to the nature of the problem. This is true if one
looks at a and b from their tails. Wiki has a better explanation on the rationale for LCS which results in that classic recursion.
In such a case, one can safely takes the digit and decreate both i and j by 1 (moving diagonally upper left);
- If at memo[i][j], a[i] != b[j], such a digit must not be on LCS. One shall examine the left cell and cell above memo[i][j] to decide
the next move: if memo[i][j - 1] >(=) memo[i - 1][j], move left; Otherwise, move up;

- Keep the moves until memo[len(a)][len(b)] digits have been picked up. Be aware, there could be multiple LCSs;
*/
class SolutionLongestCommonSubsequence {
public:
	vector<int> longestCommonSubsequence(vector<int> a, vector<int> b) {
		int lena = (int)a.size(), lenb = (int)b.size(), len = 0, m = 0, n = 0, k = 0;
		vector<vector<int>> memo(lena + 1, vector<int>(lenb + 1, 0));
		for (int i = 1; i <= lena; ++i)
			for (int j = 1; j <= lenb; ++j) {
				if (a[i - 1] == b[j - 1]) memo[i][j] = 1 + memo[i - 1][j - 1];
				else memo[i][j] = std::max(memo[i - 1][j], memo[i][j - 1]);
			}
		len = memo[lena][lenb], m = lena, n = lenb;
		vector<int> ans(len, 0);
		while (len > 0) {
			if (a[m - 1] == b[n - 1]) ans[--len] = a[--m], --n;
			else if (memo[m][n - 1] >= memo[m - 1][n]) --n;
			else --m;
		}
		return ans;
	}
};