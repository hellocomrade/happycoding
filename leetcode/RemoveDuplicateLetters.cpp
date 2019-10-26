#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/remove-duplicate-letters/
/*
316. Remove Duplicate Letters

Given a string which contains only lowercase letters, remove duplicate letters so that every letter appears once and only once.
You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: "bcabc"

Output: "abc"

Example 2:

Input: "cbacdcbc"

Output: "acdb"

Observations:

First of all, lexicographical order simply means 'a' < 'b' < 'c' < ...

This is a problem that can be figured out by scanning the sequence and finding the pattern. Can't believe
it can be solved in such a straightforward way!

Of course, we have to count the number of occurrence for each letter. Since only 26 of them, this can be done
in constant time using constant space.

Then, loop through the character with the help from a stack. When a character is presented, decrease its count
first no matter what. Then, compare it with the characters on the stack, pop those characters and reset their visit status if and only if:

1. current character has not been put on stack yet;
1. stack.top() > current character;
2. counter[statck.top()] > 0;

After the comparsion, all characters on the stack are either smaller than current character or only appear
before current character. In either case, they have to stay in that order.

There should be an array to track if a character is on the stack now (visit status). However, I managed to
reuse the counter array:

If a char is on the stack, simply negate its counter. When the time comes to decrease the counter, we will have
to check if counter[current_char - 'a'] is positive or negative and then do --positive or ++negative, which both
means decreaing by 1.

When a char is poped from the stack, simply reset its visit status by negate the previous negation.

Since only 26 letters are given, inner while loop will run at most 26 times. Therefore, time complexity is O(26N) -> O(N)
*/
class SolutionRemoveDuplicateLetters {
public:
	string removeDuplicateLetters(string s) {
		int counts[26] = { 0 }, sz = 0;
		stack<char> stk;
		std::for_each(s.begin(), s.end(), [&](char c) { ++counts[c - 'a']; });
		for (char c : s) {
			if (0 > counts[c - 'a']) {
				++counts[c - 'a'];
				continue;
			}
			if (0 < counts[c - 'a']) --counts[c - 'a'], counts[c - 'a'] *= -1;
			while (false == stk.empty() && 0 > counts[stk.top() - 'a'] && c < stk.top()) {
				counts[stk.top() - 'a'] *= -1;
				stk.pop();
			}
			stk.push(c);
		}
		sz = stk.size();
		vector<char> vec(sz, 0);
		while (false == stk.empty()) vec[--sz] = stk.top(), stk.pop();
		return string(vec.begin(), vec.end());
	}
};
/*
Test cases:

"bcabc"
"cbacdcbc"
"bbccaa"
"bcaabc"
"bczcb"
""
"a"

Outputs:

"abc"
"acdb"
"bca"
"abc"
"bcz"
""
"a"
*/