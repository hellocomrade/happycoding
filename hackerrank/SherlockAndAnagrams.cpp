#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

//https://www.hackerrank.com/challenges/sherlock-and-anagrams
/*
Sherlock and Anagrams

Given a string S, find the number of "unordered anagrammatic pairs" of substrings.
In other words, find the number of unordered pairs of substrings of S that are anagrams of each other.

Two strings are anagrams of each other if the letters of one string can be rearranged to form the other string.

Input Format
First line contains T, the number of testcases. Each testcase consists of string S in one line.

Constraints
- 1 <= T <= 10
- 2 <=length(S) <= 100

String  contains only the lowercase letters of the English alphabet.

Output Format
For each testcase, print the required answer in one line.

Sample Input#00

2
abba
abcd
Sample Output#00

4
0
Sample Input#01

5
ifailuhkqq
hucpoltgty
ovarjsnrbf
pvmupwjjjf
iwwhrlkpek
Sample Output#01

3
2
2
6
3
Explanation

Sample00
Let's say S[i, j] denotes the substring Si, Si+1, ...Sj.

testcase 1:
For S=abba, anagrammatic pairs are:  (a and a),  (ab and ba),  (b and b) and  (abb and bba).

testcase 2:
No anagrammatic pairs.

Sample01

ifailuhkqq
i|0,0| i|3,3|
q|8,8| q|9,9|
afi|0,2| afi|1,3|
3
hucpoltgty
t|6,6| t|8,8|
gt|6,7| gt|7,8|
2
ovarjsnrbf
r|3,3| r|7,7|
jnrs|3,6| jnrs|4,7|
2
pvmupwjjjf
p|0,0| p|4,4|
j|6,6| j|7,7|
j|6,6| j|8,8|
j|7,7| j|8,8|
jj|6,7| jj|7,8|
mpuv|0,3| mpuv|1,4|
6
iwwhrlkpek
w|1,1| w|2,2|
k|6,6| k|9,9|
ekp|6,8| ekp|7,9|
3

Observations:
If naive, O(N^3); using hash can reduce complexity to O(N^2).

Only lowercase English letters are allowed, so we have a free const time/space dimension: up to 26...

My idea is using prefix sum. Of course, every element in the prefix sum array is a vector with size 26, but so what? It's still considered const :)

Then comparing every substring pairs with size varying from 2 to (len - 1) to see if they have the same signature.
The signature is defined by the frequence table (a vector with 26 elements). The idea is that if two strings are anagrams,
their frequence table shall be the same.
For example: "abad" => [a: 2, b: 1, d: 1], "daba" => [a: 2, b: 1, d: 1]
This can be retrieved in O(26) through the prefixSum array.

Attention should be given on the case like "ajjj", we have [j(1), j(2)], [j(1), j(3)], [j(2), j(3)], [jj(1-2), jj(2-3)].
This is the reason unordered_map has to be used instead of unordered_set. The count of the existence of a substring has to be
available as well!
When the first j shows up, 1 is given, not addition to the ans. When the second shows, ans += memo[j], then ++memo[j] to 2; when
the third shows up, we do ans += 2 and then memo[j] + 1 to 3. Therefore, we count all 3 combination into ans.
This is actually C(K, 2).


So, we could end up a simpler solution by filling the frequence table for all possible substrings then count.

*/
class SolutionSherlockAndAnagrams {
private:
	string getKey(const vector<size_t> vec) {
		std::stringstream ss;
		for (int i = 0; i < 26; ++i)
			ss << i << ':' << vec[i] << ',';
		return ss.str();
	}
public:
	int sherlockAndAnagrams(string s) {
		size_t len = s.length(), cnt = 1, ans = 0;
		unordered_map<string, size_t> memo;
		vector<vector<size_t>> prefixSum(len + 1, vector<size_t>(26, 0));
		vector<size_t> vec(26, 0);
		for (size_t i = 0; i < len; ++i) {
			prefixSum[i + 1][s[i] - 'a'] = 1;
			for (int j = 0; j < 26; ++j)
				prefixSum[i + 1][j] += prefixSum[i][j];
		}
		while (cnt < len) {
			for (size_t i = 0; i + cnt <= len; ++i) {
				for (int j = 0; j < 26; ++j)
					vec[j] = prefixSum[i + cnt][j] - prefixSum[i][j];
				string key = this->getKey(vec);
				if (memo.end() == memo.find(key))
					memo.emplace(key, 1);
				else
					ans += memo[key]++;
			}
			++cnt;
		}
		return static_cast<int>(ans);
	}
};
void TestSherlockAndAnagrams() {
	SolutionSherlockAndAnagrams so;
	assert(4 == so.sherlockAndAnagrams("abba"));
	assert(0 == so.sherlockAndAnagrams("abcd"));
	assert(3 == so.sherlockAndAnagrams("ifailuhkqq"));
	assert(2 == so.sherlockAndAnagrams("hucpoltgty"));
	assert(2 == so.sherlockAndAnagrams("ovarjsnrbf"));
	assert(6 == so.sherlockAndAnagrams("pvmupwjjjf"));
	assert(3 == so.sherlockAndAnagrams("iwwhrlkpek"));
}