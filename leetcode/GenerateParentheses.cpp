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
*/
class SolutionGenerateParentheses {
private:
	void _aux(vector<string>& ans, int l, int r, string& str, int idx) {
		if (r < l)return;
		if (0 == r && 0 == l) {
			ans.emplace_back(str);
			return;
		}
		if (idx < str.length()) {
			str[idx] = '(';
			_aux(ans, l - 1, r, str, idx + 1);
			str[idx] = ')';
			_aux(ans, l, r - 1, str, idx + 1);
		}
	}
public:
	vector<string> generateParenthesis(int n) {
		vector<string> ans;
		string str(n * 2, ' ');
		_aux(ans, n, n, str, 0);
		return ans;
	}
};