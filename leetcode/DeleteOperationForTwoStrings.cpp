#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

//https://leetcode.com/problems/delete-operation-for-two-strings/
/*
583. Delete Operation for Two Strings

Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:

Input: "sea", "eat"

Output: 2

Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".

Note:
- The length of given words won't exceed 500.
- Characters in given words can only be lower-case letters.

Observations:

My first thought is this is a variation of Edit Distance. But I have trouble to prove the following is correct:

memo[j + 1] = (word1[j] == word2[i]) ? ul + 1 : std::max(t, memo[j]);

Supposely, if only deletion is allowed, only memo[i - 1][j] should be allowed. However, memo[i - 1][j] means deleting word2[i] in order to get word1[0...j].
The problem indicates: "each step you can delete one character in either string". So, you are allowed to remove one character from either string
(but not both) each step. So, memo[i][j - 1] actually is qualified as deletion: it removes one character word1[j] in order to get word2[0...i].

This is kind of hard for me to swallow, but it appears to be solid.

Well, another approach to solve this is using LCS: find the longest common subsequence from two strings, then all others shall be removed. This is actually
more straightforward if LCS is more familiar to you. Returning using:

len1 - 2 * memo[len1] + len2;

to avoid possible overflow on size_t.
*/
class SolutionDeleteOperationForTwoStrings {
public:
	//LCS DP
	int minDistance(string word1, string word2) {
		size_t len1 = word1.length(), len2 = word2.length();
		vector<size_t> memo(len1 + 1, 0);
		for (size_t i = 0, ul = 0; i < len2; ul = 0, ++i)
			for (size_t j = 0, t = 0; j < len1; ++j) {
				t = memo[j + 1];
				memo[j + 1] = (word1[j] == word2[i]) ? ul + 1 : std::max(t, memo[j]);
				ul = t;
			}
		return static_cast<int>(len1 - 2 * memo[len1] + len2);
	}
	//DP Edit distance
	int minDistance0(string word1, string word2) {
		size_t len1 = word1.length(), len2 = word2.length();
		vector<size_t> memo(len1 + 1, 0);
		std::iota(memo.begin(), memo.end(), 0);
		for (size_t i = 0, ul = 0; i < len2; ++i) {
			ul = memo[0], memo[0] = i + 1;
			for (size_t j = 0, t = 0; j < len1; ++j) {
				t = memo[j + 1];
				memo[j + 1] = (word1[j] == word2[i]) ? ul : std::min(t, memo[j]) + 1;
				ul = t;
			}
		}
		return static_cast<int>(memo[len1]);
	}
};
/*
Test cases:

""
""
"a"
""
""
"a"
"abc"
""
""
"abc"
"sea"
"eat"
"eat"
"sea"
"mart"
"karma"
"karma"
"mart"
"kitten"
"setting"
"setting"
"kitten"
"agjojoejgpwjegwjegjijpohyjerheporhgoerhgoehgihp"
"itjohooghoephgpqhghoerhg"
"itjohooghoephgpqhghoerhg"
"agjojoejgpwjegwjegjijpohyjerheporhgoerhgoehgihp"

Outputs:

0
1
1
3
3
2
2
5
5
7
7
41
41
*/