#include <cassert>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters
/*
395. Longest Substring with At Least K Repeating Characters

Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.

Observations:

By reading the problem, I immediately had the thought of using two pointers, sliding windows, which works so great that
someone even invented a so called "template" to solve such problems, for example leetcode 76: Minimum Window Substring.

I was fascinated by this approach and eventually got nothing but Wrong Answer...

During this painful path, I did notice this problem having all necessary elements to be solved by divide and conquer:

- First, we count the appearence for each letter since there are only 26 characters;

- Then scanning the string and stop at the letter who's count is lss than k. At this point, index j, we know the longest
possible substring shall either in [0, j - 1] and [j + 1, len(s) - 1];

- Let's examine substring [0, j - 1], then you will notice that the same approach can be taken: count the appearence and split;

That gives you longestSubstring1, which is ACCEPTED but extremely slow for given test cases, such as "aaaaaaaaaaaaa". Two reasons:

1. Too many recount. In each iteration, the count will be done repeatly! We can address this by pre-calculate the prefix sum up front using
O(26N) space. Then when we need to know the counts between [i, j], we just do prefixSum[j] - prefixSum[i - 1];
2. Too few split. In each iteration, there could be more than 1 split points which actually breaks the string into multiple segments.
Therefore, we can split the string along these points to reduce the depth of recursion;

That's longestSubstring0. It's faster but still not impressed.

Then, I gave up the "optimization" for item 1 but keep item 2, that's longestSubstring. Finally, I have my solution on the main street.

Why longestSubstring0 is slower? There are only 28 test cases. My guess is the given test cases is not in favor of it...

My estimate for this algorithm is O(NlogN).

There is actually doable through a two pointers approach. I even saw someone used the sliding window template! But these solution looks so
complicated that I don't even want to dig into them. If it's not pretty and short, it's no point to use it for interview.
*/
class SolutionLongestSubstringWithAtLeastKRepeatingChars {
private:
	int aux(const string &s, int l, int r, int k) {
		if (r - l + 1 < k) return 0;
		int cnt[26] = { 0 }, i = l, ans = -1;
		for (int j = l; j <= r; ++j) ++cnt[s[j] - 'a'];
		for (int j = l; j <= r; ++j) {
			if (cnt[s[j] - 'a'] < k) {
				ans = std::max(ans, this->aux(s, i, j - 1, k));
				i = j + 1;
			}
		}
		if (i > l) ans = std::max(ans, this->aux(s, i, r, k));
		return -1 == ans ? r - l + 1 : ans;
	}
	int aux0(const vector<vector<int> > &memo, const string &s, int l, int r, int k) {
		if (r - l < k) return 0;
		int i = 0, m = l, ans = -1, t = 0;
		for (i = l; i < r; ++i) {
			t = memo[r][s[i] - 'a'] - memo[l][s[i] - 'a'];
			if (t > 0 && t < k) {
				ans = std::max(ans, this->aux0(memo, s, m, i, k));
				m = i + 1;
			}
		}
		if (m != l) ans = std::max(ans, this->aux0(memo, s, m, r, k));
		return -1 == ans ? r - l : ans;
	}
	int aux1(const string &s, int l, int r, int k) {
		if (r - l + 1 < k) return 0;
		int cnt[26] = { 0 }, i = l;
		for (int j = l; j <= r; ++j) ++cnt[s[j] - 'a'];
		while (i <= r && cnt[s[i] - 'a'] >= k) ++i;
		if (i > r) return r - l + 1;
		else return std::max(this->aux1(s, l, i - 1, k), this->aux1(s, i + 1, r, k));
	}
public:
	int longestSubstring(string s, int k) {
		return this->aux(s, 0, s.length() - 1, k);
	}
	int longestSubstring0(string s, int k) {
		int len = (int)s.length();
		if (len < k || k < 1) return 0;
		vector<vector<int> > memo(len + 1, vector<int>(26, 0));
		for (int i = 1; i <= len; ++i) {
			memo[i][s[i - 1] - 'a'] = 1;
			for (int j = 0; j < 26; ++j) memo[i][j] += memo[i - 1][j];
		}
		return this->aux0(memo, s, 0, len, k);
	}
	int longestSubstring1(string s, int k) {
		return this->aux1(s, 0, s.length() - 1, k);
	}
};
void TestLongestSubstringWithAtLeastKRepeatingChars() {
	SolutionLongestSubstringWithAtLeastKRepeatingChars so;
	assert(3 == so.longestSubstring("aaabb", 3));
	assert(0 == so.longestSubstring("aaabbbacccbdc", 4));
	assert(3 == so.longestSubstring("ddacaabbbcecdf", 3));
}
/*
Test cases:

"ababbc"
2
"aaabb"
3
"ddacaabbbcecdf"
3
"ddwgweddaageecabbbcdweeww"
3
"ddwgweddaageecabbbcdweeww"
2
"ddwgweddaageecabbbcdweeww"
1
"bb"
3
"wtqqyriabcaffbcacbfafcbebbdffbacee"
4
"aaabbbacccbdc"
4

Outputs:

5
3
3
3
25
25
0
16
0
*/