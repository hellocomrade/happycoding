#include <cassert>
#include <ctype.h>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/basic-calculator-ii/
/*
227. Basic Calculator II

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces .
The integer division should truncate toward zero.

Example 1:

Input: "3+2*2"

Output: 7

Example 2:

Input: " 3/2 "

Output: 1

Example 3:

Input: " 3+5 / 2 "

Output: 5

Note:

- You may assume that the given expression is always valid.
- Do not use the eval built-in library function.

Observations:

Again, I paid the price for being stick with Shunting Yard algorithm. No RPN is generated, tried to get
immiedate results as fast as I could. But still get a pretty long function...

Stack for operators is not really necessary for this case and subtraction operation needs to be converted to
negation on current immediate calculation result and then pop '-' and push '+' instead (convert subtraction to addition).

Why this is necessary? For example: "18 + 17-25*7/3-45", if no above operation, the result of 25*7/3 will be
substracted by 45 first then substracted against (18 + 17). The '-' in the middle is lost in this context.
That explains why '-' has to be converted to '+' by negating the operand then replacing '-' with '+' on the stack.
see calculate1.

Based upon calculate1, the hypothesis is that operand stack will never has more than 3 elements, operator stack
will has no more than 2 elements. Therefore, stack might be replaced by regular variables, which will
potentially boost the performance by removing push/pop operations to none. This is actually a varation and
local optimization against stack implementation in calculate1. The stack operations are still there, just
replaced by shifting values among variables.
*/
class SolutionBasicCalculator2 {
public:
	int calculate(string s) {
		int old_opd = 0, prev_opd = 0, opd = 0, ret = 0, len = (int)s.length(), i = -1;
		char prev_opt = 0, opt = 0;
		auto cal = [](int opd1, int opd2, char opera) {
			if (1 > opera) return opd2;
			switch (opera) {
			case '+': return opd1 + opd2;
			case '-': return opd1 - opd2;
			case '*': return opd1 * opd2;
			case '/': return opd1 / opd2;
			}
			return 0;
		};
		while (++i < len) {
			if (' ' == s[i]) continue;
			else if (0 != isdigit(s[i])) opd = opd * 10 + (int)(s[i] - '0');
			else {
				if (prev_opt > 0 && ('+' == opt || '-' == opt)) prev_opd = cal(old_opd, prev_opd, prev_opt);
				else if ('*' == opt || '/' == opt || (opt > 0 && ('+' == s[i] || '-' == s[i]))) opd = cal(prev_opd, opd, opt), prev_opd = old_opd, opt = prev_opt;
				prev_opt = opt, opt = s[i], old_opd = prev_opd, prev_opd = opd, opd = 0;
				if ('-' == prev_opt) prev_opt = '+', prev_opd *= -1;
			}
		}
		return cal(old_opd, cal(prev_opd, opd, opt), prev_opt);
	}
	int calculate1(string s) {
		int len = (int)s.length(), i = -1, num = 0;
		stack<int> operands;
		stack<char> operators;
		auto higherOrder = [](char opt1, char opt2) -> bool { return ('*' == opt1 || '/' == opt1) || ('+' == opt2 || '-' == opt2); };
		auto cal = [&operands, &operators]() -> int {
			int r = operands.top(); operands.pop();
			int l = operands.top(); operands.pop();
			char opt = operators.top(); operators.pop();
			int neg = (false == operators.empty() && '-' == operators.top()) ? (operators.pop(), operators.push('+')), -1 : 1;
			switch (opt) {
			case '+': return (l + r) * neg;
			case '-': return (l - r) * neg;
			case '*': return (l * r) * neg;
			case '/': return (l / r) * neg;
			}
			return 0;
		};
		while (++i < len) {
			switch (s[i]) {
			case ' ':
				break;
			case '+': case '-': case '*': case '/':
				if (false == operators.empty() && true == higherOrder(operators.top(), s[i])) operands.push(cal());
				operators.push(s[i]);
				break;
			default:
				num = 0;
				while (i < len && 0 != isdigit(s[i])) num = num * 10 + (int)(s[i++] - '0');
				--i, operands.push(num);
			}
		}
		while (false == operators.empty()) operands.push(cal());
		return operands.top();
	}
};
void TestBasicCalculator2() {
	SolutionBasicCalculator2 so;
	assert(5 == so.calculate("3+2"));
	assert(7 == so.calculate("3+2*2"));
	assert(3 == so.calculate("1 + 2"));
	assert(1 == so.calculate(" 3/2 "));
	assert(7 == so.calculate("3*2+1"));
	assert(4 == so.calculate(" 3 -2 +3"));
	assert(-3 == so.calculate("1+2-3*2"));
	assert(-23 == so.calculate("18 + 17 - 25 * 7 / 3"));
	assert(-68 == so.calculate("18 + 17-25*7/3-45"));
}
/*
Test Cases:

"3+2*2"
" 3/2 "
" 3+5 / 2 "
" 3 -2 +3"
" 4/7*2 +  1 "
"1 + 2 - 3 * 2"
"18 + 17-25*7/3"
"18 + 17-25*7/3-45+12/6-7+8+4/106*2 + 3 * 7 /7 "

Outputs:

7
1
5
4
1
-3
-23
-62
*/