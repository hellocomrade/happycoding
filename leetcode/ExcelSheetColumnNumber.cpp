#include <string>

using namespace std;

//https://leetcode.com/problems/excel-sheet-column-number
/*
171. Excel Sheet Column Number

Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28

Observations:

It's a 26-based number system. It asks the conversion from base-26 to base-10

Since there is no zero in this 26-based system, we have to do (s[i] - 'A' + 1)
*/
class SolutionExcelSheetColumnNumber {
public:
	//Start from left, aka most significant bit
	int titleToNumber(string s) {
		int len = (int)s.length(), ans = 0;
		for (int i = 0; i < len; ++i)
			ans = ans * 26 + (s[i] - 'A' + 1);
		return ans;
	}
	//Start from right, aka lest significant bit
	int titleToNumber1(string s) {
		int len = (int)s.length(), ans = 0;
		for (int i = 0, base = 1; i < len; ++i, base *= 26)
			ans += base * (s[len - i - 1] - 'A' + 1);
		return ans;
	}
};
/*
Test cases:

"T"
"BB"
"ZZ"
"AAA"
"AAZ"
"ABA"
"BBA"
"ZBCAC"

Outputs:

20
54
702
703
728
729
1405
11918585
*/