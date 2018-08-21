#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/generate-parentheses/
/*
22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
"((()))",
"(()())",
"(())()",
"()(())",
"()()()"
]

Observations:
Looks pretty close to printing combinations with one restriction that parentheses must match in pairs. Try backtracing?

Well, since we know we will have same numbers of left and right parentheses, the only question is to make sure the combination forms
a valid parentheses string.

We could do that by getting every possible combination and then test if it's well-formed. But if you take a close look, we could
actually terminate illed-formed ones if and only if the remaining right parentheses is less than left parentheses, which means there is
no way to form a valid parentheses chain. On the other hand, a valid one can be checked by the fact both remaining left and right parentheses
are zero.

So, backtracing with a newly created string to host the temp result.

***Update on 8/21/2018***

Back tracing is definitely the way to go since it asks to return all valid combinations. The trick of this question comparing
with other traditional BT, such as permutation and combination is that one can not construct a legit "for loop" during recursion.
Furthremore, if one ever consider using a stack to track valid parentheses, which is natuarl reaction for handling parenthese match,
the outcome won't be the optimal. The stack can be used though, but it's not necessary.

The theory is: at any moment of building process, if right parentheses are more than left ones, no valid combination can be formed.

For example:

(()))

())

In the above two cases, adding more right parentheses will definitely fail to form any valid combination!

Therefore, given two counters for left and right parentheses, the options are:

1. If left parenthese is still available, try to add one;
2. If the number of left parentheses are more than right ones, try to add a right one here;

Notes, the above two conditions will result in the assignment on the same index of memo string. Either '(' or ')'
will be written. Actually, on each index of string memo, '(' and ')' are only two possibilities.
*/
class SolutionGenerateParentheses {
private:
	void _aux(vector<string>& ans, int l, int r, string& str, int idx) {
		if (r < l)return;
		if (0 == r && 0 == l) {
			ans.emplace_back(str);
			return;
		}
		if (idx < (int)str.length()) {
			str[idx] = '(';
			_aux(ans, l - 1, r, str, idx + 1);
			str[idx] = ')';
			_aux(ans, l, r - 1, str, idx + 1);
		}
	}
public:
	vector<string> generateParenthesis(int n) {
		vector<string> ans;
		if (1 > n) return ans;
		string memo(n * 2, 0);
		auto bt = [&](int left, int right, auto& fun) {
			if (n == right) {
				ans.emplace_back(string(memo.begin(), memo.end()));
				return;
			}
			if (left < n) {
				memo[left + right] = '(';
				fun(left + 1, right, fun);
			}
			if (left > right) {
				memo[left + right] = ')';
				fun(left, right + 1, fun);
			}
		};
		bt(0, 0, bt);
		return ans;
	}
	vector<string> generateParenthesis0(int n) {
		vector<string> ans;
		if (1 > n) return ans;
		string memo(n * 2, 0);
		auto bt = [&](int left, int right, auto& fun) {
			if (0 == right) {
				ans.emplace_back(string(memo.begin(), memo.end()));
				return;
			}
			if (left > 0) {
				memo[n * 2 - left - right] = '(';
				fun(left - 1, right, fun);
			}
			if (left < right && right > 0) {
				memo[n * 2 - left - right] = ')';
				fun(left, right - 1, fun);
			}
		};
		bt(n, n, bt);
		return ans;
	}
	vector<string> generateParenthesis1(int n) {
		vector<string> ans;
		string str(n * 2, ' ');
		_aux(ans, n, n, str, 0);
		return ans;
	}
};