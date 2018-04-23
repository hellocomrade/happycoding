#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/ambiguous-coordinates
/*
816. Ambiguous Coordinates

We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)".  Then, we removed all commas, decimal points, and spaces, and ended up with the string S.  Return a list of strings representing all possibilities for what our original coordinates could have been.

Our original representation never had extraneous zeroes, so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other number that can be represented with less digits.  Also, a decimal point within a number never occurs without at least one digit occuring before it, so we never started with numbers like ".1".

The final answer list can be returned in any order.  Also note that all coordinates in the final answer have exactly one space between them (occurring after the comma.)

Example 1:

Input: "(123)"

Output: ["(1, 23)", "(12, 3)", "(1.2, 3)", "(1, 2.3)"]

Example 2:

Input: "(00011)"

Output:  ["(0.001, 1)", "(0, 0.011)"]

Explanation:

0.0, 00, 0001 or 00.01 are not allowed.

Example 3:

Input: "(0123)"

Output: ["(0, 123)", "(0, 12.3)", "(0, 1.23)", "(0.1, 23)", "(0.1, 2.3)", "(0.12, 3)"]

Example 4:

Input: "(100)"

Output: [(10, 0)]

Explanation:

1.0 is not allowed.

Note:

- 4 <= S.length <= 12.
- S[0] = "(", S[S.length - 1] = ")", and the other elements in S are digits.

Observations:

This is a weird one, especially for C++, which always has concern on extra copy construction. I had to make sure using rvalue
as much as I can so the move construction can be triggered on string and vector.

It could have a much better code flow and logic if we do this using Java and Python:

https://leetcode.com/problems/ambiguous-coordinates/solution/

Both of them use temp variable which could be a luxury for C++ handing string, imho.

The thoughts:

General idea is to put period between digits with rules:

1. If there is any tailing zero, no period allowed at any position;

2. If there is any tailing zero, the only possible coordinate is either the full string if there is no leading zero,
in other words, if both leading and trailing zeros exist, no valid coordinate;

3. A leading zero will lead to only one possible coordinate, which is period after the first zero, as long as there is
no tailing zero.

4. If there is more than one leading zeros, the period can only be posted after the first zero. For example
given "001", 0.01 makes sense, but 00.1 doesn't;

The above logic can be implemented easier if temp string variable is affordable...
*/
class SolutionAmbiguousCoordinates {
private:
	vector<string> aux(const string &str, int start, int end) {
		vector<string> ans;
		int leading0 = 0, i = start;
		while (i <= end && '0' == str[i]) ++i, ++leading0;
		if (leading0 > 0) {
			if (end == start || ('0' != str[end] && end - start + 1 > leading0))
				ans.push_back(str.substr(start, 1) + (end == start ? "" : ".") + str.substr(start + 1, end - start));
		}
		else {
			if ('0' != str[end])
				for (int n = 1; n <= end - start + 1; ++n)
					ans.push_back(str.substr(start, n) + (end - start + 1 == n || end == start ? "" : ".") + str.substr(start + n, end - start - n + 1));
			else
				ans.push_back(str.substr(start, end - start + 1));
		}
		return ans;
	}
public:
	vector<string> ambiguousCoordinates(string S) {
		int len = S.length();
		vector<string> ans;
		for (int i = 1; i < len - 2; ++i) {
			vector<string> v1 = this->aux(S, 1, i);
			vector<string> v2 = this->aux(S, i + 1, len - 2);
			if (0 < v1.size() && 0 < v2.size()) {
				for (auto& s1 : v1)
					for (auto& s2 : v2)
						ans.push_back('(' + s1 + ", " + s2 + ')');
			}
		}
		return ans;
	}
};
/*
Test cases:

"(123)"
"(01002340540)"
"(00)"
"(010)"

Outputs:

["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
["(0, 1002340540)","(0.1002, 340540)","(0.10023, 40540)","(0.10023405, 40)","(0.100234054, 0)"]
["(0, 0)"]
["(0, 10)","(0.1, 0)"]
*/