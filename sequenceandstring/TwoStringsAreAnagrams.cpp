#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

//http://www.lintcode.com/en/problem/two-strings-are-anagrams/
/*
TwoStringsAreAnagrams

Write a method anagram(s,t) to decide if two strings are anagrams or not.

Clarification
What is Anagram?
- Two strings are anagram if they can be the same after change the order of characters.

Example
Given s = "abcd", t = "dcab", return true.
Given s = "ab", t = "ab", return true.
Given s = "ab", t = "ac", return false.
*/
class SolutionTwoStringsAreAnagrams {
public:
	/**
	* @param s: The first string
	* @param b: The second string
	* @return true or false
	*/
	bool anagram(string s, string t) {
		// write your code here
		if (s == t)return true;
		int len1 = s.length();
		int len2 = t.length();
		if (len1 != len2 || len1 == 0)return false;
		unordered_map<char, int> map;
		auto end = map.end();
		for (char c : s)
		{
			if (map.find(c) == end)
				map.emplace(c, 1);
			else
				++map[c];
		}
		for (char c : t)
		{
			if (map.find(c) == end)return false;
			else
			{
				--map[c];
				if (0 == map[c])
					map.erase(c);
			}
		}
		return true;
	}
};
