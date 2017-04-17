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

Optimal substructure: The optimal substructure relation for this problem means, if the lengths of A and B are M and N respectively,
then if A(1..M), B(1..N) interleaves C(1..M+N), for 1 <= K < M and 1 <= L < N, A(1..K) and B(1..L) will interleave C(1..K+L)

0    a    d    e

0  T    T    T    F

a  T    F    T    F

b  F    F    T    T

Given str1 = "ab" as header row, str2 = "ade" as the first column, str3 = "adabe", we have above matrix.

Adding dummy 0 as prefix for str1 and str2 is not only for facilitating algorithm writing, it actually has a real meaning: memo[0, 0 ... len2] means applying only str2
to form interleaved str3. memo[0 ... len1, 0] means use only str1 to form interleaved str3. These two are possible if either given str2 or str1 is empty.

memo[0, 0] is always TRUE, since we actually apply prefix 0 on str3 as well: "0adabe".

Each cell (i, j) in the matrix contains either a T (true) or F (false). If memo[i, j] is true, that means str1(1..i), str2(1..j) interleaves str3(1..i+j).

For example, memo[1, 1] == F, at this position, str1 = "a", str2 = "a", str3 = "ad", str1 and str2 can not interveal to s3

Another example, memo[2, 2] == T, str1 = "ab", str2 = "ad", str3 = "adab", str1 and str2 can interveal to s3

The optimal equations are:

str1[i - 1] == str3[i + j - 1] && TRUE == memo[i - 1][j]
and
str2[j - 1] == str3[i + j - 1] && TRUE == memo[i][j - 1]

You may wonder why we have to check memo[i][j - 1] if str2[j - 1] == str3[i + j - 1]? why not checking memo[i - 1][j] as well?

Still use the example above, M(2, 3) = T, that means either str1[2 - 1] = 'b' or str2[3 - 1] = 'e' can be added to the possible string "abad" ("ab" from str1 and "ad" from str2) or "aade" ("a" from str1 and "ade" from str2)
to form a valid interleaving string. Obviously, "aade" is not a valid selection for str3 "adabe", this can actually be confirmed by memo[1, 3] = FALSE, which means by combining "a" and "ade", we are NOT able to
form a valid interleaved string to match the first 4 characters of str3, which is "adab". So, this pre-existing match comes from "abad", memo[2, 2] = TRUE!

By comparing str1[2 - 1] = 'b', str2[3 - 1] = 'e' with str3[3 + 2 - 1] = 'e', str2[2] has a match. Therefore, we have to check if there is a pre-existing match with "abad" ("ab" from str1 and "ad" from str2), memo[2, 2] = TRUE.
So, we can safely say memo[2, 3] = TRUE as well. By the explanation above, checking memo[i - 1][j] => memo[1][2] does NOT make sense since it represents the combined string "aade" ("a" from str1 and "ade" from str2), 'e' has been
used already, it will be impossible to use 'e' again if memo[1][2] is involved.
*/
class SolutionInterleavingStrings {
public:
	bool isInterleave(string s1, string s2, string s3) {
		size_t len1 = s1.size(), len2 = s2.size(), len3 = s3.size();
		if (len3 != len1 + len2)return false;
		++len1, ++len2, ++len3;
		vector<bool> memo(len2, 0);
		for (size_t i = 0; i < len1; ++i) {
			for (size_t j = 0; j < len2; ++j) {
				if (0 == i && 0 == j)
					memo[0] = true;
				else if (0 == i)
					memo[j] = (s2[j - 1] == s3[i + j - 1] && true == memo[j - 1]) ? true : false;
				else if (0 == j)
					memo[j] = (s1[i - 1] == s3[i + j - 1] && true == memo[j]) ? true : false;
				else
					memo[j] = (s1[i - 1] == s3[i + j - 1] && true == memo[j]) || (s2[j - 1] == s3[i + j - 1] && true == memo[j - 1]) ? true : false;
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
