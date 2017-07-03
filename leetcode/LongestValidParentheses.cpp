#include <cassert>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/longest-valid-parentheses/
/*
32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

Observations:
Doesn't look like a DP for me. Appears can be done with one stack and one extra variable. Stack only push if a '('  is met. The value
we push onto stack depends on the position of '('. If the prior char is ')' and it happens to have a valid parentheses at ')', the value
is store in variable last and we push the value of last onto stack when we see the first '(' then reset last = 0, so all following possible
push of '(' will be 0.

Therefore, for example "()(((", only '(' with index 2 is pushed onto stack with value (last) of 2, the following '('
will be pushed with value of 0. The reason to do so is: only if the following count reach index 2, will the valid parentheses from index 0 to 1
be counted, for example "()((()))", the longest one is the whole string, when we reach "((()))", . If we have "()((())", the last
value (2) we store on stack when '(' at index 2 is met, will never be touched since there is no way to use this '(' to form any valid parentheses.

If ')' is met, depending on the status of the stack (empty or not), we either count length and store it in variable last if the stack is not empty,
or simply reset last to 0, which indicates there is no valid parentheses can be found at this location at all. So there is no way to connect previous
valid parentheses with the possible valid ones down the road because of this barrier ')'.

Since we reset last in the midde of every iteration, ans has to be examined at the beginning of each iteration, as well as after exit of the loop since
it's possible to have a valid parentheses reaches the end of the string. The value is stored in last and will not be examined on ans since the loop is done.



OK, here we go the "DP" version: I was about to give up on DP since this is really not DP for me. However, leetcode setup a pretty tough test case that
a Java with stack will get a TLE even I replaced stack with deque...
Here is how "DP" works: create a memo array with with zero. If we meet a '(' at index i, we leave 0 at memo[i], if we see a ')', check
the follow conditions:
1. if the previous char is '(', then we can count 2 at least for memo[i];
2. if the previous char is ')', say '(())', i = 3, previous index i = 2. In this case, memo[2] = 2, ')' with index i = 3 will actually be
   checked against index i - memo[i - 1] - 1 = 0. By doing so, we solve the nested parentheses;

With the above 2 steps, we count the total from '(' till matched ')', for the example '(())', we have the count from index 0 to index 3;

3. Now, we need to find out if there is a valid parentheses ends just before the '(' we checked. Say '()(())' and we are at index i = 5.
   In this case, we first get the length from i = 2 to 5. Then move the index one step backward, we check index i = 1. If the char at
   index i = 1 is ')', then we need to add the length in memo[1] onto memo[5].
   
Adding 3 steps together, we have memo[i] = 2 + memo[i - 1] + memo[i - memo[i - 1] - 2] if and only if ')' == s[i] && i - memo[i - 1] - 1 >= 0 && '(' == s[i - memo[i - 1] - 1]
Of course, if i - memo[i - 1] - 2 < 0, then no need to add it. Also, no need to check the char at index = i - memo[i - 1] - 2. Why? If it's '(',
then memo[i - memo[i - 1] - 2] == 0

In each iteration, we compare memo[i] with ans and keep the max in ans. This is a O(N) time and O(N) space algorithm. I would rather call
it a memorization algorithm instead of DP though...
*/
class SolutionLongestValidParentheses {
public:
	//A "DP" version. Store longest so far at each possible ')'
        int longestValidParentheses(string s) {
            long long len = (long long)s.length(), ans = 0;
            if(len < 2)return 0;
            vector<long long> memo(len, 0LL);
            for(int i = 1; i < len; ++i) {
                if(')' == s[i] && i - memo[i - 1] - 1 >= 0 && '(' == s[i - memo[i - 1] - 1]) {
                    memo[i] = 2 + memo[i - 1] + ((i - memo[i - 1] - 2 >= 0) ? memo[i - memo[i - 1] - 2] : 0);
                    ans = std::max(ans, memo[i]);
                }
            }
            return (int)ans;
        }
	//Not DP, using stack, simplified
	int longestValidParentheses1(string s) {
		size_t last = 0, ans = 0;
		stack<size_t> stk;
		for (char c : s) {
			ans = std::max(ans, last);
			if ('(' == c) {
				stk.push(last);
				last = 0;
			}
			else if (false == stk.empty()) {//')' == c
				last += 2 + stk.top();
				stk.pop();
			}
			else last = 0;//')' == c && stk.empty()
		}
		return (int)std::max(ans, last);
	}
	//Not DP, using stack
	int longestValidParentheses2(string s) {
		size_t len = s.length();
		long long last = 0, ans = 0;
		if (len < 2)return 0;
		stack<long long> stk;
		for (char c : s) {
			if (true == stk.empty()) {
				ans = std::max(last, ans);
				if ('(' == c)
					stk.push(last);
				last = 0;
			}
			else {
				if (')' == c) {
					last += 2 + stk.top();
					stk.pop();
				}
				else {
					stk.push(last);
					ans = std::max(last, ans);
					last = 0;
				}
			}
		}
		return (int)std::max(last, ans);
	}
};
void TestLongestValidParentheses() {
	SolutionLongestValidParentheses so;
	assert(0 == so.longestValidParentheses(")"));
	assert(0 == so.longestValidParentheses("("));
	assert(6 == so.longestValidParentheses(")()((())()"));
	assert(10 == so.longestValidParentheses(")()((())())"));
	assert(8 == so.longestValidParentheses(")()((())))()"));
	assert(2 == so.longestValidParentheses("(()(((()"));
	assert(22 == so.longestValidParentheses(")(((((()())()()))()(()))("));

	assert(2 == so.longestValidParentheses("(()"));
	assert(4 == so.longestValidParentheses(")()())"));
	assert(4 == so.longestValidParentheses("(())"));
	assert(6 == so.longestValidParentheses("()(())"));
	assert(12 == so.longestValidParentheses(")()())()))()()((()))()"));
	assert(12 == so.longestValidParentheses(")())()(()()(())))()(())))())()))"));
}
