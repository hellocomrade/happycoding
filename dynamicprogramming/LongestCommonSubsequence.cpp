#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//http://lintcode.com/en/problem/longest-common-subsequence/
/*
Given two strings, find the longest common subsequence (LCS).

Your code should return the length of LCS.

Clarification
What's the definition of Longest Common Subsequence?

https://en.wikipedia.org/wiki/Longest_common_subsequence_problem

Example
For "ABCD" and "EDCA", the LCS is "A" (or "D", "C"), return 1.

For "ABCD" and "EACB", the LCS is "AC", return 2.

Observation:

Classic DP

LCS(i, j) = (A[i] == A[j]) ? LCS(i - 1, j - 1) + 1 : MAX(LCS(i, j - 1), LCS(i - 1, j))

O(M*N) time and O(N) space
*/
class SolutionLCS {
public:
	/**
	* @param A, B: Two strings.
	* @return: The length of longest common subsequence of A and B.
	*/
	int longestCommonSubsequence(string A, string B) {
		size_t lena = A.length(), lenb = B.length(), upperleft = 0, tmp = 0;
		// pick the shorter string between A and B, so we could save some memory for memo
		size_t endj = std::min(lena, lenb) + 1, endi = std::max(lena, lenb) + 1;
		string& stri = (endi == lena) ? A : B;
		// in case len(A) == len(B), we can't use (endi == lena) as condition again
		string& strj = (A == stri) ? B : A;
		vector<size_t> memo(endj, 0);
		for (size_t i = 1; i < endi; ++i) {
			//upperleft is memo[i - 1][j - 1]
			upperleft = 0;
			for (size_t j = 1; j < endj; ++j) {
				tmp = memo[j];
				// memo[j] at the end of expression represents memo[i][j - 1]
				memo[j] = (stri[i - 1] == strj[j - 1]) ? upperleft + 1 : std::max(memo[j - 1], memo[j]);
				upperleft = tmp;
			}
		}
		return memo[endj - 1];
	}
};
void testLCS() {
	SolutionLCS so;
	assert(0 == so.longestCommonSubsequence("", "aadbbcbcac"));
	assert(3 == so.longestCommonSubsequence("abc", "abc"));
	assert(5 == so.longestCommonSubsequence("aabcc", "aadbbcbcac"));
	assert(2 == so.longestCommonSubsequence("abcd", "eacb"));
	assert(1 == so.longestCommonSubsequence("abcd", "edca"));
}