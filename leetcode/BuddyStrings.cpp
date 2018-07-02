#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/buddy-strings/
/*
859. Buddy Strings

Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B.

Example 1:

Input: A = "ab", B = "ba"

Output: true

Example 2:

Input: A = "ab", B = "ab"

Output: false

Example 3:

Input: A = "aa", B = "aa"

Output: true

Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"

Output: true

Example 5:

Input: A = "", B = "aa"

Output: false

Note:

- 0 <= A.length <= 20000
- 0 <= B.length <= 20000
- A and B consist only of lowercase letters.

Observations:

This is a "weird" problem. If you think you can get this sovled through two pointers, you might be in trouble. At least,
I can't find such a solution.

Instead, enumerating all scenarios is the right way to go:

- Obviously, if two strings are not equal in length or length is less than 2, they are not buddies;

- If we scan 2 strings together and reach an index k that A[k] != B[k], then two strings are buddies if and only if
the next index l that A[l] != B[l] satisfies: A[k] = B[l] && A[l] = B[k] and such a k is unique. Therefore, by swapping
B[k] and B[l], A == B';

- The exception is A is equal to B, say A = "aab", B = "aab", A and B are buddies since we can swap B[0] and B[1], which is meaningless
but meets the requirements. So, in this case, such a string should have at least one letter repeats more than once.
*/
class SolutionBuddyStrings {
public:
	bool buddyStrings(string A, string B) {
		int lena = (int)A.length(), lenb = (int)B.length();
		if (lena != lenb || lena < 2) return false;
		char cnts[26] = { 0 };
		bool moreThanOne = false;
		for (int i = 0, j = 0; i < lena; j = ++i) {
			if (++cnts[A[i] - 'a'] > 1) moreThanOne = true;
			if (A[i] == B[i]) continue;
			while (j < lena && (B[j] != A[i] || A[j] != B[i])) ++j;
			if (lena == j) return false;
			std::swap(B[i], B[j]);
			return A == B;
		}
		return true == moreThanOne;
	}
};