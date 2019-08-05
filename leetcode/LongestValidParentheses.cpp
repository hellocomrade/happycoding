#include <cassert>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/longest-valid-parentheses/
/*
32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

Observations:

Doesn't look like a DP for me. It can be done with one stack and an extra variable. Stack is only pushed if a '('  is met. The value
that is pushed onto stack is either the length of the last max valid substring or zero depending on the position of '('.
If the prior char is ')' and it happens to have a valid parentheses ends at ')', the value is store in variable last and we push the value of last onto stack.
Otherwise 0 will be pushed. This is either because the prior char is '(' or ')' but no valid substring can be found there.

For example "()(((", push occurs at '(' (index 2) with value (last) of 2, the following '(' will be pushed with value of 0.
The reason to do so is: only if any valid substring starts from index 2, will the valid parentheses from index 0 to 1
be counted and therefore exends the valid substring, for example "()((()))", the longest one is the whole string, when we reach "((()))".

If we have "()((())", the last value (2) we store on stack when '(' at index 2 is met, will never be touched since there is no way to use this '(' to form any valid parentheses.

If ')' is met, depending on the status of the stack (empty or not), we could:
1. The stack is not empty, count length and store it in variable last if the stack is not empty then pop the stack. The pop here will remove matched '(' with the value
   of 0, which indicates there is no any valid substring before this '(' or a non-zero value which indicates otherwise.
2. The stack is empty, then simply reset last to 0, which indicates there is no valid parentheses can be found at this location at all. So there is no way to connect previous
   valid parentheses with the possible valid ones down the road because of this barrier ')'.

***Update on 2019-08-03***

leetcode offerred solutions:

https://leetcode.com/problems/longest-valid-parentheses/solution/

Two of them are interesting:
- One is using stack, which is no better than my longestValidParentheses1, but still an elegant solution with some very subtle setup;
- The other one is an amazing O(N) time with constant space solution which comes with a cost: 1 time slower than other linear solutions;
*/
class SolutionLongestValidParentheses {
public:
	int longestValidParentheses_leetcode_stack(string s) {
		int len = (int)s.length(), ans = 0;
		//stack will only store index for any '(' and any ')' that qualifies to mark the left boundary exclusively
		stack<int> stk;
		/*
		pushing -1 is necessary since the length of a valid parentheses is calculated
		using current index minus the index of the '(' before the leftmost '(' forming current
		valid parenteses. For example:

		"(()"

		when i = 2, the value on top of the stack is 0, length = 2 - 0;

		-1 for the case like "()".

		Why doing this? This is designed specifically for continuously tracking max valid substring, for example "(()()"
		When i = 4, the top of stack is with value 0. The max len at index 4 is (4 - 0) then.

		This might not be intuitive: only '('s have not been matched by ')' remain on the stack. They mark the left boundary
		for any max valid substring (exclusive). Furthermore, it also store ')' that can be used as the left boumdary marker
		in the case there is no more left '(' and -1 is poped.

		Comparing with DP solution, this looks more elegant but actually even harder to follow.
		*/
		stk.push(-1);
		for (int i = 0; i < len; ++i) {
			if ('(' == s[i]) stk.push(i);
			else {
				//Always pop '(' currently matches with s[i]
				stk.pop();
				/*
				Pushing i when s[i] == ')' is to make sure:

				1. len will be 0 in this case, which is that an extra ')' is discovered at i but no matching '('.
				2. More importantly, in this case, we use ')' as the mark of left boundary on the stack.
				*/
				if (true == stk.empty()) stk.push(i);
				ans = std::max(ans, i - stk.top());
			}
		}
		return ans;
	}
	/*
	Two pointers solution, constant space. Don't know why it works but it works:

	1. Scan from left to right, at anytime, the number of '(' L, is equal to the nubmer of ')', R, a valid substring
	   is found and its length is 2*R. If R is larger than L, reset both L and R to zero;
	2. Scan from right to left, at anytime, the number of '(' L, is equal to the nubmer of ')', R, a valid substring
	   is found and its length is 2*L. If L is larger than R, reset both L and R to zero;

	Why have to scan from both ends? For example "(()" will not return anything if only scanning from left coz L is always
	greater than R. This can be only solved if the scanning is done from right.
	*/
	int longestValidParentheses_leetcode_o1_space(string s) {
		int len = (int)s.length(), ans = 0;
		for (int i = 0, cntFromLeft = 0, cntFromRight = 0; i < len; ++i) {
			if ('(' == s[i]) ++cntFromLeft;
			else ++cntFromRight;
			if (cntFromRight == cntFromLeft) ans = std::max(ans, cntFromRight * 2);
			else if (cntFromRight > cntFromLeft) cntFromRight = cntFromLeft = 0;
		}
		for (int i = len - 1, cntFromLeft = 0, cntFromRight = 0; i > -1; --i) {
			if ('(' == s[i]) ++cntFromLeft;
			else ++cntFromRight;
			if (cntFromLeft == cntFromRight) ans = std::max(ans, cntFromLeft * 2);
			else if (cntFromLeft > cntFromRight) cntFromRight = cntFromLeft = 0;
		}
		return ans;
	}
	//A "DP" version. Store longest so far at each possible ')'
	int longestValidParentheses(string s) {
		int len = (int)s.length(), ans = 0;
		if (len < 2)return 0;
		vector<int> memo(len, 0);
		for (int i = 1; i < len; ++i) {
			if (')' == s[i] && i - memo[i - 1] - 1 >= 0 && '(' == s[i - memo[i - 1] - 1]) {
				memo[i] = 2 + memo[i - 1] + ((i - memo[i - 1] - 2 >= 0) ? memo[i - memo[i - 1] - 2] : 0);
				ans = std::max(ans, memo[i]);
			}
		}
		return ans;
	}
	//Not DP, using stack, simplified
	int longestValidParentheses1(string s) {
		size_t last = 0, ans = 0;
		stack<size_t> stk;
		for (char c : s) {
			if ('(' == c) {
				stk.push(last);
				last = 0;
			}
			else if (false == stk.empty()) {//')' == c
				last += 2 + stk.top();
				stk.pop();
			}
			else last = 0;//')' == c && stk.empty()
			ans = std::max(ans, last);
		}
		return ans;
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