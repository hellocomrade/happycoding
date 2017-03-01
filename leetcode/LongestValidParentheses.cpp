#include <cassert>
#include <stack>
#include <string>

using namespace std;

//https://leetcode.com/problems/longest-valid-parentheses/
/*
 32. Longest Valid Parentheses
 
 Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 
 For "(()", the longest valid parentheses substring is "()", which has length = 2.
 
 Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
 */
class SolutionLongestValidParentheses {
public:
    //Not DP, using stack
    int longestValidParentheses(string s) {
        size_t len = s.length();
        long long last = 0, ans = 0;
        if(len < 2)return 0;
        stack<long long> stk;
        for(char c : s) {
            if(true == stk.empty()) {
                ans = std::max(last, ans);
                if('(' == c)
                    stk.push(last);
                last = 0;
            }
            else {
                if(')' == c) {
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
