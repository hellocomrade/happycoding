#include <string>

using namespace std;

//https://leetcode.com/problems/bulls-and-cows/
/*
299. Bulls and Cows

You are playing the following Bulls and Cows game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.

Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows.

Please note that both secret number and friend's guess may contain duplicate digits.

Example 1:

Input: secret = "1807", guess = "7810"

Output: "1A3B"

Explanation: 1 bull and 3 cows. The bull is 8, the cows are 0, 1 and 7.

Example 2:

Input: secret = "1123", guess = "0111"

Output: "1A1B"

Explanation: The 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow.

Note: You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.

Observations:

It's not hard at all to carry out a linear alogrithm with 2 passes on the string. First loop counts the number for each letter
in string "secret". The second loop iterates "secret" and "guess" together. If secret[i] == guess[i], it counts an A;
Otherwise, if letter in guess[i]'s count in "secret" is greater than zero, it counts an B. The only catch is when guess[i]
as neither A nor B is encountered before guess[i] as an A,

For example:

"1122"

"1222"

"3A0B"

At index 1, guess[1] = 2 is not A and not B. For this edge case, extra count down on B has to be added when secret[i] == guess[i]:
if (0 > --counts[guess[i] - '0']) --b; It will remove duplicated count on B.

There is actually a better one pass solution: instead of counting number of letters in a separate loop, the count is done
dynamically along with counting A and B. This can be achieved through two separate arrays for strings "secret" and "guess"
or a better solution is using only one array to count both "secret" and "guess":

At any given index i when secret[i] != guess[i]:

0 > counts[secret[i] - '0'] means secret[i] - '0' was discovered earlier in "guess"

0 < counts[guess[i] - '0'] means guess[i] - '0' was discovered earlier in "secret"

Eiteher way, they should be counted as B.

After the check, we should do:

++counts[secret[i] - '0'];
--counts[guess[i] - '0'];

You may do --counts[secret[i] - '0'] and ++counts[guess[i] - '0'] if you want, but the conditions for counting B
should be flipped as well.

I don't understand why so many people gave a thumb-down. It's actually a pretty good interview question coz interviewer
could expact candidate giving a two-pass solution first then encourge a better one pass solution.
*/
class SolutionBullsAndCows {
public:
	string getHint(string secret, string guess) {
		int counts[10] = { 0 };
		int a = 0, b = 0, len = (int)secret.length();
		for (int i = 0; i < len; ++i)
			if (secret[i] == guess[i]) ++a;
			else {
				if (0 > counts[secret[i] - '0']++) ++b;
				if (0 < counts[guess[i] - '0']--) ++b;
			}
		return std::to_string(a) + "A" + std::to_string(b) + "B";
	}
	string getHint1(string secret, string guess) {
		int counts[10] = { 0 };
		int a = 0, b = 0, len = (int)secret.length();
		for (char c : secret) ++counts[c - '0'];
		for (int i = 0; i < len; ++i)
			if (secret[i] == guess[i]) {
				++a;
				if (0 > --counts[guess[i] - '0']) --b;
			}
			else if (0 < counts[guess[i] - '0']) ++b, --counts[guess[i] - '0'];
		return std::to_string(a) + "A" + std::to_string(b) + "B";
	}
};
/*
Test cases:

"1122"
"1222"
"1221"
"1212"
"1807"
"7810"
"1123"
"0111"
"1234"
"4321"
"1111"
"0000"
"1222"
"2111"
"1"
"1"
"1"
"0"
""
""

Outputs:

"3A0B"
"2A2B"
"1A3B"
"1A1B"
"0A4B"
"0A0B"
"0A2B"
"1A0B"
"0A0B"
"0A0B"
*/