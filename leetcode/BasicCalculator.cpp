#include <ctype.h>
#include <string>
#include <stack>
#include <functional>

using namespace std;

//https://leetcode.com/problems/basic-calculator/
/*
224. Basic Calculator

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

Example 1:

Input: "1 + 1"

Output: 2

Example 2:

Input: " 2-1 + 2 "

Output: 3

Example 3:

Input: "(1+(4+5+2)-3)+(6+8)"

Output: 23

Note:

- You may assume that the given expression is always valid.
- Do not use the eval built-in library function.

Observations:

Looks like a stack problem for me. Shunting-yard algorithm is so famous. However, since this is simplified version,
no need to follow that algorithm at all.

That has been said, my first attempt does look like shunting-yard a lot. Two stacks are used.
One for operators ('+', '-', '('), the other for operands.

Calculation will be done on the way scanning the string and intermediate results are pushed back to
the stack for operands. In terms of operator precedence, such as 1 - (3 - 2) and order, such as 1 - 2 + 1, a greedy
approach is taken. That is: calculate as early as possible. So, the calculation is done whenever a number is catched or
a ')' is met.

At the end, if there is operators/operands on the stacks, empty them through calculation, given the fact that input string
is always valid.

Actually, this is still slow comparing with other smarter approach, which doesn't need stack at all since only +, - and ()
are supported. That's a totally different alogirhtm built for this problem only.
*/
class SolutionBasicCalculator {
public:
	int calculate(string s) {
		stack<int> operands;
		stack<char> operators;
		int len = (int)s.length(), i = -1, j = 0, opt0 = 0, opt1 = 0;
		function<void()> cal = [&]() -> void {
			if (false == operators.empty() && '(' != operators.top() && 1 < operands.size()) {
				opt0 = operands.top(), operands.pop(), opt1 = operands.top(), operands.pop();
				operands.push('+' == operators.top() ? opt1 + opt0 : opt1 - opt0);
				operators.pop();
			}
		};
		while (++i < len) {
			switch (s[i]) {
			case ' ':
				break;
			case '+':
			case '-':
			case '(':
				operators.push(s[i]);
				break;
			case ')':
				operators.pop();
				cal();
				break;
			default:
				j = i;
				while (true == isdigit(s[i])) ++i;
				operands.push(std::stoi(s.substr(j, i-- - j)));
				cal();
			}
		}
		while (false == operators.empty()) cal();
		return operands.top();
	}
};
/*
Test cases:

"1 + 1"
" 2-1 + 2 "
"(1+(4+5+2)-3)+(6+8)"
"(1) +((2 - 3) + 3) - ((1+(2)))"
"(1 - (4+5+2) - (1+2))-10"

Outputs:

2
3
23
0
-23
*/