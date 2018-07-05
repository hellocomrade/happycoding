#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
/*
712. Minimum ASCII Delete Sum for Two Strings

Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:


Input: s1 = "sea", s2 = "eat"

Output: 231

Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:

Input: s1 = "delete", s2 = "leet"

Output: 403

Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

Note:
- 0 < s1.length, s2.length <= 1000.
- All elements of each string will have an ASCII value in [97, 122].

Observations:

This is a variation of Edit Distance (leetcode 72) and comparable with Delete Operation for Two Strings (leetcode 583) as well since
they both are derived from Edit Distance. The difference here is that we apply costs/weight instead of char counts.

Therefore, for [i, 0] and [0, j], we are doinng prefix sum/partial sum instead of index increment.

Comparing with official solution here:

https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/solution/

My question is:

ul + (long long)s1[j] + (long long)s2[i]

If this is necessary? If not, how can we prove it?
*/
class SolutionMinimumASCIIDeleteSumForTwoStrings {
public:
	int minimumDeleteSum(string s1, string s2) {
		size_t len1 = s1.length(), len2 = s2.length();
		vector<long long> memo(len1 + 1, 0);
		long long ul = 0, t = 0;
		for (size_t i = 1; i <= len1; ++i) memo[i] = memo[i - 1] + (long long)s1[i - 1];
		for (size_t i = 0; i < len2; ++i) {
			ul = memo[0], memo[0] += s2[i];
			for (size_t j = 0; j < len1; ++j) {
				t = memo[j + 1];
				memo[j + 1] = (s1[j] == s2[i]) ? ul : std::min(ul + (long long)s1[j] + (long long)s2[i], std::min(t + (long long)s2[i], memo[j] + (long long)s1[j]));
				ul = t;
			}
		}
		return static_cast<int>(memo[len1]);
	}
};