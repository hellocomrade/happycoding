#include <stack>
#include <string>

using namespace std;

//https://leetcode.com/problems/valid-parentheses/
/*
20. Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

Observations:

Stack is the most intuitive thought. If only one type of parenthese pair is given, a counter is enough. However,
multiple parenthese types here, has to use a stack. See isValid.

This will take O(N) time and O(N) space. It's possible to reduce the space complexity to O(1) by reusing
the input argument. By maintaining a int variable as the pointer to the top of the "stack", the given string
can be turned into a stack. This "stack" is built upon visited elements only therefore will not interference
with string iteration. See isValid0.
*/
class SolutionValidParentheses {
public:
	//Shorter
	bool isValid(string s) {
		int len = (int)s.length();
		stack<char> stk;
		for (char c : s) {
			switch (c) {
			case '[': stk.push(']'); break;
			case '(': stk.push(')'); break;
			case '{': stk.push('}'); break;
			default:
				if (true == stk.empty() || c != stk.top()) return false;
				else stk.pop();
				break;
			}
		}
		return stk.empty();
	}
	//No Stack explicitly, using input string as the stack
	bool isValid0(string s) {
		int stkTop = -1, len = (int)s.length();
		for (int i = 0; i < len; ++i) {
			switch (s[i]) {
			case '(': s[++stkTop] = ')'; break;
			case '{': s[++stkTop] = '}'; break;
			case '[': s[++stkTop] = ']'; break;
			default: if (0 > stkTop || s[i] != s[stkTop--]) return false; break;
			}
		}
		return -1 == stkTop;
	}
	//Naive
	bool isValid1(string s) {
		int len = (int)s.length();
		stack<char> stk;
		for (int i = 0; i < len; ++i) {
			if (false == stk.empty()) {
				switch (stk.top()) {
				case '[':
					if (']' == s[i])stk.pop();
					else stk.push(s[i]);
					break;
				case '(':
					if (')' == s[i])stk.pop();
					else stk.push(s[i]);
					break;
				case '{':
					if ('}' == s[i])stk.pop();
					else stk.push(s[i]);
					break;
				default:
					break;
				}
			}
			else stk.push(s[i]);
		}
		return stk.empty();
	}
};
/*
Test cases:

"()"
"()[]{}"
"(]"
"([)]"
"{[]}"
"()]["
""

Outputs:

true
true
false
false
true
false
true
*/