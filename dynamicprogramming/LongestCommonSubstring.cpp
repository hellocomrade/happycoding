#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//http://www.lintcode.com/en/problem/longest-common-substring/
/*
Longest Common Substring

Given two strings, find the longest common substring.

Return the length of it.

Notice

The characters in substring should occur continuously in original string. This is different with subsequence.

Example
Given A = "ABCD", B = "CBCE", return 2.

Observation:

Variation of LCS, the difference is: memo[i][j] will not carry over max(memo[i - 1][j], memo[i][j - 1]) when A[i] != B[j]
instead, just leave 0 there. Why? We are looking for continueous matched substring here, not sebsequence.
*/
class SolutionLongestCommonSubstring {
public:
	/**
	* @param A, B: Two string.
	* @return: the length of the longest common substring.
	*/
	int longestCommonSubstring(string &A, string &B) {
		size_t lena = A.size(), lenb = B.size(), upperleft = 0, max = 0, tmp = 0;
		vector<size_t> memo(lenb, 0);
		for (size_t i = 0; i < lena; ++i) {
			upperleft = 0;
			for (size_t j = 0; j < lenb; ++j) {
				tmp = memo[j];
				memo[j] = (A[i] == B[j]) ? upperleft + 1 : 0;
				upperleft = tmp;
				max = std::max(max, memo[j]);
			}
		}
		return static_cast<int>(max);
	}
	/*
	Classic LCS by DP! The only detail that needs to be addressed here:

	If memo[i][j] == 0, then there is no need to check memo[i - 1][j - 1]
	*/
	int longestCommonSubstring1(string &A, string &B) {
		int len1 = A.size();
		int len2 = B.size();
		if (0 == len1 || 0 == len2)return 0;
		int max = 0;
		vector<vector<int> > memo(len1, vector<int>(len2, 0));
		for (int i = 0; i < len1; ++i)
		{
			for (int j = 0; j < len2; ++j)
			{
				memo[i][j] = A[i] == B[j] ? 1 : 0;
				if (memo[i][j] > 0 && i - 1 >= 0 && j - 1 >= 0)
					memo[i][j] += memo[i - 1][j - 1];
				max = std::max(max, memo[i][j]);
			}
		}
		return max;
	}
};