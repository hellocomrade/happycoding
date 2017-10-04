#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/longest-palindromic-substring/
/*
5. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"

Output: "bb"

Observations:
I almost tried DP, but DP can only gives us O(N^2). so, why not try sliding window?

A palindrome is always either completely sysmmetrical or mirrored around a center, classic even/odd situation...

So, at every given i, 0 <= i < len(s), we try out both even and odd palindrome with pointer m and n, see how far we can go at both
direction until:
- m < 0
- n >= len(s)
- s[m] != s[n]

Then we compare m - n + 1 with variables that are meant to track longest.

Note: I used two pairs of pointers: m1, n1 for odd, m2, n2 for even. Therefore, m1 - n1 - 1 is always odd and m2 - n2 - 1 is always even.
For the situation, there is no palindrome at given index i, m1 - n1 + 1 = 1, which is expected to get a single character which is a palindrome as well.

Wait, is the length supposed to be m1 - n1 + 1? Why (m1 - n1 - 1)?! Well, by exiting the loop, bot m1 and n1 are at an invalid positions,
has to rewind, which means m1 + 1 and n1 - 1, therefore n1 - 1 - (m1 + 1) + 1 is the length.

Leetcode has official solutions here:
https://leetcode.com/problems/longest-palindromic-substring/solution/

It points out that there are 2n - 1 possible centers in a string in order for a palindrome, for example
a[b]a, ab[]ba
This is a good way to think about this question!

Implementation wide, since I use C++, I tried to delay using substr and copy construct as much as I can coz
they are really expensive for string operations...

According to the offical soluations, there is a DP version. Idea is:

Given p(i, j) = True, 0 <= i = j < len(s)

then p(i, j) = p(i + 1, j - 1) && s[i + 1] == s[j - 1], 0 <= i < j < len(s)

I think it demonstrates 2d memorization pretty well.
Unlike other string DP, using 2D memo involves comparing str[i] with str[j] sequentially. Here, we compare str[i] with
str[i + step].
*/
class SolutionLongestPalindromicSubstr {
public:
	string longestPalindrome(string s) {
		int len = s.size(), m1 = 0, n1 = 0, m2 = 0, n2 = 0, a1 = 0, a2 = 0;
		for (int i = 0; i < len; ++i) {
			m1 = n1 = i;
			while (m1 > -1 && n1 < len && s[m1] == s[n1])--m1, ++n1;
			m2 = i - 1, n2 = i;
			while (m2 > -1 && n2 < len && s[m2] == s[n2])--m2, ++n2;
			if (a2 - a1 + 1 < std::max(n1 - m1 - 1, n2 - m2 - 1)) {
				a1 = n1 - m1 - 1 > n2 - m2 - 1 ? m1 + 1 : m2 + 1;
				a2 = n1 - m1 - 1 > n2 - m2 - 1 ? n1 - 1 : n2 - 1;
			}
		}
		return s.substr(a1, a2 - a1 + 1);
	}
	//DP
	string longestPalindrome1(string s) {
		int len = s.size(), step = 1, alen = 1, start = 0;
		vector<vector<bool> > memo(len, vector<bool>(len));
		for (int i = 0; i < len; ++i) {
			++step;
			for (int j = 0; j + step <= len; ++j) {
				memo[j][j + step - 1] = (j + 1 >= j + step - 2 || true == memo[j + 1][j + step - 2]) && s[j] == s[j + step - 1];
				if (true == memo[j][j + step - 1] && alen < step) {
					start = j;
					alen = step;
				}
			}
		}
		return 0 == len ? s : s.substr(start, alen);
	}
};
void TestLongestPalindromicSubstr() {
	SolutionLongestPalindromicSubstr so;
	assert("abba" == so.longestPalindrome("cdabbacd"));
	assert("ccccc" == so.longestPalindrome("ccccc"));
}