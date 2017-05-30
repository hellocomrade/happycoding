#include <cassert>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/word-break/
/*
139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to get the latest changes.


Observation:
Classic entry level DP question. O(N^2)

In order to check whether string s from index 0 to i can be split into words in wordDict, we have to try

[0-1, 2-i], [0-2, 3-i],... ,[0-(i-1),i]

Each of above can be further split into small sections, which obviously generates lots of duplicates that can be memorized up front.

If we do this bottom up, we will use two pointers, one, i, to mark the end of the index (from 0 to len(str) - 1); the other one, j, is used to
move between [0, i], so str in [0, i] can be split into [0, j - 1], [j, i]. If such a j exists that str[j + 1, i] matches a word in dict and str[0, j - 1]
can be built using wordDict (this is checked using memo array), we know str[0, i] can be built using wordDict, then this info is kept in memo array.

In order to find word in dict faster, we could put wordDict onto a hashset, which gives us O(1) lookup time.

You may get a TLE if you just implment through the above appraoch. The catch is: you don't have to examine all possible j if (i - j) is larger than the longest
word in wordDict. By doing so, certain test cases can be completed earlier.

The boundary condition is tricky if s is allowed to be empty. An extra space in memo is used to cover this.
*/
class SolutionWordBreak {
public:
	bool wordBreak(string s, const vector<string>& wordDict) {
		size_t len = s.length(), maxL = 0;
		auto maxWord = std::max_element(wordDict.begin(), wordDict.end(), [](const string& a, const string& b) {
			return a.length() < b.length();
		});
		if (wordDict.end() != maxWord)
			maxL = (*maxWord).length();
		vector<bool> memo(len, false);
		unordered_set<string> wordMap(wordDict.begin(), wordDict.end());
		auto end = wordMap.end();
		for (size_t i = 0; i < len; ++i) {
			for (long long j = i; (i - j + 1) <= maxL && j > -1; --j) {
				if (0 == j || true == memo[j - 1]) {
					if (end != wordMap.find(s.substr(j, i - j + 1))) {
						memo[i] = true;
						break;
					}
				}
			}
		}
		return memo[len - 1];
	}
	//If string s can be empty
	bool wordBreak1(string s, unordered_set<string> &dict) {
		size_t len = s.length(), maxL = 0;
		auto maxWord = std::max_element(dict.begin(), dict.end(), [](const string& a, const string& b) {
			return a.length() < b.length();
		});
		if (dict.end() != maxWord)
			maxL = (*maxWord).length();
		vector<bool> memo(len + 1, false);
		memo[0] = true;
		unordered_set<string> wordMap(dict.begin(), dict.end());
		auto end = wordMap.end();
		for (size_t i = 1; i <= len; ++i) {
			for (long long j = i - 1; (i - j) <= maxL && j > -1; --j) {
				if (true == memo[j]) {
					if (end != wordMap.find(s.substr(j, i - j))) {
						memo[i] = true;
						break;
					}
				}
			}
		}
		return memo[len];
	}
};
void TestWordBreak() {
	SolutionWordBreak so;
	assert(true == so.wordBreak("leetcode", vector<string>{"leet", "code"}));
	assert(true == so.wordBreak("aaaa", vector<string>{"a"}));
	assert(true == so.wordBreak("aaaa", vector<string>{"aa"}));
	assert(false == so.wordBreak("aaaa", vector<string>{"aaa"}));
	assert(false == so.wordBreak("learningfoobar", vector<string>{"learn", "nin", "gfoob", "rning", "bar", "a"}));
	assert(true == so.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", vector<string>{"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"}));
}
