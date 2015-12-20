#include <cassert>
#include <algorithm>
#include <iostream>

using namespace std;

/*
Implement a function void reverse(char* str) in C or C++ which reverses a null-terminated
string.

This is a classic old school task you should expect to be able to write on a whiteboard...
*/
void reverseString(char *pstr)
{
	assert(NULL != pstr);
	char *p = pstr;
	char t;
	while (NULL != *p++);
	p -= 2;
	while (pstr < p)
	{
		t = *pstr;
		*pstr = *p;
		*p = t;
		--p;
		++pstr;
	}
	return;
}
void testReverseString()
{
	char s1[] = "abcd";
	reverseString(s1);
	cout << "Expect dcba:" << s1 << endl;

	char s2[] = "abc";
	reverseString(s2);
	cout << "Expect cba:" << s2 << endl;

	char s3[] = "a";
	reverseString(s3);
	cout << "Expect a:" << s3 << endl;

	char s4[] = "";
	reverseString(s4);
	cout << "Expect :" << s4 << endl;
}