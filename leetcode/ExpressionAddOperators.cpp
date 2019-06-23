#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

//https://leetcode.com/problems/expression-add-operators/
/*
282. Expression Add Operators

Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators
(not unary) +, -, or * between the digits so they evaluate to the target value.

Example 1:

Input: num = "123", target = 6

Output: ["1+2+3", "1*2*3"]

Example 2:

Input: num = "232", target = 8

Output: ["2*3+2", "2+3*2"]

Example 3:

Input: num = "105", target = 5

Output: ["1*0+5","10-5"]

Example 4:

Input: num = "00", target = 0

Output: ["0+0", "0-0", "0*0"]

Example 5:

Input: num = "3456237490", target = 9191

Output: []

Observations:

It says returning all possibilities so Back Tracing it is. The catches are:

1. Operand could be more than one digit. For example, given "105", it can be split to [1, 0 ,5] or [10, 5];
2. Some splits might not be valid. Still use example of "105", ["1", "05"] is not valid. "05" is not a valid number;

Given string with length N, operands can be inserted between any two digts or two groups of digits.
If considering no operator between two digits as an operator, along with '+', '-' and '*' three operators, there are
total 4 operators. So total N^4 possibilities. N^4 is the time complexity of this back tracing.

The optimizations that might be necessary:

1. Eliminate the use of temp string. This is extremely important for certain programming languages, including C++.
   stringstream can be used as a String Buffer. stringstream doesn't have a function to clear the content. So,
   have to record the position by tellp() then reset position by seekp();

2. Can back tracing be early terminated? If we could know certain splits won't reach target anyway, that recursion can
   be stopped immediately. Well, however, this is not possible without evaluating the last possible operands and operators;

3. The evaluation of the expression can obviously be done when a possible expression is ready. It may take N time to complete.
   Is it possible to calcuate the value of the expression while it's building?

addOperators1 barely passed the time limit requirement. It applies optimization 1 only. The expression evaluation algirhtm
is taken from leetcode 227 (Basic Calculator II). That algorithm itself is pretty solid and takes O(N) time and constant space without using
stack. However, since the expression evaluation is done separately for every 4^N expression. This leads to a NX4^N algorithm,
which is slower...

addOperators embedded expression evaluation in the recursion. So once the whole expression is ready, the result is done as well.
Huge performance boost using leetcode test cases! That has been said, the algorithm is actually still NXN^4 coz pushing
a new substring of stringstream still takes O(N) time to copy every character...

Edge case:

1. Integer overflow on calculation:
   "2147483648"
   -2147483648

   2147483648 is an overflow on 32 bits integer. When comparing with -2147483648, the overflowed value from 2147483648
   is -2147483648. So int(2147483648) == int(-2147483648). I am not 100% sure, but my guess is the overflowed result
   is undefined so why 2147483648 overflows to -2147483648 is not obvious to tell unless looking into the detail of OS
   implementation.

   Anyway, using long long instead of int during calculation will fix the problem. Why not using long? See below.

2. Long on Linux 64bits vs Windows 64bits. Long on Linux 64bits is 8 bytes, good enough to cover 4 bytes integer overflow.
   On Windows, long is only 4 bytes... Therefore, stol() is fine for Linux but will fail on Windows. So, use stoll() is
   the safer choice.
*/
class SolutionExpressionAddOperators {
public:
	vector<string> addOperators(string num, int target) {
		int len = (int)num.length();
		char operators[3] = { '+', '-', '*' };
		stringstream memo;
		vector<string> ans;
		function<void(int, long long, long long, char)> bt = [&](int idx, long long prev, long long cur, char operator_) -> void {
			long long prev_val = prev, cur_val = cur;
			std::streampos pos_opt, pos_opd = memo.tellp();
			string str;
			for (int i = 1; i <= len - idx; memo.seekp(pos_opd, std::ios_base::beg), prev_val = prev, cur_val = cur, ++i) {
				if ('0' == num[idx] && 1 < i) break;
				str = num.substr(idx, i);
				memo << str;
				if ('+' == operator_) cur_val += prev_val, prev_val = stoll(str);
				else if ('-' == operator_) cur_val += prev_val, prev_val = -1L * stoll(str);
				else prev_val *= stoll(str);
				if (idx + i < len)
					for (int j = 0, k = 0; j < 3; memo.seekp(pos_opt, std::ios_base::beg), ++j) {
						pos_opt = memo.tellp(), memo << operators[j];
						bt(idx + i, prev_val, cur_val, operators[j]);
					}
				else
					if (target == cur_val + prev_val) ans.push_back(memo.str().substr(0, (int)memo.tellp()));
			}
		};
		bt(0, 0, 0, '+');
		return ans;
	}
	vector<string> addOperators1(string num, int target) {
		int len = (int)num.length();
		char operators[3] = { '+', '-', '*' };
		stringstream memo;
		memo.exceptions(ios::failbit | ios::badbit);
		vector<string> ans;
		function<long(const string&)> cal = [](const string &memo) -> long {
			long ans = 0L, prev_operand = 0L, operand = 0L, i = 0L, end = (long)memo.length();
			char operator_ = '+';
			while (i < end) {
				while (i < end && 0 != std::isdigit(memo[i])) operand = operand * 10 + (int)(memo[i++] - '0');
				switch (operator_) {
				case '+': ans += prev_operand; prev_operand = operand; break;
				case '-': ans += prev_operand; prev_operand = -1 * operand; break;
				case '*': prev_operand *= operand; break;
				default: break;
				}
				if (i < end) operator_ = memo[i++], operand = 0L;
			}
			return ans + prev_operand;
		};
		function<void(int)> bt = [&](int idx) -> void {
			long pos_opt = 0, pos_opd = memo.tellp();
			for (int i = 1; i <= len - idx; memo.seekp(pos_opd, std::ios_base::beg), ++i) {
				if ('0' == num[idx] && 1 < i) break;
				memo << num.substr(idx, i);
				if (idx + i == len) {
					string str = memo.str().substr(0, (int)memo.tellp());
					if (target == cal(str)) ans.push_back(str);
				}
				else
					for (int j = 0; j < 3; memo.seekp(pos_opt, std::ios_base::beg), ++j) {
						pos_opt = memo.tellp(), memo << operators[j];
						bt(idx + i);
					}
			}
		};
		bt(0);
		return ans;
	}
};
void TestExpressionAddOperators() {
	SolutionExpressionAddOperators so;
	so.addOperators("123", 6);
	so.addOperators("105", 5);
	so.addOperators("2147483648", numeric_limits<int>::min());
}
/*
Test cases:

"123"
6
"232"
8
"105"
5
"00"
0
"123"
123
"2147483648"
-2147483648
"8999999"
-999991

Outputs:

["1+2+3","1*2*3"]
["2+3*2","2*3+2"]
["1*0+5","10-5"]
["0+0","0-0","0*0"]
["123"]
[]
["8-999999"]

*/