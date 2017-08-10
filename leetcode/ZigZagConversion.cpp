#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/zigzag-conversion/
/*
6. ZigZag Conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

Observations:
See the thumb down this one got so far? Leetcode could offer more detailed explanation on this zig-zag pattern!

- If numRows < 0, numRows is considered 1;
- If numRows is 1, originaly string shall be returned;
- If numRows is 2, the shorter column (zag) is 0, therefore, the string is 2 characters a column. For example:
["abcd", numRows = 2]:
ac
bd
- If numRows is larger than 2, th shorter column is numRows - 1 tall and the character shall be put in from bottom to top
of this shorter columns. For example:
["abcdefghijklmnopqrstu", numRows = 5]:
a				i				q
b		h		j		p		r
c		g		k		o		s
d		f		l		n		t
e				m				u

This is so-called "Zig-Zag". Leetcode's example failed to illustrate the facts...

Observation:
This will be a O(N) time algorithm. If figure out the pattern on index is too much, we could simply build this zigzag string then
return the level traversal accordingly.

Or, spending some time on the pattern. Therefore you will have a O(1) space solution. Well, with couple variables as helpers.

- The longer column has numRows letters, the shorter one has (numRows - 2). That explains the logic on why shorter column (zig-zag pattern)
doesn't exist when numRows == 2;
- The first letter on each row is the first numRows letter in the string;
- On index i = 0 or (numRows - 1), offset from one column to the next is addition of column 1 and column 2, which is:
numRows + numRows - 2 = 2 * (numRows - 1);
- On index in range [1, numRows - 2], such offsets come in pair. They switch between:
2 * (numRows - i - 1)
and
numRows + numRows - 2 - (2 * (numRows - i - 1)) = 2 * i

In the case above, for index = 0 and 4, offset is 8
in between, we have:
(6, 2)
(4, 4)
(2, 6)

See the pattern there?
*/
class SolutionZigZagConversion {
public:
	string convert(string s, int numRows) {
		numRows = std::max(1, numRows);
		size_t col1 = numRows, col2 = std::max(0, numRows - 2), len = s.length(), idx = 0, offset1 = 0, offset2 = 0, k = 0;
		if (1 == numRows || 0 == len)return s;
		string ans;
		for (int i = 0; i < numRows; ++i) {
			idx = i, k = 1;
			offset1 = 2 * (numRows - i - 1);
			offset2 = 2 * i;
			while (idx < len) {
				ans.append(1, s[idx]);
				idx += (1 & k++) ? ((offset1 > 0) ? offset1 : offset2) : ((offset2 > 0) ? offset2 : offset1);
			}
		}
		return ans;
	}
};