#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/longest-palindromic-subsequence
/*
516. Longest Palindromic Subsequence

Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Example 1:

Input:

"bbbab"

Output:

4

One possible longest palindromic subsequence is "bbbb".

Example 2:

Input:

"cbbd"

Output:

2

One possible longest palindromic subsequence is "bb".

Observations:

This really look like DP and it's DP. It's actually a variation of LCS. If you know LCS and are aware what palindrome is, you can
apply the same LCS algorithm on this with one change: instead of comparing the string itself, we compare string s and its reverse, std::reverse(s).
This is the nature of palidrome: finding the longest common subsequence between a string and its reversed form will reveal the longest palindrom subsequence.

This can be done in O(N^2) time using O(N^2) space and can be optimized using O(N) space since only the immediate previous result is necessary.

See longestPalindromeSubseq

That has been said, there is actually another thought for solving this using DP. GeekforGeeks even made a video:

https://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/

We still use a 2D array, but it's index [i, j] here represents the longest palindrom in substring s[i, j]. It actually still apply LCS's
transition function:

LPS[i, j] = 2 + LPS[i + 1, j - 1] IF s[i] == s[j] ELSE MAX(LPS[i + 1, j], LPS[i, j - 1])

See longestPalindromeSubseq1

By visualizing the memorization 2D array, you will see we only populate the upper triangular matrix. So definitely we could
optimize the space. This can be reduced to O(N) as well. But I have trouble to figure it out. I stole it from someone else:

See longestPalindromeSubseq0

The complication is to find a way to make sure only the last memo row is needed. So, instead of finding all LPS for substrings with same length,
it goes for all substrings starting at the same index i till the end of the string. Such as substring s[i,j] can satisfy our demand by storing the
the count at memo[j], yes, the end of the substring.
*/
class SolutionLongestPalindromicSubsequence {
public:
	int longestPalindromeSubseq(string s) {
		int len = (int)s.length(), upperleft = 0, tmp = 0;
		vector<int> memo(len + 1, 0);
		for (int j = len - 1; j > -1; upperleft = 0, --j)
			for (int i = 0; i < len; ++i) {
				tmp = memo[i + 1];
				memo[i + 1] = (s[i] == s[j]) ? 1 + upperleft : std::max(tmp, memo[i]);
				upperleft = tmp;
			}
		return memo[len];
	}
	int longestPalindromeSubseq0(string s) {
		// dp[i][j] longest palindrome subsequence within s[i...j]
		//
		// dp[i][j] = dp[i+1][j-1] + 2 if s[i] == s[j]
		// dp[i][j] = max(dp[i+1][j], dp[i][j-1]) if s[i] != s[j]
		// 
		// dp[i][i] = 1. dp[i][i-1] = 0.
		//
		// To save space, use 1d array.
		// i: n-1 -> 0. j : i->n-1

		int n = s.size();
		vector<int> dp(n, 0);

		for (int i = n - 1; i >= 0; --i) {
			int p1, p2 = dp[i];
			dp[i] = 1;
			for (int j = i + 1; j < n; ++j) {
				p1 = dp[j];
				dp[j] = (s[i] == s[j]) ? p2 + 2 : max(p1, dp[j - 1]);
				p2 = p1;
			}
		}
		return dp[n - 1];
	}
	int longestPalindromeSubseq1(string s) {
		int len = (int)s.length();
		vector<vector<int> > memo(len, vector<int>(len, 0));
		for (int i = 0; i < len; ++i) memo[i][i] = 1;
		for (int j = 1; j < len; ++j)
			for (int i = 0; i < len - j; ++i)
				memo[i][i + j] = (s[i] == s[i + j]) ? 2 + memo[i + 1][i + j - 1] : std::max(memo[i][i + j - 1], memo[i + 1][i + j]);
		return 0 == len ? 0 : memo[0][len - 1];
	}
};
void TestLongestPalindromicSubsequence() {
	SolutionLongestPalindromicSubsequence so;
	so.longestPalindromeSubseq("bbbab");
}
/*
Test cases:

"bbbab"
"cbbd"
""
"a"
"ab"
"acda"
"abc"
"acecdfacadef"
"agwewpjpjpawegjpwtiqiqj[m[kjqjpojtqetqoit"

Outputs:

4
2
0
1
1
3
1
7
15
*/