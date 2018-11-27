#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

//https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
/*
Sherlock and the Valid String

Sherlock considers a string to be valid if all characters of the string appear the same number of times. It is also valid if he can remove just 1 character at 1 index in the string,
and the remaining characters will occur the same number of times. Given a string s, determine if it is valid. If so, return YES, otherwise return NO.

For example, if s = abc, it is a valid string because frequencies are {a: 1, b: 1, c: 1}. So is s = abcc because we can remove one c and have 1 of each character in the remaining string.
If s = abccc however, the string is not valid as we can only remove 1 occurrence of c. That would leave character frequencies of {a: 1, b: 1, c: 2}.

Function Description

Complete the isValid function in the editor below. It should return either the string YES or the string NO.

isValid has the following parameter(s):

s: a string

Input Format

A single string s.

Constraints

- 1 <= |s| <= 10^5
- Each character s[i] in ascii [a - z]

Output Format

Print YES if string  is valid, otherwise, print NO.

Sample Input 0

aabbcd

Sample Output 0

NO
Explanation 0

Given s = "aabbcd", we would need to remove two characters, both c and d -> aabb or a and b -> abcd,
to make it valid. We are limited to removing only one character, so s is invalid.

Sample Input 1

aabbccddeefghi

Sample Output 1

NO

Explanation 1

Frequency counts for the letters are as follows:

{'a': 2, 'b': 2, 'c': 2, 'd': 2, 'e': 2, 'f': 1, 'g': 1, 'h': 1, 'i': 1}

There are two ways to make the valid string:

Remove 4 characters with a frequency of 1: {fghi}
Remove 5 characters of frequency 2: {abcde}

Neither of these is an option.

Sample Input 2

abcdefghhgfedecba

Sample Output 2

YES

Explanation 2

All characters occur twice except for e which occurs 3 times. We can delete one instance of e to have a valid string.

Observations:

Three scenarios:

1. All chars in the string have the same number of occurrence;
2. Only 1 char has a frequency that is one greater than others;
3. All chars have the same frequence except for 1 char which only shows up 1 time in the string;
*/
class SherlockAndValidString {
public:
	string isValid(string s) {
		int cnts[26] = { 0 }, maxCnt = 0, minCnt = s.length() + 1, maxNum = 0, minNum = 0;
		for (char c : s) ++cnts[c - 'a'];
		for (int i : cnts)
			if (i > 0) {
				maxCnt = std::max(maxCnt, i);
				minCnt = std::min(minCnt, i);
			}
		if (maxCnt == minCnt) return "YES";
		else if (minCnt > 1 && maxCnt - minCnt > 1) return "NO";
		for (int i = 0; i < 26; ++i) {
			if (maxCnt == cnts[i]) ++maxNum;
			else if (minCnt == cnts[i]) ++minNum;
			else if (0 != cnts[i]) return "NO";
		}
		return (1 == maxNum && 1 == maxCnt - minCnt) || 1 == minNum ? "YES" : "NO";
	}
};

int TestSherlockAndValidString()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string s;
	getline(cin, s);
	SherlockAndValidString so;
	string result = so.isValid(s);

	fout << result << "\n";

	fout.close();

	return 0;
}