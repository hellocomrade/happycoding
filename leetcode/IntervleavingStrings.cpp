#include <cassert>
#include <string>
#include <vector>

using namespace std;

//https://leetcode.com/problems/interleaving-string/
/*
 97. Interleaving String
 
 Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
 
 For example,
 Given:
 s1 = "aabcc",
 s2 = "dbbca",
 
 When s3 = "aadbbcbcac", return true.
 When s3 = "aadbbbaccc", return false.
 
 https://leetcode.com/articles/interleaving-strings/
 
 Observation:
 http://techieme.in/find-interleaving-strings-using-dynamic-programming/
    0    a    d    e
 
 0  T    T    T    F
 
 a  T    F    T    F
 
 b  F    F    T    T
 
 Given str1 = "abe", str2 = "ab", str3 = "adabe" and above matrix,
 
 Each cell (i, j) in the matrix contains either a T (true) or F (false). If M(i,j) is true, that means str1(1..i), str2(1..j) interleaves str3(1..i+j).
 
 For example, M(1, 1) == F, at this position, str1 = "a", str2 = "a", str3 = "ad", str1 and str2 can not interveal to s3
 
 Anther example, M(2, 2) == T, str1 = "ab", str2 = "ad", str3 = "adab", str1 and str2 can interveal to s3
 
 The optimal sub-solutions are:
 
 s1[i - 1] == s3[i + j - 1] && 1 == memo[i - 1][j]
 and
 s2[j - 1] == s3[i + j - 1] && 1 == memo[i][j - 1]
 
 You may wonder why we have to check memo[i - 1][j] if s1[i - 1] == s3[i + j - 1]? why not memo[i][j - 1]?
 
 Still use the example above, M(2, 3) = T, that's because str1[2 - 1] = 'b' == str3[2 - 1 + 3 - 1] = 'b', at this moment, given str3 = "adab", we have to see what other characters we could have by adding 'b', there are str2 = "ad" and str1 ="a". In order to check the result with "a", "ad", we have to check memo[i - 1][j]... 
*/
class SolutionInterleavingStrings {
public:
    bool isInterleave(string s1, string s2, string s3) {
        size_t len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
        if(len3 != len1 + len2)return false;
        ++len1, ++len2, ++len3;
        vector<char> memo(len2, 0);
        for(size_t i = 0; i < len1; ++i) {
            for(size_t j = 0; j < len2; ++j) {
                if(0 == i && 0 == j)
                    memo[0] = 1;
                else if(0 == i)
                    memo[j] = (s2[j - 1] == s3[i + j - 1] && 1 == memo[j - 1]) ? 1 : 0;
                else if(0 == j)
                    memo[j] = (s1[i - 1] == s3[i + j - 1] && 1 == memo[j]) ? 1 : 0;
                else
                memo[j] = (s1[i - 1] == s3[i + j - 1] && 1 == memo[j]) || (s2[j - 1] == s3[i + j - 1] && 1 == memo[j - 1]) ? 1 : 0;
            }
        }
        return memo[len2 - 1];
    }
};
void TestInterleavingStrings() {
    SolutionInterleavingStrings so;
    assert(true == so.isInterleave("", "", ""));
    assert(true == so.isInterleave("aabcc", "dbbca", "aadbbcbcac"));
    assert(false == so.isInterleave("aabcc", "dbbca", "aadbbbaccc"));
}
