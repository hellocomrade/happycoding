#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/
/*
1003. Check If Word Is Valid After Substitutions

We are given that the string "abc" is valid.

From any valid string V, we may split V into two pieces X and Y such that X + Y (X concatenated with Y) is equal to V.
(X or Y may be empty.)  Then, X + "abc" + Y is also valid.

If for example S = "abc", then examples of valid strings are: "abc", "aabcbc", "abcabc", "abcabcababcc".
Examples of invalid strings are: "abccba", "ab", "cababc", "bac".

Return true if and only if the given string S is valid.

Example 1:

Input: "aabcbc"

Output: true

Explanation:

We start with the valid string "abc".
Then we can insert another "abc" between "a" and "bc", resulting in "a" + "abc" + "bc" which is "aabcbc".

Example 2:

Input: "abcabcababcc"
Output: true
Explanation:
"abcabcabc" is valid after consecutive insertings of "abc".
Then we can insert "abc" before the last letter, resulting in "abcabcab" + "abc" + "c" which is "abcabcababcc".

Example 3:

Input: "abccba"

Output: false

Example 4:

Input: "cababc"

Output: false


Note:

- 1 <= S.length <= 20000
- S[i] is 'a', 'b', or 'c'

Observations:

It may take one some time to understand the problem: given "abc" as the seed, one may split the seed into
two parts: ["", "abc"], ["a", "bc"], ["ab", "c"], ["abc", ""] and then concatenate them around "abc" to form
new strings. Those strings are considered as new seeds that can be used to create new valid string by concatenating
the parts around them.

For example, "abcabcabc" is considered as a valid string, because it is built by:

1. "abc" + ["abc"] + "" = "abcabc", using the part: ["abc", ""]
2. "" + ["abcabc"] + "abc" = "abcabcabc", using the part ["", "abc"]

It appears this can be solved by a greedy alogrithm. If the first "abc" (leftmost?) is removed from the given string,
the remaining should remain a valid string. It's no hard to have isValid1 but it takes O(N^2) time due to the
concatenation of substrings: S.substr(0, i) + S.substr(i + 3)

leetcode tags this problem as "string" and "stack", which means it can be solved using the same technics in leetcode 316:

https://leetcode.com/problems/remove-duplicate-letters/

https://github.com/hellocomrade/happycoding/blob/master/leetcode/RemoveDuplicateLetters.cpp

Actually, this problem is simpler than leetcode 316. It's like a variation of leetcode 20 (Valid Parentheses).
The difference is the parentheses here could be: one left: "", "a", "ab", "abc" and "abc", "bc", "c", "" respectively.
Either way, the right parenthese ends at letter 'c'. The problem can be translated to check if the given
string is valid in a cascading parentheses pattern.

The problem can be solved in O(N) time: loop the given string, if current char is not 'c', push it onto a stack.
Otherwise, check the top 2 char on the stack if they are 'b', 'a' and in that order. If they are not or the stack
is less than 2, the given string is not valid. If they are, remove both of them from stack and move to the
next character. This's effectively like removing a parenthese pair formed by "abc" from the string and remaing
string should still be properly paired using "abc" as parentheses if it's valid.

Notes: len(S) >0, therefore empty string is not a concern.
*/
class SolutionCheckWordValidAfterSubstitutions {
public:
	bool isValid(string S) {
		vector<char> stk;
		for (char c : S) {
			if ('c' != c) stk.push_back(c);
			else {
				if (true == stk.empty() || 'b' != stk.back()) return false;
				stk.pop_back();
				if (true == stk.empty() || 'a' != stk.back()) return false;
				stk.pop_back();
			}
		}
		return true == stk.empty();
	}
	//O(N^2) barely passed
	bool isValid1(string S) {
		if (0 == S.length()) return true;
		std::size_t i = S.find("abc");
		if (std::string::npos == i) return false;
		return isValid1(S.substr(0, i) + S.substr(i + 3));
	}
};
/*
Test cases:

"aabcbcabc"
"abc"
"aabcbc"
"abcabc"
"abcabcababcc"
"abccba"
"ab"
"cababc"
"bac"
"a"

Outputs:

true
true
true
true
true
false
false
false
false
false
*/