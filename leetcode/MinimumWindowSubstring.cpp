#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/minimum-window-substring/description/
/*
76. Minimum Window Substring

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.

Observations:
Seems to be a good fit of hashmap and two pointers, aka sliding window. Come one, leetcode hints you in the title "Minimum Window Substring".

Two hashmap, one for counting the occurrence of each char in t, one for counting the occurrence of chars in t in the sliding window.

Varaible cnt is used to count if every char (including duplicates) in t has shown in the sliding window.

Once cnt == len(t) is met, potential min substring is examined, then move the left pointer forward and adjust the count in hashmap for sliding window
and cnt accordingly.

Boundary condition: l <= len(s) - len(t). There is no need to check l <= r unless len(t) == 0, if so, r will never be touched.

Originally submittal had a running time around 36ms, which appears to be a slow one based upon the chart. Then replacing unordered_map
with vector[128], boost the performace a lot, 9ms.

There is a "template" someone summarized that only requires using one vector:

https://discuss.leetcode.com/topic/30941/here-is-a-10-line-template-that-can-solve-most-substring-problems

The reason we can solve this using one hashmap is: left pointer always repeats on the path the right pointer has passed.

Given hashmap Map for counting the occurrence of each char in t, if right pointer R moves to index i, all chars that are not
on t will have counts as negative. Then if we move the left pointer L to index, all counts on these chars are reset to zero.
In other words, only the chars on t will have non-zero counts (back to what they were) on Map when R and L are met.
*/
class SolutionMinimumWindowSubstring {
public:
	string minWindow(string s, string t) {
		vector<int> cntMap(128, 0);
		int l = 0, r = 0, cnt = 0, lens = s.length(), lent = t.length(), ans = 0, ans1 = lens + 1;
		for (char c : t)++cntMap[c];
		while (r < lens) {
			if (--cntMap[s[r++]] >= 0)++cnt;
			/*
			If r < lens is used at outter exit condition, there has to be an inner while or left pointer
			will never have chance to reach right pointer since right pointer is always running.
			*/
			while (lent == cnt) {
				if (r - l < ans1 - ans)ans = l, ans1 = r;
				//If count remains after l is increased by 1, we will have a shorter candidate.
				if (++cntMap[s[l++]] > 0)--cnt;
			}
		}
		return ans1 == lens + 1 ? "" : s.substr(ans, ans1 - ans);
	}
	string minWindow1(string s, string t) {
		vector<int> cntMap(128, 0);
		int l = 0, r = 0, cnt = 0, lens = s.length(), lent = t.length(), ans = 0, ans1 = lens + 1;
		for (char c : t)++cntMap[c];
		while (l <= lens - lent) {
			if (lent == cnt && r - l < ans1 - ans)
				ans = l, ans1 = r;
			if (cnt < lent && r < lens) {
				if (--cntMap[s[r++]] >= 0)++cnt;
			}
			else if (++cntMap[s[l++]] > 0)--cnt;
		}
		return ans1 == lens + 1 ? "" : s.substr(ans, ans1 - ans);
	}
	string minWindow2(string s, string t) {
		vector<int> cntMap(128, 0), cntWindow(128, 0);
		int l = 0, r = 0, cnt = 0, lens = s.length(), lent = t.length(), ans = 0, ans1 = lens + 1;
		for (char c : t)++cntMap[c];
		while (l <= lens - lent) {
			if (lent == cnt && r - l > -1 && r - l < ans1 - ans)
				ans = l, ans1 = r;
			if (cnt < lent && r < lens) {
				if (cntMap[s[r]] > 0) {
					++cntWindow[s[r]];
					if (cntWindow[s[r]] <= cntMap[s[r]])++cnt;
				}
				++r;
			}
			else {
				if (cntWindow[s[l]] > 0) {
					if (cntWindow[s[l]] <= cntMap[s[l]])--cnt;
					--cntWindow[s[l]];
				}
				++l;
			}
		}
		return ans1 == lens + 1 ? "" : s.substr(ans, ans1 - ans);
	}
	string minWindow3(string s, string t) {
		unordered_map<char, int> cntMap, cntWindow;
		int l = 0, r = 0, cnt = 0, lens = s.length(), lent = t.length(), ans = 0, ans1 = lens + 1;
		for (char c : t)++cntMap[c];
		while (l <= lens - lent) {
			if (lent == cnt && r - l > -1 && r - l < ans1 - ans)
				ans = l, ans1 = r;
			if (cnt < lent && r < lens) {
				if (cntMap.count(s[r]) > 0) {
					++cntWindow[s[r]];
					if (cntWindow[s[r]] <= cntMap[s[r]])++cnt;
				}
				++r;
			}
			else {
				if (cntWindow.count(s[l]) > 0) {
					if (cntWindow[s[l]] <= cntMap[s[l]])--cnt;
					--cntWindow[s[l]];
				}
				++l;
			}
		}
		return ans1 == lens + 1 ? "" : s.substr(ans, ans1 - ans);
	}
};
void TestMinimumWindowSubstring() {
	SolutionMinimumWindowSubstring so;
	assert("a" == so.minWindow("a", "a"));
	assert("" == so.minWindow("a", "b"));
	assert("" == so.minWindow("", "b"));
	assert("" == so.minWindow("a", ""));
	assert("" == so.minWindow("", ""));
	assert("" == so.minWindow("ab", "abc"));
	assert("BANC" == so.minWindow("ADOBECODEBANC", "ABC"));
	assert("NC" == so.minWindow("ADOBECODEBANC", "NC"));
}