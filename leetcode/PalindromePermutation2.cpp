#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

//https://leetcode.com/articles/palindrome-permutation-ii/
//https://www.lintcode.com/problem/palindrome-permutation-ii/
/*
267. Palindrome Permutation II

Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

Example 1:

Input: "aabb"

Output: ["abba", "baab"]

Example 2:

Input: "abc"

Output: []

Observations:

This is a problem requiring subscription on leetcode. However, lintcode offers it for free.

Since asking for all solutions, not just the number, backtracing is the first choice.

If a string S can form a palindrome, it meets the following:

- If len(S) is even, then the occurrence of each char in the string is an even number;
- If len(S) is odd, only one char's occurrence in the string is odd number, this include the case like "a";

Based upon above rationales:

1. Count for all 26 letters' occurrence in S;
2. Backtracing on the first half of palindrome, len(S) / 2;
3. The other half is the reversed first half plus the center if len(S) is odd;

In the implementation below, we pre-calcuate center char if exists to simplify procedure in BT.
*/
class SolutionPalindromePermutation2 {
public:
	/**
	* @param s: the given string
	* @return: all the palindromic permutations (without duplicates) of it
	*/
	vector<string> generatePalindromes(const string &s) {
		int charcnt[26] = { 0 }, oddcnt = 0, len = s.length() / 2;
		vector<string> ans;
		vector<char> str(len, 0);
		for (char c : s) oddcnt = (1 == (++charcnt[c - 'a'] & 1)) ? oddcnt + 1 : oddcnt - 1;
		if (1 < oddcnt) return ans;
		else oddcnt = 0;
		for (int i = 0; i < 26; ++i) if (1 == (charcnt[i] & 1)) oddcnt = i + 'a';
		function<void(vector<char>&, int)> bt = [&charcnt, &ans, &bt, len, oddcnt](vector<char> &str, int idx) -> void {
			if (idx == len) {
				string s(str.begin(), str.end()), revs(s);
				std::reverse(revs.begin(), revs.end());
				if (0 < oddcnt) s.push_back((char)oddcnt);
				ans.push_back(s + revs);
				return;
			}
			for (int i = 0; i < 26; ++i) {
				if (1 < charcnt[i]) {
					charcnt[i] -= 2;
					str[idx] = (char)(i + 'a');
					bt(str, idx + 1);
					str[idx] = 0;
					charcnt[i] += 2;
				}
			}
		};
		bt(str, 0);
		return ans;
	}
};
void TestPalindromePermutation2() {
	SolutionPalindromePermutation2 so;
	so.generatePalindromes("aabb");
	so.generatePalindromes("aacbbcc");
}