#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/custom-sort-string/
/*
791. Custom Sort String

S and T are strings composed of lowercase letters. In S, no letter occurs more than once.

S was sorted in some custom order previously. We want to permute the characters of T so that they match the order
that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.

Return any permutation of T (as a string) that satisfies this property.

Example:

Input:

S = "cba"

T = "abcd"

Output: "cbad"

Explanation:

"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".
Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.

Note:

- S has length at most 26, and no character is repeated in S.
- T has length at most 200.
- S and T consist of lowercase letters only.

Observations:

This problem came to my attention because of a trends post on leetcode for a Facebook onsite interview:

https://leetcode.com/discuss/interview-experience/301164/facebook-onsite-interview-experience-2019

This problem is in round 2.

Sorting a string using a custom order. The most intuitive reaction is using built-in sort with a comp lambda. The custom
order can be recorded by simply looping string S. be aware that S is no longer than 26 without any duplicate. T though,
doesn't have a length contraint. It's possible that some characters's orders are not given in S. In this case, there is
no definition on how these characters should be ordered. I simply gave them order 0, which is different than the standard
answers from leetcode.

Then with the order in hand, simply do a std::sort with a lambda. Overall time compexlity is O(NlogN), given N is the length
of T, space complexity is O(1). See customSortString1.

There is actually a O(N) time solution, using bucket sort (only 26 buckets are needed). Then looping S, which naturally following
the custom order S[i], re-constructing the sorted T with the count in the bucket[S[i]]. The time complexity is O(N) and
space complexity is O(N) as well due to the newly constructed string.

Overall, this is a good screening question that has more than one solution, which gives interviewer the option to ask if
there is alternative solution or comparing the complexity of two solutions etc.

By simply browsing the questions asked in this interview, it sounds like an entry level software engineer position.
*/
class SolutionCustomSortString {
public:
	string customSortString(string S, string T) {
		int i = 0, cnts[26] = { 0 };
		string ans(T.length(), ' ');
		for (char c : T) ++cnts[c - 'a'];
		for (char c : S) while (0 < cnts[c - 'a']) --cnts[c - 'a'], ans[i++] = c;
		for (int j = 0; j < 26; ++j) while (0 < cnts[j]) --cnts[j], ans[i++] = 'a' + j;
		return ans;
	}
	string customSortString1(string S, string T) {
		int i = 0;
		char order[26] = { 0 };
		for (char c : S) order[c - 'a'] = i++;
		auto comp = [&order](auto c1, auto c2) -> bool { return order[c1 - 'a'] < order[c2 - 'a']; };
		std::sort(T.begin(), T.end(), comp);
		return T;
	}
};