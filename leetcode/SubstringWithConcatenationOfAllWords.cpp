#include <cassert>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

//https://leetcode.com/problems/substring-with-concatenation-of-all-words/
/*
30. Substring with Concatenation of All Words

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

Observations:
I did leetcode 76 first, then it's natural for me to try to mimic the same approach here. First try is findSubstring1, it runs O(MN), given
M as the length of vector words and N as the length of string s. The complication is the overlap of word on s, in order to deal with that, the
algorithm has to scan from every index on string s and we will NOT be able to tell exactly if a candidate sliding window is the "Concatenation of All Words".
due to overlap. Therefore, a linear scan costed O(M) has to be conducted every time on a potential fit.

Then I took a look on O(N) solutions posted on leetcode, most of them are very long and use lots of extra storage to support the linear scan, which
are not very leetcode. However, I did notice one fact that I missed: the number of starting points for scan is only P, given P as the length of word in vector words,
coz every word in words having the same length! This solved overlap issue naturally as well! Since we are now only scanning with interval P, there is no need to
worry the overlap.

Also, I managed to reuse hashmap for storing word count by the knowledage we learned in leetcode 76, by the time the left pointer meets the right pointer,
all values in there are reset. Therefore, we can safely reuse it for the next iteration.

Now we have a O(N) time and O(M) space algorithm.
*/
class SolutionSubstringWithConcatenationOfAllWords {
public:
	vector<int> findSubstring(string s, const vector<string>& words) {
		unordered_map<string, int> wordCount;
		vector<int> ans;
		int l = 0, r = 0, cnt = 0, lens = s.length(), lenw = words.size(), len = words[0].length();
		for (auto w : words)++wordCount[w];
		for (int i = 0; i < len; ++i) {
			l = r = i;
			while (r <= lens - len) {
				if (--wordCount[s.substr(r, len)] >= 0)++cnt;
				r += len;
				while (cnt == lenw) {
					if (r - l == lenw * len)ans.push_back(l);
					if (++wordCount[s.substr(l, len)] > 0)--cnt;
					l += len;
				}
			}
			while (l <= lens - len) {
				if (++wordCount[s.substr(l, len)] > 0)--cnt;
				l += len;
			}
		}
		return ans;
	}
	vector<int> findSubstring1(string s, const vector<string>& words) {
		unordered_map<string, int> wordCount, wordCount1, wc;
		vector<int> ans;
		int l = 0, r = 0, cnt = 0, lens = s.length(), lenw = words.size(), len = words[0].length(), i = 0;
		for (auto w : words)++wordCount[w], ++wordCount1[w];
		while (r <= lens - len) {
			if (--wordCount[s.substr(r++, len)] >= 0)++cnt;
			while (cnt >= lenw && r - 1 + len - l >= lenw * len) {
				if (r - 1 + len - l == lenw * len) {
					wc = wordCount1;
					for (i = l; i < r - 1 + len && --wc[s.substr(i, len)] >= 0; i += len);
					if (i == r - 1 + len)ans.push_back(l);
				}
				if (++wordCount[s.substr(l++, len)] > 0)--cnt;
			}
		}
		return ans;
	}
};
void TestSubstringWithConcatenationOfAllWords() {
	SolutionSubstringWithConcatenationOfAllWords so;
	vector<int> ret = { 0, 9 };
	assert(ret == so.findSubstring("barfoothefoobarman", vector<string>{"foo", "bar"}));
	ret = { 1 };
	assert(ret == so.findSubstring("barfoobfoobar", vector<string>{"bar", "arf", "foo", "oob"}));
	ret = {};
	assert(ret == so.findSubstring("abcbbarffoob", vector<string>{"bar", "arf", "foo", "oob"}));
	assert(ret == so.findSubstring("abcbbarffoobcd", vector<string>{"bar", "arf", "foo", "oob"}));
	ret = { 0 };
	assert(ret == so.findSubstring("aaaaaa", vector<string>{"aaa", "aaa"}));
	ret = {};
	assert(ret == so.findSubstring("abababab", vector<string>{"ab", "ba"}));
}