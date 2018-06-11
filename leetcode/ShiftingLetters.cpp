#include <string>
#include <vector>

using namespace std;

//https://leetcode.com/problems/shifting-letters
/*
848. Shifting Letters

We have a string S of lowercase letters, and an integer array shifts.

Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a').

For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.

Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.

Return the final string after all such shifts to S are applied.

Example 1:

Input: S = "abc", shifts = [3,5,9]

Output: "rpl"

Explanation:

We start with "abc".

After shifting the first 1 letters of S by 3, we have "dbc".

After shifting the first 2 letters of S by 5, we have "igc".

After shifting the first 3 letters of S by 9, we have "rpl", the answer.

Note:

- 1 <= S.length = shifts.length <= 20000

- 0 <= shifts[i] <= 10 ^ 9

Observations:

"wrapping around so that 'z' becomes 'a'" means module against 26;

We could follow the instruction in shifts to process S, but it's going to be O(N^2);

Therefore, we need to get the total shifts needed for each character in S, then this can be done in O(N);

Using "prefix sum" will do. This needs to be done backward from len - 1 to 0, postfix sum;

My first submittal failed coz I didn't pay attention a classic "prefix sum" edge case: integer overflow. Two possible remedies:
- Using a separate prefix sum array with type of long;
- Calculate module against 26 at each position, note: (X + Y) % Z = X % Z + Y % Z;

I picked the second option, see shiftingLetters1

The above algorithm requires O(2*N). In fact this can be done in one linear scan: we could calculate "postfix sum" at each position
while we scan through S. This gives us shiftingLetters, running in O(N) time and O(1) space.
*/
class SolutionShiftingLetters {
public:
	string shiftingLetters(string S, vector<int>& shifts) {
		int len = (int)shifts.size();
		for (int i = len - 1, sum = shifts[len - 1] % 26; i > -1; sum += shifts[--i] % 26)
			S[i] = 'a' + ((S[i] - 'a') + sum) % 26;
		return S;
	}
	string shiftingLetters1(string S, vector<int>& shifts) {
		int len = (int)shifts.size();
		for (int i = len - 2; i > -1; --i) shifts[i] = shifts[i + 1] % 26 + shifts[i] % 26;
		for (int i = 0; i < len; ++i) S[i] = 'a' + ((S[i] - 'a') + shifts[i]) % 26;
		return S;
	}
};
/*
Test cases:

"abc"
[3,5,9]
"a"
[76]
"zba"
[3,6,9]
"ytuiqdq"
[190,0,32,67,0,7,1999]
"mkgfzkkuxownxvfvxasy"
[505870226,437526072,266740649,224336793,532917782,311122363,567754492,595798950,81520022,684110326,137742843,275267355,856903962,148291585,919054234,467541837,622939912,116899933,983296461,536563513]

Outputs:

"rpl"
"y"
"rqj"
"fstbuhn"
"wqqwlcjnkphhsyvrkdod"
*/