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

Each character  in the number is an integer where .
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
*/
class RichieRich {
public:
    string richieRich(string s, int n, int k){
        if(n < 1 || k < 0 || n > s.length())return "-1";
        if(1 == n) {
            if(k > 0)
                s[0] = '9';
            return s;
        }
        int cnt = 0;
        bitset<100001> memo;
        for(int i = 0; i < n / 2; ++i) {
            if(s[i] != s[n - i - 1]) {
                ++cnt;
                memo.set(i, 1);
                if(s[i] >= s[n - i - 1]) s[n - i - 1] = s[i];
                else s[i] = s[n - i - 1];
            }
        }
        if(cnt > k)return"-1";
        cnt = k - cnt;
        for(int i = 0; i < n / 2 && cnt > 0; ++i) {
            if('9' != s[i] && (1 == memo.test(i) ? cnt - 1 : cnt - 2) > -1) {
                cnt = 1 == memo.test(i) ? cnt - 1 : cnt - 2;
                s[i] = s[n - i - 1] = '9';
            }
        }
        if(cnt > 0 && 1 == (1 & n))s[n / 2] = '9';
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
