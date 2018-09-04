#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/reconstruct-original-digits-from-english/
/*
423. Reconstruct Original Digits from English

Given a non-empty string containing an out-of-order English representation of digits 0-9, output the digits in ascending order.

Note:
- Input contains only lowercase English letters.
- Input is guaranteed to be valid and can be transformed to its original digits. That means invalid inputs such as "abc" or "zerone" are not permitted.
- Input length is less than 50,000.

Example 1:

Input: "owoztneoer"

Output: "012"

Example 2:

Input: "fviefuro"

Output: "45"

Observations:

It's funny to realize that this is done through enumeration. The general idea is to try to identify each word just by its unique letter.
This may sound promising for couple words, which can be indentified immediately:

"zero" - 'z'
"two" - 'w'
"four" - 'u'
"six" - 'x'
"eight" - 'g'

However, other words can be identified by a single letter. My original idea is to focus on the initial letter of each word. They might be identifiable
by checking multiple letters, for example, "one"

Starting with 'o', however, other words, such as 'zero', 'two', 'four', have 'o' as well. If one can tell, there are more 'o' then 'zero', 'two', 'four' combined,
there must be an 'one':

memo['o' - 'a'] > memo['z' - 'a'] + memo['w' - 'a'] + memo['u' - 'a']

memo is an array storing the number of occurrence of all letters in the string.

This approach works for all words except for "nine". Fortunately, this is the only exception. So, it can be identified after switch case by
checking how many 'i's are left given the fact all input strings are valid. Why not 'n'? Well, "nine" has two 'n's so the count has to be divided by 2.
'i' is an unique letter in "nine".

This approach works but it's not the best one in terms of time complexity, it requires looping string twice.

Actually, this problem can be done in strict O(N) time! After the counting on letters is done, the number of digits can be done in O(1).

First of all, the following can be done easily:

digits[0] = memo['z' - 'a'];

digits[2] = memo['w' - 'a'];

digits[4] = memo['u' - 'a'];

digits[6] = memo['x' - 'a'];

digits[8] = memo['g' - 'a'];

With the above variables as clue, other digits can be decided accordingly, for example:

digits[1] = memo['o' - 'a'] - digits[0] - digits[2] - digits[4];
*/
class SolutionReconstructOriginalDigitsFromEnglish {
public:
	string originalDigits(const string s) {
		int memo[26] = { 0 }, digits[10] = { 0 };
		string str;
		stringstream ss;
		for (char c : s) ++memo[c - 'a'];
		digits[0] = memo['z' - 'a'];
		digits[2] = memo['w' - 'a'];
		digits[4] = memo['u' - 'a'];
		digits[6] = memo['x' - 'a'];
		digits[8] = memo['g' - 'a'];
		digits[1] = memo['o' - 'a'] - digits[0] - digits[2] - digits[4];
		digits[3] = memo['t' - 'a'] - digits[2] - digits[8];
		digits[5] = memo['f' - 'a'] - digits[4];
		digits[7] = memo['v' - 'a'] - digits[5];
		digits[9] = memo['i' - 'a'] - digits[5] - digits[6] - digits[8];
		for (int i = 0; i < 10; ++i)
			while (digits[i]-- > 0) ss << i;
		return ss.str();
	}string originalDigits1(string s) {
		int memo[26] = { 0 }, digits[10] = { 0 };
		string str;
		stringstream ss;
		for (char c : s) ++memo[c - 'a'];
		for (char c : s) {
			str = "";
			if (1 > memo[c - 'a']) continue;
			switch (c) {
			case 'e':
				if (memo['g' - 'a'] > 0) str = "eight", ++digits[8];
				break;
			case 'f':
				if (memo['u' - 'a'] > 0) str = "four", ++digits[4];
				else str = "five", ++digits[5];
				break;
			case 'o':
				if (memo['o' - 'a'] > memo['z' - 'a'] + memo['w' - 'a'] + memo['u' - 'a']) str = "one", ++digits[1];
				break;
			case 's':
				if (memo['x' - 'a'] > 0) str = "six", ++digits[6];
				else str = "seven", ++digits[7];
				break;
			case 't':
				if (memo['w' - 'a'] > 0) str = "two", ++digits[2];
				else if (memo['h' - 'a'] > memo['g' - 'a']) str = "three", ++digits[3];
				break;
			case 'z':
				str = "zero", ++digits[0];
				break;
			default:
				break;
			}
			for (char cc : str)
				--memo[cc - 'a'];
		}
		for (int i = 0; i < 10; ++i)
			while (digits[i]-- > 0) ss << i;
		while (memo['i' - 'a']-- > 0) ss << 9;
		return ss.str();
	}
	//TLE
	string originalDigits2(string s) {
		vector<string> one2ten{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
		vector<int> ans(10, 0);
		unordered_map<char, int> cntmap;
		for (char c : s) ++cntmap[c];
		stringstream ss;
		while (false == cntmap.empty()) {
			for (int i = 0, cnt = 0; i < 10; ++i) {
				cnt = 0;
				for (char c : one2ten[i]) if (cntmap.count(c) > 0) ++cnt;
				if (cnt == one2ten[i].length()) {
					for (char c : one2ten[i])
						if (0 == --cntmap[c])
							cntmap.erase(c);
					++ans[i];
				}
			}
		}
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < ans[i]; ++j)
				ss << i;
		return ss.str();
	}
};
void TestReconstructOriginalDigitsFromEnglish() {
	SolutionReconstructOriginalDigitsFromEnglish so;
	so.originalDigits("ffixivoeurs");
}
/*
Test cases:

"owoztneoer"
"fviefuro"
"zeroonetwothreefourfivesixseveneightnine"
"fivesixxisvifeeigththgienineninenineeinn"

Outputs:

"012"
"45"
"0123456789"
"5566889999"
*/