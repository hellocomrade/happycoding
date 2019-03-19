#include <string>

using namespace std;

//https://leetcode.com/problems/isomorphic-strings
/*
205. Isomorphic Strings

Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"

Output: true

Example 2:

Input: s = "foo", t = "bar"

Output: false

Example 3:

Input: s = "paper", t = "title"

Output: true

Note:
- You may assume both s and t have the same length.

Observations:

1. Characters in test cases include ASCII other than lowercase letters;
2. Mapping here means one to one mapping from s to t only, therefore s = "ab", t = "aa" is False since 'a' -> 'a', 'b' can't map to 'a' anymore.
   s = "ab", t ="ca" is True coz mapping is one direction only, 'a' -> 'c' doesn't affect 'b' -> 'a' since the second 'a' is in t;
3. In isIsomorphic, mapping is indicated by (index + 1), 0 based index can't be used directly coz 0 also means not mapped at all, which
   could conflict with mapping from s[0] to t[0]. Using character as value doesn't have this concern, see isIsomorphic1.
*/
class SolutionIsomorphicStrings {
public:
	bool isIsomorphic(string s, string t) {
		int map[256] = { 0 }, rmap[256] = { 0 }, len = (int)s.length();
		for (int i = 0; i < len; ++i) {
			if (map[(int)s[i]] != rmap[(int)t[i]]) return false;
			map[(int)s[i]] = rmap[(int)t[i]] = i + 1;
		}
		return true;
	}
	bool isIsomorphic1(string s, string t) {
		int map[256] = { 0 }, rmap[256] = { 0 }, lens = (int)s.length(), lent = (int)t.length();
		if (lent != lens) return false;
		for (int i = 0; i < lens; ++i) {
			if (0 == map[(int)s[i]] && 0 == rmap[(int)t[i]]) map[(int)s[i]] = (int)t[i], rmap[(int)t[i]] = (int)s[i];
			else if ((int)t[i] != map[(int)s[i]]) return false;
		}
		return true;
	}
};
/*
Test cases:

"egg"
"add"
"foo"
"bar"
"paper"
"title"
"aaa"
"aaa"
""
""
"13"
"42"
"ab"
"aa"
"ab"
"ca"

Outputs:

true
false
true
true
true
true
false
true
*/