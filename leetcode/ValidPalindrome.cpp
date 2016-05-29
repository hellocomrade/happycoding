#include <ctype.h>
#include <string.h>

//https://leetcode.com/problems/valid-palindrome/
/*
125. Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.

Observation:
Both uppercase/lowercase chars plus numbers 0 - 9 are valid. isalnum is handy.

"" is valid
"0a" is not valid
".a" is valid

Some crazy test case like "\"Sue,\" Tom smiles\n\"Selim smote us.\""
*/
bool isPalindrome(char* s) {
	int len = strlen(s);
	if (0 == len)return true;
	char *f = s;
	char *t = s + len - 1;
	//if f >= t, we are done, no invalid case found so far.
	while (f < t)
	{
		while (f < t && !isalnum(*f))++f;
		while (f < t && !isalnum(*t))--t;
		//printf("%c -- %c\n", *f, *t);
		if (tolower(*t--) != tolower(*f++))
			return false;
	}
	return true;
}