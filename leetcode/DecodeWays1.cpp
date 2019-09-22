#include <string>

using namespace std;

//https://leetcode.com/problems/decode-ways/
/*
91. Decode Ways

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1

'B' -> 2

...

'Z' -> 26

Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"

Output: 2

Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:

Input: "226"

Output: 3

Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Observations:

Redo this after 3 years, original one was using C at: https://github.com/hellocomrade/happycoding/blob/master/leetcode/DecodeWays.cpp

The reason for redo is because someone met this problem during an interview and other people made the comment saying
this is one of the FAQs during interview...

It's not hard to define this as a DP problem. Then if one takes a closer look, it appears O(1) space is promising coz
only the previous count and the count before the previous are needed for deciding the count at current index.

The tricky part which contributes to the low ACCEPT rate is on detail. The followings are not valid

'0', '00', '01', '27', '100', '130'

since only '1' to '26' are legit

But these are valid:

'110',

So if the edge case involving zero can be ruled out first, which is:

- s[i] = 0, s[i - 1] = 0;
- s[i] = 0, s[i - 1] != '1' or '2';

Remaining cases (subproblems) can be represented by a state transform formula with the extra routine on
the cases involving zero:

count[i] =

- count[i - 1], if s[i - 1: i] is not a valid decode, which is in [1, 26];
- count[i - 2] + count[i - 1], if s[i - 1: i] is in [1, 26] and s[i] != 0, which means count[i - 1] can not be carried over.
  for example: '1220', count[i] = count[i - 2] = 2 since s[i] = 0, count[i - 1] = 3 can not apply since s[i] = 0 is not valid.
  however, for the case of '1223', count[i] = count[i - 2] + count[i - 1] = 2 + 3 = 5, since s[i] = 3 is a valid decode;
- count[i - 2], if s[i - 1: i] is in [1, 26] and s[i] = 0;

Overall O(N) time and O(1) space, only two extra variable is needed: one for previous count, the other is for previous character.
*/
class SolutionDecodeWays1 {
public:
	int numDecodings(string s) {
		int ans = 1, prev = 0, t = 0;
		char prev_c = 0;
		for (char c : s) {
			if ('0' == c && (0 == prev_c || ('1' != prev_c && '2' != prev_c))) return 0;
			t = ans;
			ans = ('1' == prev_c || ('7' > c && '2' == prev_c)) ? ('0' != c ? ans : 0) + prev : ans;
			prev = t, prev_c = c;
		}
		return 0 < s.length() ? ans : 0;
	}
};
/*
Test Cases:

""
"0"
"1"
"10"
"17"
"71"
"27"
"26"
"62"
"72"
"01"
"1001"
"12"
"120"
"61"
"226"
"2123"
"12345"
"54321"
"2353626"
"235362668"
"355036670372"
"435767967363610469761206436"

Outputs:

0
0
1
1
2
1
1
2
1
1
0
0
2
1
1
3
5
3
2
4
4
0
1
*/