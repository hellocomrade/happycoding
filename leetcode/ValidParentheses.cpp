#include <stack>
#include <string>

using namespace std;

//https://leetcode.com/problems/valid-parentheses/
/*
20. Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/
class SolutionValidParentheses {
public:
	//Shorter
	bool isValid(string s) {
		int len = (int)s.length();
		stack<char> stk;
		for (char c : s) {
			switch (c) {
			case '[': stk.push(']');break;
			case '(': stk.push(')');break;
			case '{': stk.push('}');break;
			default:
				if (true == stk.empty() || c != stk.top())return false;
				else stk.pop();
				break;
			}
		}
		return stk.empty();
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