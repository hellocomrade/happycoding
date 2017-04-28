#include <cassert>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/longest-uncommon-subsequence-ii
/*
522. Longest Uncommon Subsequence II

Given a list of strings, you need to find the longest uncommon subsequence among them. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.

Example 1:
Input: "aba", "cdc", "eae"
Output: 3
Note:

All the given strings' lengths will not exceed 10.
The length of the given list will be in the range of [2, 50].
*/
class SolutionLongestUncommonSubsequence2 {
private:
	bool isSubsequence(const vector<unordered_set<char> >& haystack, const string& pattern) {
		size_t plen = pattern.size(), hlen = haystack.size();
		int i = 0, j = hlen - 1;
		while (i < plen) {
			while (j > -1 && 0 == haystack[j].size())--j;
			while (j > -1 && haystack[j].end() == haystack[j].find(pattern[i]))--j;
			if (-1 == j)return true;
			else --j, ++i;
		}
		return false;
	}
public:
	int findLUSlength(const vector<string>& strs) {
		vector<unordered_map<string, int> > memo(11, unordered_map<string, int>());
		vector<unordered_set<char> > memochr(11, unordered_set<char>());
		for (auto s : strs) {
			if (memo[s.length()].end() != memo[s.length()].find(s))
				++memo[s.length()][s];
			else
				memo[s.length()].emplace(s, 1);
		}
		for (int i = memo.size() - 1; i > -1; --i) {
			for (auto s : memo[i]) {
				if (1 == s.second && true == this->isSubsequence(memochr, s.first))
					return i;
				else
					for (size_t j = 0; j < s.first.size(); ++j)
						memochr[s.first.size() - j].emplace(s.first[j]);
			}
		}
		return -1;
	}
};
void TestLongestUncommonSubsequence2() {
	SolutionLongestUncommonSubsequence2 so;
	assert(-1 == so.findLUSlength(vector<string>{"", "", ""}));
	assert(-1 == so.findLUSlength(vector<string>{"aabbcc", "aabbcc", "b"}));
	assert(3 == so.findLUSlength(vector<string>{"aba", "cdc", "eae"}));
	assert(4 == so.findLUSlength(vector<string>{"abcd", "abcd", "defg", "bcd", "c", "d"}));
	assert(3 == so.findLUSlength(vector<string>{"abcd", "abcd", "defg", "defg", "efg", "efg", "fff"}));
	assert(-1 == so.findLUSlength(vector<string>{"abc", "abc", "c"}));
	assert(1 == so.findLUSlength(vector<string>{"abc", "abc", "d"}));
}