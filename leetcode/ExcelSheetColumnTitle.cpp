#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/excel-sheet-column-title/
/*
168. Excel Sheet Column Title

Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

1 -> A
2 -> B
3 -> C
...
26 -> Z
27 -> AA
28 -> AB

Observations:

Convert from 10-based number to 26-based number, note: this 26-based number system has range in [1, 26], no zero!

That caused my first attempt failed on handling 26, which is supposed to be 'Z'. Without (n - 1) / 26 when removing lower bits,
my answer was 'AZ' coz 26 ('Z') is a valid dividend.
*/
class SolutionExcelSheetColumnTitle {
public:
	string convertToTitle(int n) {
		stringstream ss;
		while (n > 0) {
			ss << (char)('A' + (n - 1) % 26);
			n = (n - 1) / 26;
		}
		string ans = ss.str();
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
};
/*
Test cases:

26
1
256
1234
33
22
789
898
1234567

Outputs:

"Z"
"A"
"IV"
"AUL"
"AG"
"V"
"ADI"
"AHN"
"BRFGI"
*/