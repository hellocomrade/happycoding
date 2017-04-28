#include <cassert>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

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

Observations:
Since I did 521 already, I kind of know 522 should have nothing to do with LCS or DP either. 522 is an expansion of 521, as you can guess.

Instead of comparing only 2 strings in 521, you get a list of strings. Such a "LUS" can be decided in the following rules with precedence:
Examine the strings in a decending order:
1. The longest string is the answer as long as no duplicate can be found for such a string;
["abc", "de", "f"], "abc" is the answer
["abc", "abc", "de"], "abc" is NOT the answer, since the duplicate. "abc" at index 0 is a subsequence of "abc" at index 1.

2. If the first rule can not be met, start from shorter strings using the rule 1 as well with one more addon:
such a string can not be a subsequence of any string that is longer.
["abc", "abc", "de"], "de" is the answer
["abc", "abc", "ac"], "ac" is NOT the answer since "ac" is a subsequence of "abc"

Since we need to scan the string list in a decending order, it appears we need to sort strings by their length. But I took a differnt route, did
too much Java recently so I go with Hashtables and array. No string's length exceeds 10, we only need 11 entries in hashtable, it's like a bucket sort.
Given array memo, at index k stores all strings with length of k. The data type inside the bucket is a Hashtable, key is the string and value is the count of its occurrence.
This can fulfill the sorting but we need a way to check if it's a subsequence.

Instead of checking all string pairs, I used this "bucket"/"bin" sort idea again. Again, since no string is longer than 10, we only need 11 bins. Each index on the bin
represents the position on the string. The data type inside the bin is a Hashset, which tracks unique occurrence for any character at this position in all longer strings.

Then when we have to test if a string S is a subsequence of any string that has been scaned(longer than S), starts from haystack backward, comparing character by character, each
check will take O(logN) time, N is the number of characters at haystack[i]
*/
class SolutionLongestUncommonSubsequence2 {
private:
	bool isSubsequence(const vector<unordered_set<char> >& haystack, const string& pattern) {
		size_t plen = pattern.size(), hlen = haystack.size();
		int i = 0, j = hlen - 1;
		while (i < plen) {
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
				/*
				string s.second is an answer if and only if it doesn't have a duplicate and it is NOT a subsequence of any
				string that is longer than it.
				*/
				if (1 == s.second && true == this->isSubsequence(memochr, s.first))
					return i;
				else//Otherwise, put all characters on to haystack
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