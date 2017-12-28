#include <string>

using namespace std;

//https://leetcode.com/problems/longest-palindrome/
/*
409. Longest Palindrome

Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.

Observations:
Palindrome has two forms: one is a string that is completely mirrored, the other form is sysmetric around a center.

If a letter occurs even times, all its occurences can be used to built the palindrome.

If odd times, all its occurences minus 1  can be contributed for building the palindrome.

The exception is the center letter. If there is any letter with an odd times occurence, the palindrome can have one and only one center.

The above BS can be simplifed by:

Given cnt as the length of the palindrome, i as the count for each letter, f to indicate if a center exists
- cnt += i / 2 * 2;
- if 0 == f && 1 == (1 & i)): f = true;
*/
class SolutionLongestPalindrome {
public:
    int longestPalindrome(string s) {
        int memo[52] = {0}, odd = 0, ans = 0;
        for(char c : s) {
            if(c >= 'a')++memo[(int)c - (int)'a' + 26];
            else ++memo[(int)c - (int)'A'];
        }
        for(int i : memo) {
            ans += i / 2 * 2;
            if(i > 0 && 0 == odd && 1 == (i & 1))++odd;
        }
        return ans + odd;
    }
    int longestPalindrome1(string s) {
        int memo[52] = {0}, odd = 0, ans = 0;
        for(char c : s) {
            if(c >= 'a')++memo[(int)c - (int)'a' + 26];
            else ++memo[(int)c - (int)'A'];
        }
        for(int i : memo) {
            if(0 == i)continue;
            if(0 == (i & 1))ans += i;
            else {
                if(0 == odd)++odd;
                ans += i - 1;
            }
        }
        return ans + odd;
    }
};
