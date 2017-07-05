#include <cassert>
#include <string>

using namespace std;

//https://www.hackerrank.com/challenges/palindrome-index
/*
Palindrome Index

Given a string, S, of lowercase letters, determine the index of the character whose removal will make S a palindrome.
If S is already a palindrome or no such character exists, then print -1. There will always be a valid solution,
and any correct answer is acceptable. For example, if S = "bcbc", we can either remove 'b' at index 0 or 'c' at index 3.

Input Format

The first line contains an integer, T, denoting the number of test cases.
Each line i of the T subsequent lines (where 0 <= i < T) describes a test case in the form of a single string, Si.

Constraints

- 1 <= T <= 20
- 1 <= |s| <= 10e5 + 5
- All characters are lowercase English letters.

Output Format

Print an integer denoting the zero-indexed position of the character that makes S not a palindrome;
if S is already a palindrome or no such character exists, print -1.

Sample Input

3
aaab
baa
aaa
Sample Output

3
0
-1
Explanation

Test Case 1: "aaab"
Removing 'b' at index 3 results in a palindrome, so we print 3 on a new line.

Test Case 2: "baa"
Removing 'b' at index 0 results in a palindrome, so we print 0 on a new line.

Test Case 3: "aaa"
This string is already a palindrome, so we print -1; however, 0, 1, and 2 are also all acceptable answers, as the string will still be a palindrome if any one of the characters at those indices are removed.

Observations:
Two pointers, aka caterpillar approach should work.

Trick is: decide which one to remove when s[l] != s[r]. Well, since there is always a valid palindrome in a given test case,
we could test if S[l + 1, r] is a palindrome, if so, we know l could be removed. Otherwise, r should be removed.

O(N) time and O(1) space
*/
class SolutionPalindromeIndex {
private:
	bool isValidPalindrome(const string& s, size_t start, size_t end) {
		while (start < end && s[start] == s[end])++start, --end;
		return !(start < end);
	}
public:
	int palindromeIndex(const string& s) {
		size_t len = s.length();
		if (len > 1) {
			size_t l = 0, r = len - 1;
			while (l < r && s[l] == s[r])++l, --r;
			if (l < r)
				return static_cast<int>(true == isValidPalindrome(s, l + 1, r) ? l : r);
		}
		return -1;
	}
};
void TestPalindromeIndex() {
	SolutionPalindromeIndex so;
	assert(3 == so.palindromeIndex("aaab"));
	assert(0 == so.palindromeIndex("baa"));
	assert(-1 == so.palindromeIndex("aaa"));
	assert(1 == so.palindromeIndex("acdcacda"));
	assert(6 == so.palindromeIndex("acdadcda"));
	assert(44 == so.palindromeIndex("hgygsvlfcwnswtuhmyaljkqlqjjqlqkjlaymhutwsnwcwflvsgygh"));
}