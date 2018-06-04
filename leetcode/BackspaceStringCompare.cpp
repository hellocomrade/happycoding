#include <string>
#include <stack>
using namespace std;

//https://leetcode.com/problems/backspace-string-compare
/*
844. Backspace String Compare

Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"

Output: true

Explanation: Both S and T become "ac".

Example 2:

Input: S = "ab##", T = "c#d#"

Output: true

Explanation: Both S and T become "".

Example 3:

Input: S = "a##c", T = "#a#c"

Output: true

Explanation: Both S and T become "c".

Example 4:

Input: S = "a#c", T = "b"

Output: false

Explanation: S becomes "c" while T becomes "b".

Note:

- 1 <= S.length <= 200
- 1 <= T.length <= 200
- S and T only contain lowercase letters and '#' characters.

Observations:

If you realize this is like stack operation, you can figure out the code in 5 minutes. Or, you can tackle it in the hard way by
using linear scanning backward on 2 given strings:

Counting the number of '#'s and skip non '#' characters by cancelling out existing '#'s if the member of '#'s is greater than zero.
After the loops end on both S and T, the count on '#'s shall be zero and i, j could end up like:

- i > -1 && j > -1:
In this situation, if S[i] != T[j], we know false can be returned immediately;

- Either i or j reaches -1 but not both, we know there is a mismatch and a char is compared with nothing, return false;

- None of above applied, then --i, --j;

The condition of outter loop is (i > -1 || j > -1). If it ends, we know two strings match each other.

The difficulty of this approach is to cover all edge cases and know when to return false and when to continue...
*/
class SolutionBackspaceStringCompare {
public:
	//O(1) space, scanning strings backward
	bool backspaceCompare(string S, string T) {
		int i = S.size() - 1, j = T.size() - 1, m = 0;
		while (i > -1 || j > -1) {
			while (i > -1 && ('#' == S[i] || m > 0)) m = ('#' == S[i--]) ? m + 1 : m - 1;
			while (j > -1 && ('#' == T[j] || m > 0)) m = ('#' == T[j--]) ? m + 1 : m - 1;
			if ((i > -1 && j > -1 && S[i] != T[j]) || ((i > -1) ^ (j > -1))) return false;
			--i, --j;
		}
		return true;
	}
	//Using stack
	bool backspaceCompare1(string S, string T) {
		stack<char> stk1, stk2;
		for (char c : S) {
			if ('#' != c) stk1.push(c);
			else if (false == stk1.empty()) stk1.pop();
		}
		for (char c : T) {
			if ('#' != c) stk2.push(c);
			else if (false == stk2.empty()) stk2.pop();
		}
		while (false == stk1.empty() && false == stk2.empty()) {
			if (stk1.top() != stk2.top()) return false;
			stk1.pop(), stk2.pop();
		}
		return true == stk1.empty() && true == stk2.empty();
	}
};
/*
Test cases:

"ab#c"
"ad#c"
"ab##"
"c#d#"
"a##c"
"#a#c"
"a#c"
"b"
"##acb#a"
"acd#a"
"bxj##tw"
"bxo#j##tw"
"abc"
"dbc"
"xywrrmp"
"xywrrmu#p"
"bxj##tw"
"bxj###tw"

Outputs:

true
true
true
false
true
true
false
true
false
*/