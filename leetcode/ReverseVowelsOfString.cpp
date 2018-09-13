#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/reverse-vowels-of-a-string
/*
345. Reverse Vowels of a String

Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:

Input: "hello"

Output: "holle"

Example 2:

Input: "leetcode"

Output: "leotcede"

Note:
The vowels does not include the letter "y".

Observations:

Two pointers shall be sufficient. One runs from beginning of the string, the other runs from the end. Similiar approach
for quick sort.

The only catch is: string may contain both lowercase and uppercase letters.
*/
class SolutionReverseVowelsOfString {
public:
	string reverseVowels(string s) {
		int l = 0, len = (int)s.length(), r = len - 1;
		auto isVowels = [](const char c) {
			switch (c) {
			case 'A':case 'a':case 'E':case 'e':case 'I':case 'i':case 'O':case 'o':case 'U':case 'u':
				return true;
			}
			return false;
		};
		while (l < r) {
			while (l < r && false == isVowels(s[l])) ++l;
			while (r > l && false == isVowels(s[r])) --r;
			if (l < r) std::swap(s[l++], s[r--]);
		}
		return s;
	}
};
/*
Test cases:

"hello"
"leetcode"
"aeiou"
"hEllo"
"AajdcEeee"

Outputs:

"holle"
"leotcede"
"uoiea"
"hollE"
"eejdceEaA"
*/