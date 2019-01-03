#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/regular-expression-matching/
/*
10. Regular Expression Matching

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

Observations:
We have two strings and have to do some comparison between them and the decision we make
at every character will also depend on the previous decision. So, typical DP and we probably
start with a 2D matrix.

By playing with given test cases, we know both s and p can be empty, so our 2D matrix will be
having p.size() + 1 to cover empty pattern/string, which is classic for this type of DP.
For example, given "abc" over ".*c", we shall have a matrix like:
0 . * c
0 + - + -
a - + + -
b - - + -
c - - + +

0 a b . * e t
0 + - - - - - -
a - + - - - - -
b - - + - + - -
* - - - + + - -
w - - - - + - -
e - - - - + + -
g - - - - + - -
w - - - - + - -
e - - - - + + -
t - - - - + - +

These extra row and column (1st) will make the algorithm way more convenient, we don't have to
handle the edge cases when dealing with the first row or first column, which would give us a out of range on
memo array.

So, the idea is:
- If (p[j] == s[i] AND '*' != s[i]) OR '.' == p[j], memo[i][j] = memo[i - 1][j - 1]
- If '*' == p[j], things got complicated there. I was stuck there until I peeked the discussion...Too hard for me
to sort out the conditions to cover all cases...
1. If s[i] == p[j - 1] OR '.' == p[j - 1]:
For example 'b' over 'b*' OR 'b' over '.*', in this situation, 'b' could match zero b,
a single 'b' or multiple 'b':
# Match single 'b', then we have to look at if memo[i][j - 1] is True. For example:
'a[b]' over 'ab*';
0 a b  *
0 + - -  -
a - + -  +
[b] - - + [+]
# Match more than one 'b', then we need to look at if memo[i - 1][j] is True. For example:
'ab[b]' over 'ab*';
0 a b  *
0 + - -  -
a - + -  +
b - - +  +
[b] - - - [+]
# Match zero 'b', then we have to look back if memo[i][j - 2] is True. For example:
'[b]' over 'bb*';
0 b b  *
0 + - -  -
[b] - + - [+]

2. If s[i] != p[j - 1] AND '.' != p[j - 1], then we have to look back if memo[i][j - 2] is True. For example:
'[a]' over 'ab*';
0 a b  *
0 + - -  -
[a] - + - [+]

Are we done? NO, s could be "", so does p! Luckily, we have the extra first row added to cover this, that's why
it's a classic trick!

When we do 0 against the pattern, we actually comparing an empty string with the pattern. It serves two purposes:
1. Solve the situation when s and/or pattern is/are empty;
2. Serve as the base memo for lookup for the first character in s to against the patter;

Let's focus on the first role. memo[0][0] guarantees to be True since we are comparing empty with empty. Then the only
condition that could turns a memo[0][k] to True is because of '*'.
- '*' matches empty once, in this case we look at memo[0][j - 1], for example:
0 *
0 + +
- 'x*' matches zero x, in this case we look at memo[0][j - 2], for example:
0 c *
0 + - +
The above case also covers '' against '.*':
0 . *
0 + - +

In terms of time complexity, it's O(M * N). As for space, since only the previously is necessary
for lookup, we could use only O(N) extra space plus 1 varibles for prev[j - 1].

***Update on 2018-10-12***

Redo after a year. DP on strings using 2D matrix, extra 1st row and 1st column are added onto matrix
to handle comparison with empty string on s and match on empty string on p.

Matrix takes pattern p as row and string s as column, for example:

0abb
0
a
b
*

- First populate the first column, a match on empty string is found if:
1. matrix[0][0], empty to empty;
2. current pattern is p[i] = '*' and match on emtpy string was found on matrix[i - 2][0], for example: "" vs "c*";

- Then populate the remaining matrix starting from i = 1 and j = 1, given i is the index on row and j is the index on column.
Three basic situations: pattern could be: '.', '*' and other characters. After a closer look,
'.' and characters other than '*' can be combined:
1. '.' and characters other than '*': given index mon p , n on s, a match is found if and only if:
(p[m] == s[n] || p[m] == '.') && true == matrix[m - 1][n - 1], which means p and s are matched on the previous comparison.

2. '*' is found and it's not on the start of p:
- If p[m - 1] != s[n] && '.' != p[m - 1], then match is only found, if pattern 'p[m - 1]*' means nothing, , true == matrix[i - 2][j], for example: "ab" vs "abc*"
- If p[m - 1] == s[n] || '.' == p[m - 1], then match is found if:
A. 'p[m - 1]*' means empty, true == matrix[i - 2][j];
B. 'p[m - 1]*' means single p[m - 1], true == matrix[i - 1][j];
C. 'p[m - 1]*' means multiple p[m - 1], in this case, one shall look at the previous match on the same row, true == matrix[i][j - 1];

Time complexity: O(len(s)*len(p)), space complexity: O(len(s)*len(p))

How to explain: "" vs "c**"? It's not a match.

***Update on 2019-01-03***

Inspired by <Beautiful Code> Charpter 1: A Regular Expression Matcher, here you go the recursive solution. It's slower than DP but
still a very elegant solution. See isMatch00

In this implementation, two functions have to call each other. Since lambda function defined through auto may not support forward delcaration at all, have to pass the function as an argument.
*/
class SolutionRegularExpressionMatching {
public:
	bool isMatch(string s, string p) {
		int lens = (int)s.length(), lenp = (int)p.length();
		vector<vector<bool> > memo(lenp + 1, vector<bool>(lens + 1, false));
		for (int i = 0; i <= lenp; ++i)
			memo[i][0] = (0 == i || (1 < i && '*' == p[i - 1] && true == memo[i - 2][0]));
		for (int i = 1, c = p[i - 1]; i <= lenp; c = p[i++])
			for (int j = 1, d = s[j - 1]; j <= lens; d = s[j++]) {
				if ('*' == c && 1 < i)
					memo[i][j] = ((p[i - 2] == d) || ('.' == p[i - 2])) ? (true == memo[i - 1][j]) || (true == memo[i][j - 1]) || (true == memo[i - 2][j]) : (true == memo[i - 2][j]);
				else
					memo[i][j] = ((d == c || '.' == c) && true == memo[i - 1][j - 1]);
			}
		return memo[lenp][lens];
	}
	bool isMatch0(string s, string p) {
		int slen = s.size(), plen = p.size();
		if ('*' == p[0])return false;
		vector<bool> cur(vector<bool>(p.size() + 1, false)), prev(vector<bool>(p.size() + 1, true));
		for (int j = 1; j <= plen; ++j)
			prev[j] = '*' == p[j - 1] && (true == prev[j - 1] || (j > 1 && true == prev[j - 2]));
		for (int i = 0; i < slen; ++i) {
			cur[0] = false;
			for (int j = 1; j <= plen; ++j) {
				cur[j] = false;
				if (('*' != s[i] && s[i] == p[j - 1]) || '.' == p[j - 1])
					cur[j] = prev[j - 1];
				else if (false == cur[j] && '*' == p[j - 1]) {
					if ('.' == p[j - 2] || s[i] == p[j - 2])
						cur[j] = prev[j] || cur[j - 1] || cur[j - 2];
					else if (s[i] != p[j - 2])
						cur[j] = cur[j - 2];
				}
			}
			if (i != slen - 1)std::copy(cur.begin(), cur.end(), prev.begin());
		}
		return 0 == slen ? prev[plen] : cur[plen];
	}
	//Recursive
	bool isMatch00(string s, string p) {
		int slen = (int)s.length(), plen = (int)p.length();
		auto matchHere = [&s, &p, slen, plen](int i, int j, const auto& f, const auto& self) -> bool {
			if (plen == j && slen == i) return true;
			if (j + 1 < plen && '*' == p[j + 1]) return f(p[j], i, j + 2, self, f);
			if (s[i] == p[j] || '.' == p[j]) return self(i + 1, j + 1, f, self);
			return false;
		};
		auto matchStar = [&s, &p, slen, plen](char c, int i, int j, const auto& f, const auto& self) -> bool {
			if (plen == j && slen == i) return true;
			do {
				if (true == f(i, j, self, f)) return true;
			} while (i < slen && (s[i++] == c || '.' == c));
			return false;
		};
		return matchHere(0, 0, matchStar, matchHere);
	}
};
void TestRegularExpressionMatching() {
	SolutionRegularExpressionMatching so;
	assert(true == so.isMatch("aab", "c*a*b"));
	assert(true == so.isMatch("abd", "a.e*d.*"));
	assert(true == so.isMatch("", ""));
	assert(false == so.isMatch("", "."));
	assert(true == so.isMatch("", "c*"));
	assert(false == so.isMatch("", "bab"));
	assert(true == so.isMatch("", ".*"));
	assert(true == so.isMatch("a", "a*."));
	assert(true == so.isMatch("a", "ab*"));
	assert(true == so.isMatch("ab", ".*..c*"));
	assert(true == so.isMatch("b", "a*b"));
	assert(false == so.isMatch("abc", "a*"));
	assert(true == so.isMatch("aa", "a*"));
	assert(true == so.isMatch("ab", ".*"));
	assert(true == so.isMatch("ab*wegwet", "ab.*et"));
	assert(true == so.isMatch("abd", "a.e*d*"));
	assert(true == so.isMatch("abd", "a.e*d.*"));
	assert(false == so.isMatch("abdddd", "ab*d"));
	assert(false == so.isMatch("abdddd", "ab*ee"));
	assert(false == so.isMatch("bbba", ".*b"));
	assert(false == so.isMatch("aab", "b.*"));
}
/*
Test cases:

"aa"
"a"
"aa"
"a*"
"ab"
".*"
"aab"
"c*a*b"
"mississippi"
"mis*is*p*."
""
""
""
"."
""
"c*"
""
"bab"
""
".*"
"a"
"a*."
"a"
"ab*"
"ab"
".*..c*"
"b"
"a*b"
"abc"
"a*"
"aa"
"a*"
"ab"
".*"
"abd"
"a.e*d*"
"abd"
"a.e*d.*"
"abdddd"
"ab*d"
"abdddd"
"ab*ee"
"bbba"
".*b"
"aab"
"b.*"
"babbcaacbccbbbbbabb"
"bb*.b*b*a*aba*c"
"bbbba"
".*a*a"
"a"
"ab*"
"aaa"
"ab*a*c*a"
"aaa"
"ab*a"
"baaa"
"abba"
"a"
".*.."
"a"
".*."
"aa"
"."
"abcdede"
"ab.*de"

Outputs:

false
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
true
true
false
true
true
true
true
false
false
false
false
false
true
true
true
false
false
false
true
false
true
*/