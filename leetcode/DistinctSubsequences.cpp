#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/distinct-subsequences/
/*
 115. Distinct Subsequences
 
 Given a string S and a string T, count the number of distinct subsequences of T in S.
 
 A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
 
 Here is an example:
 S = "rabbbit", T = "rabbit"
 
 Return 3.
 
 Observations:
 
 After doing this many DP, as long as I see two strings, sequences, arrays, first thing I would do is to build a matrix
 using one string on x axis and the other on y axis. Of course, a memo array!
 
   r a b b b i t <--s
 r 1 1 1 1 1 1 1
 a 0 1 1 1 1 1 1
 b 0 0 1 ? 2 2 2
 b 0 0 0 1 3 3 3
 i 0 0 0 0 0 3 3
 t 0 0 0 0 0 0 3
 ^
 |
 t
 
 1. By playing the matrix, it's easy to discover that if t[i] != s[j], the number of unique subsequences memo[i][j] = memo[i][j - 1], see above example, row 1.
 
 2. Also, it's important to realize that not entire memo array is necessary: we are only dealing a triangle matrix that cover the upper half of the matrix.
 
 3. It's not intuitive to introduce the DP theory here since we are not trying to find an optimized solution. The question is: at row 3, column 4, what is the total number for distinct subsequences? The answer is 2. How come?
    
    For any given s[j], if it happens to match the right character on t[j], we could use it, then the number of distinct subsequence is the number at memo[i - 1][j - 1]. For above example, if we use row 3 and column 4 'b' matching
    "rab" on string t, we need find out the number at "ra" on t, when "ra" on t is matched on s, how many we have? memo[i - 1][j - 1], that's 1
 
    If we decide to skip row 3 and column 4 'b' on string s, we have "rab" on string t matches "rab" on string s, that's memo[i][j - 1], which is 1.
 
    So the total is memo[i - 1][j - 1] + memo[i][j - 1] = 2
 
 Path[i][j] = Path[i][j-1]            (we discard S[j])
               +     Path[i-1][j-1]    (S[j] == T[i] and we are going to use S[j])
               or
               +      0                 (S[j] != T[i] so we could not use S[j])
 
 4. Use the same trick in Edit Distance, we could shrink memo array from 2D to 1D, then from 1D of two rows (previous and current) to 1D of 1 row with two extra variables.
 
 This gives us an O(N*M) time and O(N) space algorithm.
 
 Well, I still don't understand why s = "abcd" and t="", the answer is 1...I think that's just a by product of the "standard" implementation of the algorithm, which using an memo with length of (M + 1) and all memo[0][j] is initialized with 1.
 
 
*/
class SolutionDistinctSubsequences {
public:
    //3ms
    int numDistinct(string s, string t) {
        size_t lent = t.length(), lens = s.length();
        if(lens < lent)return 0;
        else if(0 == lent)return 1;
        vector<size_t> memo(lens, 0);
        for(size_t j = 0; j < lens; ++j) {
            if(t[0] == s[j])memo[j] = 1;
            memo[j] += (0 == j) ? 0 : memo[j - 1];
        }
        size_t upperleft = 0, tmp = 0;
        for(size_t i = 1; i < lent; ++i) {
            upperleft = memo[i - 1], memo[i - 1] = 0;
            for(size_t j = i; j < lens; ++j) {
                tmp = memo[j];
                if(s[j] == t[i])memo[j] =  memo[j - 1] + upperleft;
                else memo[j] = memo[j - 1];
                upperleft = tmp;
            }
        }
        return (int)memo[lens - 1];
    }
};
void TestDistinctSubsequences() {
    SolutionDistinctSubsequences so;
    assert(3 == so.numDistinct("rabbbit", "rabbit"));
    assert(1 == so.numDistinct("abcd", ""));
    assert(5 == so.numDistinct("abcfeaace", "ace"));
    assert(5 == so.numDistinct("aacaacca", "ca"));
    assert(258 == so.numDistinct("wwwadpfttapgtjbbgptqgjffjabgjgawgetpatpgwegjbluejget", "aptjg"));
    assert(10582116 == so.numDistinct("aabdbaabeeadcbbdedacbbeecbabebaeeecaeabaedadcbdbcdaabebdadbbaeabdadeaabbabbecebbebcaddaacccebeaeedababedeacdeaaaeeaecbe", "bddabdcae"));
}
