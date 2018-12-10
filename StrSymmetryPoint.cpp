#include <string>
#include <iostream>

using namespace std;

/*
StrSymmetryPoint

Find a symmetry point of a string, if any.

Write a function:

int solution(string &S);

that, given a string S, returns the index (counting from 0) of a character such that the part of the string to the left of that character is a reversal of the part of the string to its right. The function should return ?1 if no such index exists.

Note: reversing an empty string (i.e. a string whose length is zero) gives an empty string.

For example, given a string:

"racecar"

the function should return 3, because the substring to the left of the character "e" at index 3 is "rac", and the one to the right is "car".

Given a string:

"x"

the function should return 0, because both substrings are empty.

Write an efficient algorithm for the following assumptions:

the length of S is within the range [0..2,000,000].

Redo after 2 years
*/
//https://app.codility.com/demo/results/trainingMJ4TE4-WCN/
int solutionStrSymmetryPoint(const string &S) {
	int len = (int)S.length(), l = 0, r = len - 1;
	if (0 == (1 & len)) return -1;
	while (l < r) if (S[l++] != S[r--]) return -1;
	return l;
}
//https://codility.com/demo/results/trainingZKG7R5-NHG/
int solutionStrSymmetryPoint1(const string &S) {
    int len = S.length();
    int l = 0, h = len - 1;
    while(l < h)
    {
        if(S[l] == S[h])
        {
            ++l;
            --h;
        }
        else
            break;
    }
    return l == h ? l : -1;
}

void testStrSymmetryPoint()
{
    cout << "Expect 3: " << solutionStrSymmetryPoint("racecar") << endl;
    cout << "Expect 0: " << solutionStrSymmetryPoint("x") << endl;
    cout << "Expect -1: " << solutionStrSymmetryPoint("abc") << endl;
    cout << "Expect -1: " << solutionStrSymmetryPoint("") << endl;
}
