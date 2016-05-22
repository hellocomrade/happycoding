#include <string>
using namespace std;

//http://www.lintcode.com/en/problem/compare-strings/
/*
Compare Strings

Compare two strings A and B, determine whether A contains all of the characters in B.

The characters in string A and B are all Upper Case letters.

Notice

The characters of B in A are not necessary continuous or ordered.

Example
For A = "ABCD", B = "ACD", return true.

For A = "ABCD", B = "AABC", return false.
*/
class SolutionCompareStrings {
public:
	/**
	* @param A: A string includes Upper Case letters
	* @param B: A string includes Upper Case letter
	* @return:  if string A contains all of the characters in B return true
	*           else return false
	*/
	bool compareStrings(string A, string B) {
		int map[26] = { 0 };
		for (char c : A)
			++map[c - 'A'];
		for (char c : B)
			if (0 == map[c - 'A']--)
				return false;
		return true;
	}
};