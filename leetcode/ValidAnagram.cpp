//https://leetcode.com/problems/valid-anagram/
/*
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/
#include <string>
using namespace std;
class SolutionValidAnagram {
public:
    bool isAnagram(string s, string t) {
        if(s.length() == t.length()) {
            long long memo[26] = {0};
            for(auto c : s)++memo[c - 97];
            for(auto c : t) {
                if(memo[c - 97] > 0)--memo[c - 97];
                else return false;
            }
            return true;
        }
        return false;
    }
};
