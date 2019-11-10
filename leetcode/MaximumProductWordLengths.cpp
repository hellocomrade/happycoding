#include <vector>
#include <string>
#include <bitset>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/maximum-product-of-word-lengths/
/*
318. Maximum Product of Word Lengths

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters.
You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]

Output: 16

Explanation: The two words can be "abcw", "xtfn".

Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]

Output: 4

Explanation: The two words can be "ab", "cd".

Example 3:

Input: ["a","aa","aaa","aaaa"]

Output: 0

Explanation: No such pair of words.

Observations:

"each word will contain only lower case letters" indicates playing 26-buckets trick somehow to reduce the time complexity.

Naively, with 26-buckets thing, one may count occurrence of a-z for each word and store the counts in a 26-buckets array
for every word. This takes O(len(words) * max(len(words[i])) time and 26*len(words) space.

Then, comparing each pair in words to find the max product, which takes 26*O(N^2) time given N = len(words), since with each
pair, all 26 bucekts have to be examined.

A smarter way would be using bitwise operation to reduce the comparison on pairs from 26 to 1. This requires
replacing 26-buckets with a 26-bits long bitset. Two words have no same letter if and only if 0 == bitset1 & bitset2,
AND operation returns 0.

Overall time complexity is still O(N^2) but should be faster than the naive version due to the use of bitwise operations.
*/
class SolutionMaximumProductWordLengths {
public:
	int maxProduct(vector<string>& words) {
		int ans = 0, len = (int)words.size();
		vector<bitset<26>> memo(words.size());
		for (int i = 0; i < len; ++i) {
			for (char c : words[i]) memo[i].set((int)(c - 'a'));
			for (int j = 0; j < i; ++j)
				if (true == (memo[j] & memo[i]).none()) ans = std::max(ans, (int)words[i].size() * (int)words[j].size());
		}
		return ans;
	}
};
/*
Test cases:

["abcw","baz","foo","bar","xtfn","abcdef"]
["a","ab","abc","d","cd","bcd","abcd"]
["a","aa","aaa","aaaa"]
["a"]
[]

Outputs:

16
4
0
0
0
*/