#include <stack>
#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/evaluate-reverse-polish-notation/
/*
150. Evaluate Reverse Polish Notation

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:

["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9

["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

Observations:

Classic RPN parsing using a single stack:

Scanning RPN, at index i, if meets an operand, push RPN[i] onto the stack, otherwise, pop two operands from stack and apply the arithmetic operation
based upon the current operator RPN[i].

Code could be shorten if switch/case is replaced by if/else, then we don't even need the extra function cal.
*/
class SolutionEvaluateReversePolishNotation {
private:
	int cal(int opt1, int opt2, char opertor) {
		switch (opertor) {
		case '+':
			return opt1 + opt2;
		case '-':
			return opt1 - opt2;
		case '*':
			return opt1 * opt2;
		case '/':
			return opt1 / opt2;
		default:
			break;
		}
		return 0;//shouldn't ever reach here
	}
public:
	int evalRPN(vector<string>& tokens) {
		stack<int> stk;
		int opt1, opt2;
		for (const string& token : tokens) {
			if (1 == token.length()) {
				switch (token[0]) {
				case '+':
				case '-':
				case '*':
				case '/':
					opt2 = stk.top(), stk.pop();
					opt1 = stk.top(), stk.pop();
					stk.push(this->cal(opt1, opt2, token[0]));
					continue;
				default:
					break;
				}
			}
			stk.push(stoi(token));
		}
		return stk.top();
	}
};