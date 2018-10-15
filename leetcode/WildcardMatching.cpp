#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/wildcard-matching
/*
44. Wildcard Matching

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

- '?' Matches any single character.
- '*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

Note:

- s could be empty and contains only lowercase letters a-z.
- p could be empty and contains only lowercase letters a-z, and characters like ? or *.

Example 1:

Input:

s = "aa"

p = "a"

Output: false

Explanation: "a" does not match the entire string "aa".

Example 2:

Input:

s = "aa"

p = "*"

Output: true

Explanation: '*' matches any sequence.

Example 3:

Input:

s = "cb"

p = "?a"

Output: false

Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

Example 4:

Input:

s = "adceb"

p = "*a*b"

Output: true

Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

Example 5:

Input:

s = "acdcb"

p = "a*c?b"

Output: false

Observations:

With the experience on leetcode 10 (Regular Expression Matching), it's intuitive to solve this using DP.

Comparing with leetcode 10,

- '?' only matches a single character and not like ".*", "?*" doesn't have special meaning at all.
- More importantly, '*' is handled totally differently, '*' nows matches anything, including empty string.
Note, in leetcode 10, '*' matches zero or more of the preceding element. Here, no more preceding element is required.

These subtle changes affects the implementation of DP. Actually, it's easier to implement than leetcode 10.
My first attempt failed coz "**", which is not well defined in leetcode 10. But here, it's legit, for example: "ho" vs "**ho"

There is a two-pointers solution as well (leetcode probably calls it greedy), which only requires constant space but same time complexity O(MN).

The implementation in isMatch0 is a bit confusing due to the fact of handling edge cases, such as
"" vs "*", "" vs "**", therefor i <= lens is the condition for while loop.

Define four variable, i, j, k, l

1. If p[j] is '?' or equal to s[i], both pointers are increased by 1;
2. Else if p[j] is '*', store i in k, store j in l, increase j by 1. This means '*' is matched with empty string and pattern match will be between p[j + 1] and s[i];
3. Else if '*' was found before but current p[j] and s[i] are no match, then reset i to ++k, j to (l + 1). This means '*'
will be tried to match one (or more) chars in s, pattern search will have to be rewind to the index of '*' plus 1, which is (l + 1);
4. If none of above applied, break the loop;

The total match is found if lenp == j and lens == i at the end.
*/
class SolutionWildcardMatching {
public:
	//DP, O(MN) time, O(MN) space
	bool isMatch(string s, string p) {
		int lens = (int)s.length(), lenp = (int)p.length();
		vector<vector<bool> > memo(lenp + 1, vector<bool>(lens + 1, false));
		for (int i = 0; i <= lenp; ++i)
			memo[i][0] = (0 == i || (true == memo[i - 1][0] && '*' == p[i - 1])) ? true : false;
		for (int i = 1, cp = p[i - 1]; i <= lenp; cp = p[i++])
			for (int j = 1, cs = s[j - 1]; j <= lens; cs = s[j++]) {
				if (cp == cs || '?' == cp) memo[i][j] = memo[i - 1][j - 1];
				else if ('*' == cp) memo[i][j] = (true == memo[i - 1][j - 1] || true == memo[i][j - 1] || true == memo[i - 1][j]);
			}
		return memo[lenp][lens];
	}
	//Greedy, O(MN) time, O(1) space
	bool isMatch0(string s, string p) {
		int lens = (int)s.length(), lenp = (int)p.length(), i = 0, j = 0, k = -1, l = -1;
		while (i <= lens) {
			if (j < lenp && i < lens && ('?' == p[j] || p[j] == s[i])) ++i, ++j;
			else if (j < lenp && '*' == p[j]) k = i, l = j++;
			else if (-1 < l && i < lens) i = ++k, j = l + 1;
			else break;
		}
		return lens == i && lenp == j;
	}
};
/*
Test cases:

"aa"
"*a"
"ab"
"*a"
"a"
"aa"
"aaaa"
"***a"
"abefcdgiescdfimde"
"ab*cd?i*de"
"ho"
"**ho"
""
""
""
"*"
""
"**"
"a"
"**a"
"a"
"a**"
""
"?*"
"a"
"a*"
"aa"
"a"
"aa"
"*"
"cb"
"?a"
"adceb"
"*a*b"
"adceb"
"*a*eb"
"adceb"
"*a*e*b"
"acdcb"
"a*c?b"

Outputs:

true
false
false
true
true
true
true
true
true
true
true
false
true
false
true
false
true
true
true
false
*/