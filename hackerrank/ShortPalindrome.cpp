#include <string>

using namespace std;

//https://www.hackerrank.com/challenges/short-palindrome/problem
/*
Short Palindrome

Consider a string, S, of n lowercase English letters where each character, Si (0 <= i < n), denotes the letter at index i in S.
We define an (a, b, c, d) palindromic tuple of S to be a sequence of indices in S satisfying the following criteria:

- Sa = Sd, meaning the characters located at indices a and d are the same.
- Sb = Sc, meaning the characters located at indices b and c are the same.
- 0 <= a < b < c < d < |S|, meaning that a, b, c, and d are ascending in value and are valid indices within string S.
Given S, find and print the number of (a, b, c, d) tuples satisfying the above conditions. As this value can be quite large, print it modulo 10^9 + 7.

Input Format

- A single string denoting S.

Constraints

- 1 <= |S| <= 10^6
- It is guaranteed that s only contains lowercase English letters.

Output Format

Print the the number of (a, b, c, d) tuples satisfying the conditions in the Problem Statement above.
As this number can be very large, your answer must be modulo (10^9 + 7).

Sample Input 0

kkkkkkz

Sample Output 0

15

Explanation 0

The letter z will not be part of a valid tuple because you need at least two of the same character to satisfy the conditions defined above.
Because all tuples consisting of four k's are valid, we just need to find the number of ways that we can choose four of the six k's.
This means our answer is C(6, 4) = 15 (mod 10^9 + 7).

Sample Input 1

ghhggh

Sample Output 1

4

Explanation 1

The valid tuples are:

1. (0, 1, 2, 3)
2. (0, 1, 2, 4)
3. (1, 3, 4, 5)
4. (2, 3, 4, 5)

Thus, our answer is 4 = 4 (mod 10^9 + 7).

Sample Input 0

kkkkkkz

Sample Output 0

15

Sample Input 1

abbaab

Sample Output 1

4

Sample Input 2

akakak
Sample Output 2

2

Explanation 2

Tuples possible are (1, 2, 4, 5) and (0, 1, 3, 4)

Observations:

This problem can be solved by DP. But, it doesn't like the typtical string related DP, which involves building
a 2D matrix and fill in values based upon previous move. This one is built upon a quite simple but not very intuitve
recursion using three counters:

At any given index i on S,

- Counter1[c], c in [0, 26), count the occurrence of character ('a' + c) on S.substr(0, i);
At index i Counter1[S[i] - 'a']++.
- Counter2[c][d], c, d in [0, 26), count the occurrence of 2 characters pair starting with ('a' + c) and end with ('a' + d) on S.substr(0, i);
At index i, for all 26 characters represented by c, Counter2[c][S[i] - 'a'] += Counter1[c].
- Counter3[c][d][d], c, d in [0, 26), count the occurrence of 2 characters tuple starting with ('a' + c) and followed by 2 ('a' + d) on S.substr(0, i);
At index i, for all 26 characters represented by c, Counter3[c][S[i] - 'a'][S[i] - 'a'] += Counter2[c][S[i] - 'a'].
- The answer is accumulating on [d][c][c][d]. At index i, for all 26 characters represented by c, this can be retrieved by Counter3[S[i] - 'a'][c][c][S[i] - 'a'].

Notice that steps 2 - 4 can be done in one loop from 0 to 25, which is considered constant time.

The actually order on increasing these counters is opposite to the steps above in order not to use temp variables:

For c in range(0, 26):
ans += Counter3[S[i] - 'a'][c][c][S[i] - 'a']
Counter3[c][S[i] - 'a'][S[i] - 'a'] += Counter2[c][S[i] - 'a']
Counter2[c][S[i] - 'a'] += Counter1[c]
++Counter1[c]

Notice that Counter3[c][d][d] can be really shrinked to Counter3[c][d] (the third dimension is useless), only 2 2D arrays are needed:

Counter2[26][26], Counter3[26][26]

and 1 1D array Counter1[26]

So constant space is needed and the whole algorithm runs in (26 * |S|) time, which is O(N)

Note, (A + B) % C = (A % C + B % C) % C
*/
class SolutionShortPalindrome {
private:
	static const int MOD = 1000000007;
public:
	int shortPalindrome(string s) {
		int len = (int)s.length(), k = 0, ans = 0;
		int char1Cnt[26] = { 0 }, char2Cnt[26][26] = { 0 }, char3Cnt[26][26] = { 0 };
		for (char c : s) {
			k = c - 'a';
			for (int i = 0; i < 26; ++i) {
				ans = (ans + char3Cnt[k][i]) % MOD;
				char3Cnt[i][k] = (char3Cnt[i][k] + char2Cnt[i][k]) % MOD;
				char2Cnt[i][k] = (char2Cnt[i][k] + char1Cnt[i]) % MOD;
			}
			char1Cnt[k] = (1 + char1Cnt[k]) % MOD;
		}
		return ans;
	}
};