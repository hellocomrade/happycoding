#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/common-child/
/*
Common Child

Given two strings a and b of equal length, what's the longest string (s) that can be constructed such that it is a child of both? 

A string x is said to be a child of a string y if x can be formed by deleting 0 or more characters from y. 

For example, ABCD and ABDC has two children with maximum length 3, ABC and ABD. Note that we will not consider ABCD as a common child because C doesn't occur before D in the second string.

Input format

Two strings, a and b, with a newline separating them.

Constraints

- 1 <= |a|, |b| <= 5000 
- All characters are upper cased and lie between ASCII values 65-90.

Output format

Print the length of the longest string , such that  is a child of both  and .

Observations:

This is as same as Longest Common Subsequence...
*/
class SolutionCommonChild {
public:
    int commonChild(string s1, string s2){
        int len1 = (int)s1.length(), len2 = (int)s2.length(), t = 0;
        vector<int> memo(len1 + 1, 0);
        for(int i = 0, ul = memo[0]; i < len2; ul = memo[0], ++i) {
            for(int j = 0, t = memo[j + 1]; j < len1; t = memo[++j + 1]) {
                if(s1[j] == s2[i])memo[j + 1] = 1 + ul;
                else memo[j + 1] = std::max(memo[j + 1], memo[j]);
                ul = t;
            }
        }
        return 0 == len1 ? 0 : memo[len1];
    }
};
