#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

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
O(M*N) space (the entir matrix) as well. By a closer look, we only need keep the previous row. We need 2 extra variables to track the upper left and "current" values on the previous row.

Comparing with LCS, this one has 3 picky edge cases due to the way we grab previous result.

1. 0 == j:

Since the current min at given [i, j] is decided by memo[j], memo[j - 1] and previous upperleft value (old memo[j - 1]), we have
an edge case when i = 0 (if we do NOT want to have extra code in the inner loop to handle it and instead seeking for an universal form)

The universal form:

- If word1[j] == word2[i], then memo[j + 1] = previous upperleft;
- If word1[j] != word2[i], then memo[j + 1] = MIN(previous upperleft, memo[j], memo[j + 1]) + 1

For the edge case at word1[0]:

- If word1[0] == word2[i], then memo[1] = memo[1] (previous row);
- If word1[0] != word2[i], then memo[1] = memo[1] (previous row) + 1;

Therefore, in order to keep the universal form, we have to make sure that previous upperleft and memo[0] is always no less than memo[1] (previous row)
when i = 0. This is done by:

ul = memo[0], memo[0] = i + 1; //if i starts from 0

Frist one makes sure memo[1] = previous upperleft is still intact when word1[0] == word2[j];
Second one makes sure memo[0] is no less than memo[1] (previous row);

2. Either of two strings is empty:

Fortunately, the arrangement for edage case 1 could cover edge case 2 as well!

3. 0 == i:

In this case, specifically,

When word1[j] != word2[0], then memo[j + 1] = MIN(previous upperleft, memo[j], memo[j + 1]) + 1

The previous result, for this case, the initialized state of memo will impact the result (previous upperleft and memo[j + 1], memo[j] as well when i = 0).

This is handled by:

std::iota(memo.begin(), memo.end(), 0);

This plus the handling of edge case 1 together will make sure memo[j] is always picked when i = 0.
*/
class SolutionEditDistance {
public:
	int minDistance(string word1, string word2) {
		size_t len1 = word1.length(), len2 = word2.length();
		vector<size_t> memo(len1 + 1, 0);
		std::iota(memo.begin(), memo.end(), 0);
		for (size_t i = 0, ul = 0; i < len2; ++i) {
			ul = memo[0], memo[0] = i + 1;
			for (size_t j = 0, t = 0; j < len1; ++j) {
				t = memo[j + 1];
				memo[j + 1] = (word1[j] == word2[i]) ? ul : std::min(ul, std::min(memo[j], t)) + 1;
				ul = t;
			}
		}
		return static_cast<int>(memo[len1]);
	}
	int minDistance1(string word1, string word2) {
		size_t len1 = word1.length(), len2 = word2.length();
		size_t m = 0, mul = 0;
		vector<size_t> memo(len1 + 1, 0);
		for (size_t i = 1; i <= len1; ++i)memo[i] = i;
		for (size_t i = 1; i <= len2; ++i) {
			mul = memo[0], memo[0] = i;
			for (size_t j = 1; j <= len1; ++j) {
				m = memo[j];
				if (word1[j - 1] == word2[i - 1])memo[j] = mul;
				else memo[j] = std::min(std::min(mul + 1, memo[j - 1] + 1), m + 1);
				mul = m;
			}
		}
		return (int)memo[len1];
	}
	//doesn't work
	int minDistance2(string word1, string word2) {
		size_t len1 = word1.length(), len2 = word2.length();
		int ans = std::max(len1, len2), tmp, k, m;
		size_t dif = std::abs((long)len1 - (long)len2);
		vector<vector<size_t> > map(len1, vector<size_t>(len2, 0));
		for (size_t i = 0; i < len1; ++i) {
			for (size_t j = 0; j < len2; ++j) {
				tmp = (i > 0 && j > 0) ? map[i - 1][j - 1] : 0;
				if (word1[i] == word2[j])map[i][j] = 1 + tmp;
				else map[i][j] = tmp;
			}
		}
		//vector<std::pair<std::pair<int, int>, int> > ret;
		for (int i = 0; i < len2; ++i) {
			tmp = map[len1 - 1][i];
			if (tmp > 0) {
				k = i, m = len1 - 1;
				while (tmp > 1 && k > 0 && m > 0)tmp = map[--m][--k];
				//ret.push_back(std::make_pair(std::make_pair(k, m), map[len1 - 1][i]));
				tmp = (k <= m ? k + m - k : m + k - m) + dif + (len1 <= len2 ? len1 - k - map[len1 - 1][i] : len2 - k - map[len1 - 1][i]);
				ans = std::min(ans, tmp);
			}
		}
		for (int i = 0; i < len1; ++i) {
			tmp = map[i][len2 - 1];
			if (tmp > 0) {
				k = i, m = len2 - 1;
				while (tmp > 1 && k > 0)tmp = map[--k][--m];
				//ret.push_back(std::make_pair(std::make_pair(k, m), map[i][len2 - 1]));
				tmp = (k <= m ? k + m - k : m + k - m) + dif + (len1 <= len2 ? len1 - k - map[i][len2 - 1] : len2 - k - map[i][len2 - 1]);
				ans = std::min(ans, tmp);
			}
		}
		return ans;
	}
};
void TestEditDistance() {
	SolutionEditDistance so;
	string word1 = "mart";
	string word2 = "karma";
	assert(3 == so.minDistance(word1, word2));
	assert(3 == so.minDistance(word2, word1));
	word1 = "kitten", word2 = "sitting";
	assert(3 == so.minDistance(word1, word2));
	assert(3 == so.minDistance(word2, word1));
	word1 = "abcde", word2 = "fgbcabll";
	assert(6 == so.minDistance(word1, word2));
	assert(6 == so.minDistance(word2, word1));
	word1 = "", word2 = "abc";
	assert(3 == so.minDistance(word1, word2));
	assert(3 == so.minDistance(word2, word1));
	word1 = "sea", word2 = "eat";
	assert(2 == so.minDistance(word1, word2));
	assert(2 == so.minDistance(word2, word1));
}
/*
Test cases:

"sea"
"eat"
""
""
""
"a"
"a"
""
"a"
"a"
""
"abc"
"abc"
""
"horse"
"ros"
"intention"
"execution"
"mart"
"karma"
"kitten"
"sitting"
"abcde"
"fgbcabll"

Outputs:

2
0
1
1
0
3
3
3
5
3
3
6
*/