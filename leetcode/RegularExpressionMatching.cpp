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
*/
class SolutionRegularExpressionMatching {
public:
	bool isMatch(string s, string p) {
		int slen = s.size(), plen = p.size();
		if ('*' == p[0])return false;
		vector<bool> cur(vector<bool>(p.size() + 1, false)), prev(vector<bool>(p.size() + 1, true));
		for (int j = 1; j <= plen; ++j)
			prev[j] = '*' == p[j - 1] && (true == prev[j - 1] || (j > 1 && true == prev[j - 2]));
		for (int i = 0; i < slen; ++i) {
			cur[0] = false;
			for (int j = 1; j <= plen; ++j) {
				cur[j] = false;
				if (s[i] == p[j - 1] || '.' == p[j - 1])
					cur[j] = prev[j - 1];
				else if (false == cur[j] && '*' == p[j - 1]) {
					if ('.' == p[j - 2] || s[i] == p[j - 2])
						cur[j] = prev[j] || prev[j - 1] || cur[j - 2];
					else if (s[i] != p[j - 2])
						cur[j] = cur[j - 2];
				}
			}
			if (i != slen - 1)std::copy(cur.begin(), cur.end(), prev.begin());
		}
		return 0 == slen ? prev[plen] : cur[plen];
	}
};
void TestRegularExpressionMatching() {
	SolutionRegularExpressionMatching so;
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