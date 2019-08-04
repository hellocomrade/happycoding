#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/remove-invalid-parentheses/
/*
301. Remove Invalid Parentheses

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"

Output: ["()()()", "(())()"]

Example 2:

Input: "(a)())()"

Output: ["(a)()()", "(a())()"]

Example 3:

Input: ")("

Output: [""]

Observations:

Hints:

- Since we don't know which of the brackets can possibly be removed, we try out all the options!
- We can use recursion to try out all possibilities for the given expression. For each of the brackets, we have 2 options:
  1. We keep the bracket and add it to the expression that we are building on the fly during recursion.
  2. OR, we can discard the bracket and move on.
- The one thing all these valid expressions have in common is that they will all be of the same length i.e.
  as compared to the original expression, all of these expressions will have the same number of characters removed.
  Can we somehow find the number of misplaced parentheses and use it in our solution?
- For every left parenthesis, we should have a corresponding right parenthesis. We can make use of two counters
  which keep track of misplaced left and right parenthesis and in one iteration we can find out these two values.
  0 1 2 3 4 5 6 7
  ( ) ) ) ( ( ( )
  i = 0, left = 1, right = 0
  i = 1, left = 0, right = 0
  i = 2, left = 0, right = 1
  i = 3, left = 0, right = 2
  i = 4, left = 1, right = 2
  i = 5, left = 2, right = 2
  i = 6, left = 3, right = 2
  i = 7, left = 2, right = 2
  We have 2 misplaced left and 2 misplaced right parentheses.
- We found out that the exact number of left and right parenthesis that has to be removed to get a valid expression.
  So, e.g. in a 1000 parentheses string, if there are 2 misplaced left and 2 misplaced right parentheses,
  after we are done discarding 2 left and 2 right parentheses, we will have only one option per remaining character
  in the expression i.e. to consider them. We can't discard them.

Observations:

Without reading the hints, there is no way for me to figure out the minimum number of invalid parentheses that need to be removed!

Hint 4 reveals an algorithm to calculate misplaced parentheses. Misplaced here means extra ')' is met before any '(' that can match it.
So "))(" will consider as 2 misplaced ')' and 1 misplaced '(' coz none of them can find a match even though 2 ')' and 1 '('
sound like a match can be found.

With this info in hands, we can solve this using, of course, Back Tracing. Again, since "all possibilities" is asked, BT
is the number one option. I got TLE for the first attempt coz I ignore the fact that BT can have early termination if the
number of skipped (removed) parentheses exceeds the minimum member we got from the first step. I have to say that this won't
affect the worst case time complexity of the algoirthm, it's still O(2^N), for example "(((((", every parentheses should be removed.

https://leetcode.com/problems/remove-invalid-parentheses/solution/
*/
class SolutionRemoveInvalidParentheses {
public:
	vector<string> removeInvalidParentheses(string s) {
		size_t len = s.length(), count = 0;
		long long leftParentheseCnt = 0LL, rightParentheseCnt = 0LL;
		for (char c : s) {
			if (')' == c) {
				++rightParentheseCnt;
				if (leftParentheseCnt > 0) --leftParentheseCnt, --rightParentheseCnt;
			}
			else if ('(' == c) ++leftParentheseCnt;
		}
		count = len - leftParentheseCnt - rightParentheseCnt;
		vector<string> ans;
		vector<char> candidate(count);
		function<void(size_t, size_t, size_t, long long)> bt = [&](size_t idx_s, size_t idx_c, size_t skipped, long long cnt) -> void {
			if (0 > cnt || skipped > len - count || idx_c == count || idx_s == len) {
				if (idx_c == count && 0 == cnt) ans.push_back(string(candidate.begin(), candidate.end()));
				return;
			}
			char c = s[idx_s++];
			candidate[idx_c] = c;
			if (')' == c) bt(idx_s, idx_c + 1, skipped, cnt - 1);
			else bt(idx_s, idx_c + 1, skipped, ('(' == c ? cnt + 1 : cnt));
			if ('(' == c || ')' == c) {
				while (idx_s < len && c == s[idx_s]) ++idx_s;
				bt(idx_s, idx_c, skipped + 1, cnt);
			}
		};
		bt(0, 0, 0, 0LL);
		if (0 == ans.size()) ans.push_back("");
		return ans;
	}
};
/*
Test cases:

"()())()"
"()))((()"
"(a)())()"
"ab"
""
"("
")("
")(a"
"()"
"b()"
"(c)"
"()d"
"()))(("
"(t))b)(s("
"((())()))(())((())"
"a((()a)(a)))a(()a)(a((a)a)"
"((()))))()()()((())()(())((()()()"
"(dg(()we))))()(bh)r()*((())()(())(((w)e(g)()"
"(()()()()()((((()))()()((())))((((())()())())))()()()()())(("

Outputs:

["(())()","()()()"]
["()()"]
["(a())()","(a)()()"]
["ab"]
[""]
[""]
[""]
["a"]
["()"]
["b()"]
["(c)"]
["()d"]
["()"]
["(tb)s","(t)bs"]
["((()()))(())(())","((())())(())(())"]
["a(((a)(a)))a(()a)a((a)a)","a(((a)(a)))a(()a)(a(a)a)","a((()a(a)))a(()a)a((a)a)","a((()a(a)))a(()a)(a(a)a)","a((()a)(a))a(()a)a((a)a)","a((()a)(a))a(()a)(a(a)a)"]
["((()))()()()(())()(())()()()","((()))()()()(())()(())(())()","((()))()()()(())()(())(()())","((()))()()()(())()(())((()))","((()))()()()((()))(())()()()","((()))()()()((()))(())(())()","((()))()()()((()))(())(()())","((()))()()()((()))(())((()))","((()))()()()((())()())()()()","((()))()()()((())()())(())()","((()))()()()((())()())(()())","((()))()()()((())()())((()))","((()))()()()((())()(()))()()","((()))()()()((())()(())())()","((()))()()()((())()(())()())","((()))()()()((())()(())(()))"]
["(dg((we)))()(bh)r()*(())()(())(w)e(g)()","(dg((we)))()(bh)r()*(())()(())((w)eg)()","(dg((we)))()(bh)r()*(())()(())((w)e(g))","(dg((we)))()(bh)r()*(())()(())(((w)eg))","(dg((we)))()(bh)r()*((()))(())(w)e(g)()","(dg((we)))()(bh)r()*((()))(())((w)eg)()","(dg((we)))()(bh)r()*((()))(())((w)e(g))","(dg((we)))()(bh)r()*((()))(())(((w)eg))","(dg((we)))()(bh)r()*((())()())(w)e(g)()","(dg((we)))()(bh)r()*((())()())((w)eg)()","(dg((we)))()(bh)r()*((())()())((w)e(g))","(dg((we)))()(bh)r()*((())()())(((w)eg))","(dg((we)))()(bh)r()*((())()(())w)e(g)()","(dg((we)))()(bh)r()*((())()(())(w)eg)()","(dg((we)))()(bh)r()*((())()(())(w)e(g))","(dg((we)))()(bh)r()*((())()(())((w)eg))","(dg(()we))()(bh)r()*(())()(())(w)e(g)()","(dg(()we))()(bh)r()*(())()(())((w)eg)()","(dg(()we))()(bh)r()*(())()(())((w)e(g))","(dg(()we))()(bh)r()*(())()(())(((w)eg))","(dg(()we))()(bh)r()*((()))(())(w)e(g)()","(dg(()we))()(bh)r()*((()))(())((w)eg)()","(dg(()we))()(bh)r()*((()))(())((w)e(g))","(dg(()we))()(bh)r()*((()))(())((...
["(()()()()()((((()))()()((())))((((())()())())))()()()()())"]
*/