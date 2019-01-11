#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/palindrome-partitioning-ii/
/*
132. Palindrome Partitioning II

Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

Example:

Input: "aab"

Output: 1

Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Observations:

DP appears to be the best approach for this problem. My first try is a naive O(N^3) DP based upon
the idea:

Given S[i : j], there will be (j - i - 1) possible cuts. Say cut at k, k in (i, j) then

If S[i : j] is a palindrome: memo[i][j] = 0;
Else: memo[i][j] = std::min(memo[i][j], memo[i][k] + memo[i + k][j - k] + 1);

There are O(N^2) (i, j) pairs and examine all (j - i - 1) possible cuts on all pairs together will take O(N^3).

Not so good, barely passed, took over 3000ms to run;

Is there a better solution?

Yes, but you will have to tackle the problem in a different view. In fact, the idea is pretty similar to classic
DP: cut woods!

Given cuts[i] as the array for minimum cuts necessary on S[0: i - 1]. The default value on cuts[i] = i - 1, which is actually
the max cuts that could happen if no palindrome at all is discoverd. In other words, the only way to reduce cuts is by
finding palindrome in between S[0: i - 1].

By moving to next char, index from i to j = i + 1 and search any palindrome S[k : j], k in [0, j]

cuts[j] = MIN(cuts[j], cuts[k] + 1)

If the bottom-up approach is taken, we start from S[i : i], single char and expand to len(S) - 1.
From [0, i], cuts[i + 1] is examined. During this process, there will be lots of duplication on finding
palindrome. Therefore, a 2D array memo[i][j] is used to track whether [i, j] is a palindrome. By doing so,
the time for finding the palindrome is reduced to O(1)! Therefore, overall O(N^2) time, but also requires
O(N^2) space.

***
Be aware: applying single char test as palindrome is critical! Or cuts[i + 1] may never be updated if there
is no palindrome found, even cuts[i] had bee updated. By checking single char S[i], the update on cuts[i + 1]
based upon previous cuts will be triggered. cuts[i + 1] = 1 + cuts[i].
***

Is there a way to reduce the need on space? Remember leetcode 5 (Longest Palindromic Substring)?

https://leetcode.com/problems/longest-substring-without-repeating-characters/solution/

The solutions were given in both DP and so called "Expand Around Center". The second approach is able
to reduce space to O(N).

However, in order to use this trick, we will have to give up the established logic for finding palindrome
in the second DP solution, which requires all palindrome ends at j.

Here, starting from index 0, search palindromes with odd and even length, if any S[j : k] is found:

cuts[k + 1] = std::min(cuts[k + 1], cuts[j] + 1).

The search shall stop once a mismatch is found at two ends.

This solution still takes O(N^2) time but space is down to O(N)
*/
class SolutionPalindromePartitioning2 {
public:
	////DP O(N^2) time and O(1) space, 4ms
	int minCut(string s) {
		int len = (int)s.length();
		vector<int> cuts(len + 1, 0);
		for (int i = 0; i <= len; ++i) cuts[i] = i - 1;
		for (int i = 0, j = 0, k = 0; i < len; ++i) {
			j = k = i;
			while (j > -1 && k < len && s[j] == s[k]) cuts[k + 1] = std::min(cuts[k + 1], cuts[j] + 1), --j, ++k;
			j = i, k = i + 1;
			while (j > -1 && k < len && s[j] == s[k]) cuts[k + 1] = std::min(cuts[k + 1], cuts[j] + 1), --j, ++k;
		}
		return 1 > len ? -1 : cuts[len];
	}
	//DP O(N^2) time and O(N^2) space, 8ms
	int minCut0(string s) {
		int len = (int)s.length();
		vector<int> cuts(len + 1, 0);
		vector<vector<bool> > memo(len, vector<bool>(len, false));
		for (int i = 0; i <= len; ++i) cuts[i] = i - 1;
		for (int j = 1; j < len; ++j)
			for (int i = j; i > -1; --i)
				if (s[i] == s[j] && (2 > j - i || true == memo[i + 1][j - 1])) {
					memo[i][j] = true;
					cuts[j + 1] = std::min(cuts[j + 1], cuts[i] + 1);
				}
		return 1 > len ? -1 : cuts[len];
	}
	//O(N^3) DP, barely passed
	int minCut1(string s) {
		int len = (int)s.length();
		vector<vector<int> > memo(len, vector<int>(len + 1, len));
		auto isPalindrome = [&s, &memo, len](int i, int j) -> bool {
			while (i < j) {
				if (len != memo[i][j - i + 1]) return 0 == memo[i][j - i + 1];
				if (s[i++] != s[j--]) return false;
			}
			return true;
		};
		for (int i = 0; i < len; ++i) memo[i][1] = 0;
		for (int i = 2; i <= len; ++i)
			for (int j = 0; j + i <= len; ++j) {
				if (true == isPalindrome(j, j + i - 1)) {
					memo[j][i] = 0;
					continue;
				}
				for (int k = 1; k < i; ++k)
					memo[j][i] = std::min(memo[j][i], memo[j][k] + memo[j + k][i - k] + 1);
			}
		return 1 > len ? -1 : memo[0][len];
	}
};
void TestPalindromePartitioning2() {
	SolutionPalindromePartitioning2 so;
	assert(1 == so.minCut("aab"));
	assert(2 == so.minCut("ababaaaaabbbaa"));
}
/*
Test cases:

""
"aab"
"abcdefg"
"a"
"ab"
"ababa"
"aaaa"
"ababaaaaabbbaa"
"abccbaaabaaorgogqabbbbbbabaccabababajogjoegjgh"
"abaabba"
"ccddccddcddc"
"aaaabbbbbbaaccc"
"aaaaaaaaaaabbb"

Outputs:

-1
1
6
0
1
0
0
2
16
1
2
2
1
*/