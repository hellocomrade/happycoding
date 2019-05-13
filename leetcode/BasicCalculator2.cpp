#include <ctype.h>
#include <string>
#include <stack>

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
*/
class SolutionBasicCalculator {
public:
	int calculate(string s) {
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