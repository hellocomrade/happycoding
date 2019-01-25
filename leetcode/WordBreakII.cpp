#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>

using namespace std;

//https://leetcode.com/problems/word-break-ii/
/*
140. Word Break II

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:

Input:

s = "catsanddog"

wordDict = ["cat", "cats", "and", "sand", "dog"]

Output:
[
"cats and dog",
"cat sand dog"
]

Example 2:

Input:

s = "pineapplepenapple"

wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]

Output:
[
"pine apple pen apple",
"pineapple pen apple",
"pine applepen apple"
]

Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:

Input:

s = "catsandog"

wordDict = ["cats", "dog", "sand", "and", "cat"]

Output:

[]

Observations:

This is a follow up on leetcode 139 (Word Break). The same DP algorithm can be applied. Only a 1D
array is necessary for memorization.

My second attempt failed because I didn't notice that the memo[k] with True value could be overwritten.
Therefore, write should happen only if memo[k] == False.

As a follow-up, this problem requires to recover all combinations. A typical Backtracing. Actually,
this is the first time I ever had a leetcode DP problem that requires returning all solutions.

Well, the first attempt failed because of the case "a", []...

The third attempt,see wordBreak, is an iterative DP plus regular BT from index 0. The flaw of this implemention
is that the memo array can not offer any clue to break the string, therefore, substring has to be checked in Set,
which is actually expensive since hash key is string.

wordBreak11 tries to fix the problem by storing all valid sub combinations end at K. This will avoid using BT.
However, MEL was thrown due to the edge case like:

"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]

This is a cons of a bottom-up DP: if there are M states in this DP, all of them will be examined in a bottom-up DP.
It's usually ok. But for this case, since all possible substrs are stored in an exponential way, it blows the memory.
Sometimes, one may see TEL as well. That's because concatenating string in C++ is very expensive as well.

Recursion might be a better fit for this one. It's actually the advantage of top-down DP: it only computes the valid path
due to the nature of recursion. Only the one reached the end get stored, sort of like BT. That has been said, comparing with
bottom-up DP + BT, this approach takes more time since it's a recursion. But, that could be the bias of leetcode test cases
as well.
*/
class SolutionWordBreakII {
public:
	// 8ms top down DP, no BT needed
	vector<string> wordBreak(string s, const vector<string>& wordDict) {
		int len = (int)s.length(), maxlen = 0;
		auto maxelems = std::max_element(wordDict.begin(), wordDict.end(), [](const string& s1, const string& s2) { return s1.length() < s2.length();});
		if (wordDict.end() != maxelems) maxlen = (*maxelems).length();
		unordered_set<string> set(wordDict.begin(), wordDict.end());
		unordered_map<int, vector<string>> memo({ { len,{ "" } } });
		function<vector<string>(int)> dp = [&](int i) {
			if (0 == memo.count(i)) {
				string str;
				for (int j = i + 1; j <= len; ++j) {
					str = s.substr(i, j - i);
					if (1 == set.count(str)) {
						for (const string& st : dp(j))
							memo[i].push_back(str + ("" == st ? "" : " " + st));
					}
				}
			}
			return memo[i];
		};
		return dp(0);
	}
	// MEL, bottom up DP
	vector<string> wordBreak11(string s, const vector<string>& wordDict) {
		int len = (int)s.length(), maxlen = 0;
		string str;
		auto maxelems = std::max_element(wordDict.begin(), wordDict.end(), [](const string& s1, const string& s2) { return s1.length() < s2.length();});
		if (wordDict.end() != maxelems) maxlen = (*maxelems).length();
		unordered_set<string> set(wordDict.begin(), wordDict.end());
		vector<vector<string> > memo(len, vector<string>());
		for (int i = 0; i < len; ++i)
			for (int j = 1; j <= maxlen && i + j <= len; ++j) {
				str = s.substr(i, j);
				if (1 == set.count(str) && (0 == i || 0 < memo[i - 1].size())) {
					if (0 == i) memo[i + j - 1].push_back(str);
					else for (const string& st : memo[i - 1]) memo[i + j - 1].push_back(st + " " + str);
				}
			}
		return memo[len - 1];
	}
	// 4m bottom up DP + BT separately
	vector<string> wordBreak0(string s, const vector<string>& wordDict) {
		int len = (int)s.length(), maxlen = 0;
		string empty;
		vector<string> ans;
		auto maxelems = std::max_element(wordDict.begin(), wordDict.end(), [](const string& s1, const string& s2) { return s1.length() < s2.length();});
		if (wordDict.end() != maxelems) maxlen = (*maxelems).length();
		unordered_set<string> set(wordDict.begin(), wordDict.end());
		vector<bool> memo(len, false);
		for (int i = 0; i < len; ++i)
			for (int j = 1; j <= maxlen && i + j <= len; ++j) {
				if (1 == set.count(s.substr(i, j)) && false == memo[i + j - 1])
					memo[i + j - 1] = (0 == i || true == memo[i - 1]);
			}
		auto bt = [&](int i, string& str, const auto& f) {
			if (len == i) {
				ans.push_back(str);
				return;
			}
			string old_str = str, tmp;
			for (int j = 1; j <= maxlen && i + j <= len; ++j) {
				tmp = s.substr(i, j);
				if (true == memo[i + j - 1] && 1 == set.count(tmp)) {
					str = (0 == str.length()) ? tmp : str + " " + tmp;
					f(i + j, str, f);
					str = old_str;
				}
			}
		};
		if (true == memo[len - 1]) bt(0, empty, bt);
		return ans;
	}
};
void TestWordBreakII() {
	SolutionWordBreakII so;
	so.wordBreak("catsanddog", vector<string> {"cat", "cats", "and", "sand", "dog"});
	so.wordBreak("aaaaaaa", vector<string> {"aaaa", "aaa"});
	so.wordBreak("a", vector<string>());
}
/*
Test cases:

"aaaaaaa"
["aaaa","aaa"]
"a"
[]
"catsanddog"
["cat","cats","and","sand","dog"]
"pineapplepenapple"
["apple", "pen", "applepen", "pine", "pineapple"]
"catsandog"
["cats", "dog", "sand", "and", "cat"]
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]

Outputs:

["aaa aaaa","aaaa aaa"]
[]
["cat sand dog","cats and dog"]
["pine apple pen apple","pine applepen apple","pineapple pen apple"]
[]
[]
*/