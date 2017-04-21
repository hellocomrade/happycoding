#include <cassert>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/implement-strstr/
/*
28. Implement strStr()

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Observations:
It will be easy if we do brute force O(M*N), which is what leetcode expects. However, a KMP or Boyer Moore is more desirable for
the purpose of practice.

https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm

Both algorithms try to avoid restarting too frequently at haystack[i + 1] by jumpping over definitely no match characters. KMP aligns
at the beginning of the pattern (proper prefix, left side), BM focuses on the alignment of the end of the pattern (right side).

As for KMP, the definition of "proper prefix" is the prefixes of a string except the whole string. For example, given "ABCD"
the prefixes are: "A", "AB", "ABC", "ABCD"
the proper prefixes, on the other hand, are: "A", "AB", "ABC".

Why we don't need "ABCD"? Well, simply put: KMP avoids unnecessary comparisons by moving the head of the pattern directly to the next matching position.
It achieves this by a theorm: at given index i on haystack, we apply pattern for comparison, if the match fails on index j of pattern, of course,
i < j, we could jump couple position if and only if there is a longest proper prefix plus suffix available in pattern from 0 to j on pattern. For example:
EEABCABFEEEEEE
  ABCABD

It fails on 'F' vs 'D', instead of aligning pattern to 'B'(index 3), we could jump to index 5 on haystack. This is because in "ABCAB" (before failed 'D'),
we can find a lpps: "AB". Such a substring is a prefix and also suffix of "ABCAB". In other words, we try to use the existing match on the end of pattern
to see if such match also exist at the begining of pattern, if scuh thing exist, we can safely jump over multiple characters on haystack, which guarantees
safe.

Therefore, KMP needs to preprocess the pattern and calculate the longest "proper prefix and suffix" from 0 to i - 1 and store the length in an array
at index i. This process can be done in O(N).

At any given index i, lpps[i] means the longest "proper prefix and suffix" from 0 to i - 1 in the pattern. In such an array, lpps[0] = -1 and lpps[1] = 0.

In terms of implementation, we need two pointers. One for tracking next index for common prefix, nextMatchIndex; the other one is the target char in pattern.
nextMatchIndex actually has two meaning: 1, the longest lpps from 0 to nextMatchIndex - 1; 2, the next possible lpps index

When we examine pattern[nextMatchIndex] against pattern[i - 1], if they are equal, we assign lpps[i] = ++nextMatchIndex, which extends the lpps by 1; if no match,
we can find the fall back position at lpps[nextMatchIndex], which stores the next possible match index in string from 0 to nextMatchIndex - 1 in pattern.
We smiply do nextMatchIndex = lpps[nextMatchIndex], this will be the fall back position to compare with pattern[i - 1].

If such a nextMatchIndex is 0, we know there is no more fallback, we do lpps[i] = 0 and restart lpps process from the beginning of the pattern.
*/
class SolutionImplstrStr {
private:
	vector<long long> longestProperPrefixAndSuffix(string &pattern) {
		size_t len = pattern.length(), i = 2, nextMatchIndex = 0;
		/*
		lpps stands for longest proper prefix and suffix.
		It stores the immediate fallback index value at position (i - 1) for possible match, given index i, assuming pattern[i] and haystack[i] are 
		different, but match occurs at pattern[i - 1] and haystack[i - 1].
		Or you can say it's the longest substring that is both a proper prefix and suffix of string from [0 to i - 1]

		i		0	1	2	3	4	5	6	7	8
		pattern[i]	A	B	A	C	A	B	A	B	C
		lpps[i]		-1	0	0	1	0	1	2	3	2

		Pay attention on i = 8, we examine pattern[8 - 1] = 'B'.
		Step 1: At this moment, nextMatchIndex = 3, which is 'C'. Since they are not equal, we fall back based upon lpps[3] = 1.
		Step 2: This tell me in "ABA", lpps = 1, since 'A' is the lpps of "ABA". We then move nextMatchIndex to the index next to 'A',
		which is 1.
		Step 3: Then in the next iteration, we compare pattern[8 - 1] with the char in pattern on the updated nextMatchIndex, pattern[1], they are the same.
		Step 4: Therefore, nextMatchIndex += 1 and we put lpps[8] = nextMatchIndex = 2
		*/
		vector<long long> lpps(len, -1);
		//lpps[0] = -1, lpps[1] = 0;
		if (len > 1) {
			lpps[1] = 0;
			while (i < len) {
				if (pattern[i - 1] == pattern[nextMatchIndex])
					lpps[i++] = ++nextMatchIndex;
				else if (nextMatchIndex > 0)
					nextMatchIndex = lpps[nextMatchIndex];
				else
					lpps[i++] = 0;
			}
		}
		//Copy elision: http://en.cppreference.com/w/cpp/language/copy_elision
		return lpps;
	}
public:
	int strStr(string haystack, string needle) {
		size_t lenh = haystack.length(), lenn = needle.length(), i = 0, j = 0;
		if (lenh >= lenn) {
			vector<long long> lpps = this->longestProperPrefixAndSuffix(needle);
			while (i <= lenh - lenn) {
				while (j < lenn && haystack[i + j] == needle[j])++j;
				if (j == lenn)
					return i;
				else {
					/*
					when j = 0, lpps[0] = -1 works perfectly to cove the situation that the match fails at beginning of the strings
					in such a case i += j is equal to i, however since lpps[j] == -1, we actually move it to right by 1.
					In other situations, since j > 0, j - lpps[j] moves i to the next start point for comparison.
					*/
					i += j - lpps[j];
					//Avoid wasting time comparing lpps at next start point
					j = lpps[j] <= 0 ? 0 : lpps[j];
				}
			}
		}
		return (0 == lenh && 0 == lenn) ? 0 : -1;
	}
};
void TeststrStr() {
	SolutionImplstrStr so;
	assert(0 == so.strStr("", ""));
	assert(0 == so.strStr("a", "a"));
	assert(-1 == so.strStr("a", "b"));
	assert(15 == so.strStr("ABC ABCDAB ABCDABCDABDE", "ABCDABD"));
	assert(22 == so.strStr("ABC ABADABABC ABCDABCDABACABABCDBABACABABCEGA", "ABACABABC"));
}
