#include <stdio.h>
#include <cassert>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/edit-distance/
/*
 72. Edit Distance
 
 Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
 
 You have the following 3 operations permitted on a word:
 
 a) Insert a character
 b) Delete a character
 c) Replace a character
 
 https://en.wikipedia.org/wiki/Edit_distance
 
 Wagner–Fischer algorithm: https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
 Levenshtein distance: https://en.wikipedia.org/wiki/Levenshtein_distance
 
 Given len(word1) = N and len(word2) = M, WF algorithm takes O(M*N) time and O(N) space. Original algorithm takes
 O(M*N) space (the entir matrix) as well. By a closer look, we only need keep the previous row. Then further narrow the
 previous row to 2 extra variables to track the upper left and "current" values on the previous row.
 */
class SolutionEditDistance {
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
public:
    int minDistance(string word1, string word2) {
        size_t len1 = word1.length(), len2 = word2.length();
        size_t m = 0, mul = 0;
        vector<size_t> memo(len1 + 1, 0);
        for(size_t i = 1; i <= len1; ++i)memo[i] = i;
        for(size_t i = 1; i <= len2; ++i) {
            mul = memo[0], memo[0] = i;
            for(size_t j = 1; j <= len1; ++j) {
                m = memo[j];
                if(word1[j - 1] == word2[i - 1])memo[j] = mul;
                else memo[j] = std::min(std::min(mul + 1, memo[j - 1] + 1), m + 1);
                mul = m;
            }
        }
        return (int)memo[len1];
    }
};
void TestEditDistance() {
    string word1 = "mart", word2 = "karma";
    SolutionEditDistance so;
    assert(3 == so.minDistance(word1, word2));
    assert(3 == so.minDistance(word2, word1));
    word1 = "kitten", word2 = "sitting";
    assert(3 == so.minDistance(word1, word2));
    assert(3 == so.minDistance(word2, word1));

}
