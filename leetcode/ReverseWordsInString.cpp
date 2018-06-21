#include <cassert>
#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/reverse-words-in-a-string/
/*
151. Reverse Words in a String

Given an input string, reverse the string word by word.

Example:

Input: "the sky is blue",

Output: "blue is sky the".

Note:

A word is defined as a sequence of non-space characters.

Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.

Follow up: For C programmers, try to solve it in-place in O(1) space.

Observations:

This problem has over 1.3 million submissions and acceptance rate is only 15%... this is partially because "Run Code" function is disabled probably due to the
risk of buffer overflow vulnerability?

Anyway, this is definitely a linear solution and space usage should be O(1) for C/C++. My first attempt (reverseWords1) using two pointers:

1. Scaning from left and right to clear out all prepending and tailing spaces;
2. Aligning words to the left and at meantime get rid of extra spaces between words. No concern on overwriting at all;
3. Reversing the whole string from 0 to the new end we get at step 2;
4. Now we have a string from 0 to "new end" that has been trimed on both sides and the extra spaces are removed. Simply loop
through this string and reverse every word;
5. Resize the string to "new end". This is done by string:resize() in C++ and assign 0 at the "new end" for C;

You can tell we have a linear solution here and probably OK for an interview scenario. But it scans the string too many times! We should
consider merging some steps together. we still use two pointers: one for scanning the old string and one for assigning char on the new string.

1. Scanning the string from left and stop only if current char is not a space. Then left-align the word we have found and reverse it in place.
Now we have to consider adding a space after this word. In order to avoid edge case and avoid extra procedure to detect the end of the new string,
we defer this action to the next iteration only if we find a new word (current pointer on old string has not reached the end) and pointer for the new
string is not zero, which indicates there was a word procssed already.
2. Resizing the string to the new end;
3. Revsersing the entire new string;

This solution only loops the string twice in less than 10 lines of code.
*/
class SolutionReverseWordsInString {
public:
	void reverseWords(string &s) {
		int len = (int)s.size(), i = 0, k = 0, m = 0;
		while (i < len) {
			while (i < len && ' ' == s[i]) ++i;
			if (i < len && k > 0) s[k++] = ' ';
			for (m = k; i < len && ' ' != s[i]; ++k, ++i) s[k] = s[i];
			std::reverse(s.begin() + m, s.begin() + k);
		}
		s.resize(k);
		std::reverse(s.begin(), s.end());
	}
	void reverseWords1(string &s) {
		int len = (int)s.size(), i = 0, j = len - 1, k = 0;
		while (i < len && ' ' == s[i]) ++i;
		while (j > i && ' ' == s[j]) --j;
		for (int m = i; m <= j; ++m) {
			if (k > 0 && ' ' == s[k - 1] && ' ' == s[m]) continue;
			s[k++] = s[m];
		}
		std::reverse(s.begin(), s.begin() + k);
		i = 0;
		while (i < k) {
			j = i;
			while (j < k && ' ' != s[j]) ++j;
			if (j <= k) std::reverse(s.begin() + i, s.begin() + j);
			i = j + 1;
		}
		s.resize(k);
	}
};
void TestReverseWordsInString() {
	SolutionReverseWordsInString so;
	string s1 = "the sky is blue";
	so.reverseWords(s1);
	assert("blue is sky the" == s1);

	s1 = " the sky is blue    ";
	so.reverseWords(s1);
	assert("blue is sky the" == s1);

	s1 = " the sky is   blue    ";
	so.reverseWords(s1);
	assert("blue is sky the" == s1);

	s1 = " the   sky   is   blue    ";
	so.reverseWords(s1);
	assert("blue is sky the" == s1);

	s1 = "";
	so.reverseWords(s1);
	assert("" == s1);

	s1 = "   ";
	so.reverseWords(s1);
	assert("" == s1);

	s1 = " a  ";
	so.reverseWords(s1);
	assert("a" == s1);

	s1 = " ab c  defg higk l  ";
	so.reverseWords(s1);
	assert("l higk defg c ab" == s1);

	s1 = "a  b c  de fg higk l  ";
	so.reverseWords(s1);
	assert("l higk fg de c b a" == s1);

	s1 = "abcdef c  de fg higk l";
	so.reverseWords(s1);
	assert("l higk fg de c abcdef" == s1);
}