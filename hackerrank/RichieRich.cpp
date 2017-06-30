#include <cassert>
#include <string>
#include <bitset>
#include <iostream>

using namespace std;

//https://www.hackerrank.com/challenges/richie-rich
/*
Richie Rich
Sandy likes palindromes. A palindrome is a word, phrase, number, or other sequence of characters which reads the same backward as it does forward. For example, madam is a palindrome.
On her  birthday, Sandy's uncle, Richie Rich, offered her an -digit check which she refused because the number was not a palindrome. Richie then challenged Sandy to make the number palindromic by changing no more than  digits. Sandy can only change  digit at a time, and cannot add digits to (or remove digits from) the number.
Given  and an -digit number, help Sandy determine the largest possible number she can make by changing digits.

Note: Treat the integers as numeric strings. Leading zeros are permitted and can't be ignored (So 0011 is not a palindrome, 0110 is a valid palindrome). A digit can be modified more than once.

Input Format
The first line contains two space-separated integers,  (the number of digits in the number) and  (the maximum number of digits that can be altered), respectively.
The second line contains an -digit string of numbers that Sandy must attempt to make palindromic.

Constraints

- 0 < n <= 10E5
- 0 <= k <= 10E5
- Each character  in the number is an integer where 0 <= i <= 9.

Output Format

Print a single line with the largest number that can be made by changing no more than  digits; if this is not possible, print -1.
Sample Input 0
4 1
3943
Sample Output 0
3993
Sample Input 1
6 3
092282
Sample Output 1
992299
Sample Input 2
4 1
0011
Sample Output 2
-1

Explanation

Sample 0

There are two ways to make 3943 a palindrome by changing exactly k = 1 digit:
1. 3943 -> 3443
2. 3943 -> 3993
3993 > 3443, so we print 3993.

Observations:
1. Doesn't seem to need any fancy algorithm. Simply comparing s[i] with s[n - i - 1] shall tell how many differences in characters;

2. Thoughts (Lots of details to consider though):
- Scan the string to "correct" character pairs that are not identical. Since it is asked to return the largest possible palindrome number,
intuitively, we change the pair to max(s[i], s[n - i - 1]). Each of these operations counts as 1 change.
Note: if length of the string is odd, the central character keeps untouched, when i = n / 2, i == n - i - 1
- At this moment, the string is a palindrome already.
- If the changing we made is greater than k, return "-1"
- Then if there are still available changing opportunity, we replace the pair from whatever character to '9' if they are not '9' yet. This operation
will cost 2 changes if the characters in the current pair are originally same, or 1 change if the characters in the pair were "corrected" to be the same.
Why so? For example
1002, in first step, it turns to 2002, 1 change is made; and then in the final step, we make it to 9009. Then,
from 1002 -> 9009, it costs 2 changes overall. Therefore, in the final step, the change from 2 to 9 only contributes 1 change since we counted 1 change already.
- Since the scanned indexes are in [0 , n/2), if there is still change opportunity available, s[n/2] can be changed to '9' if n is an odd.

In order to track which index was changed from [0, n/2), we use a bitset with 100001 bits. It was used in the final step to decide changing to '9' costs 1 or 2.
*/
class RichieRich {
public:
	string richieRich(string s, int n, int k) {
		if (n < 1 || k < 0 || n >(int)s.length())return "-1";
		int cnt = 0;
		bitset<100001> memo;
		for (int i = 0; i <= n / 2; ++i) {
			if (s[i] != s[n - i - 1]) {
				++cnt;
				memo.set(i, 1);
				if (s[i] >= s[n - i - 1]) s[n - i - 1] = s[i];
				else s[i] = s[n - i - 1];
			}
		}
		if (cnt > k)return"-1";
		cnt = k - cnt;
		for (int i = 0; i < n / 2 && cnt > 0; ++i) {
			if ('9' != s[i] && (1 == memo.test(i) ? cnt - 1 : cnt - 2) > -1) {
				cnt = 1 == memo.test(i) ? cnt - 1 : cnt - 2;
				s[i] = s[n - i - 1] = '9';
			}
		}
		if (cnt > 0 && 1 == (1 & n))s[n / 2] = '9';
		return s;
	}
};
void TestRichieRich() {
	RichieRich rr;
	assert("3993" == rr.richieRich("3943", 4, 1));
	assert("992299" == rr.richieRich("092282", 6, 3));
	assert("-1" == rr.richieRich("0011", 4, 1));
	assert("12921" == rr.richieRich("12321", 5, 1));
	assert("992299" == rr.richieRich("932239", 6, 2));
	assert("99399" == rr.richieRich("11331", 5, 4));
}