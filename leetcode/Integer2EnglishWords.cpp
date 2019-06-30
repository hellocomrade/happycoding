#include <string>
#include <vector>
#include <sstream>
#include <functional>

using namespace std;

//https://leetcode.com/problems/integer-to-english-words/
/*
273. Integer to English Words

Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

Example 1:

Input: 123

Output: "One Hundred Twenty Three"

Example 2:

Input: 12345

Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:

Input: 1234567

Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Example 4:

Input: 1234567891

Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"

Hints:
- Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
- Group the number by thousands (3 digits). You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
- There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)

Observations:

This is an implementation problem. With hints, 3-digit-chunk is the catch. Yes, there are lots of edge cases, such as
"Zero" (display or not), space etc.

I took an approach different than most of solutions: instead of using numeric division, num is converted to string and split
into 3-digit-chunk with left padding 0 up to 2 if necessary. In order to have more fun, recursive build is used to build
and concatenate the result. It will take extra memory though.

I should redo this with numeric division approach.
*/
class SolutionInteger2EnglishWords {
public:
	string numberToWords(int num) {
		string ans, input = std::to_string(num);
		int len = (int)input.length();
		vector<string> digit2str0{ "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
		vector<string> digit2str1{ "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
		vector<string> digit2str2{ "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
		vector<string> digit2str3{ "", " Thousand", " Million", " Billion" };
		function<string(const string&&)> convert3 = [&](const string&& c3) -> string {
			stringstream ss;
			ss << ('0' != c3[0] ? digit2str0[c3[0] - '0'] + " Hundred" : "");
			if ('1' == c3[1]) {
				ss << ('0' != c3[0] ? " " : "") << digit2str1[c3[2] - '0'];
				return ss.str();
			}
			else ss << ('0' != c3[1] ? ('0' != c3[0] ? " " : "") + digit2str2[c3[1] - '0'] : "");
			ss << ('0' != c3[2] ? ('0' != c3[0] || '0' != c3[1] ? " " : "") + digit2str0[c3[2] - '0'] : "");
			return ss.str();
		};
		function<string(int, int, bool)> build = [&](int idx, int level, bool need_space) -> string {
			string str;
			if (-2 > idx) return "";
			if (-2 == idx) str = "00" + input.substr(0, 1);
			else if (-1 == idx) str = "0" + input.substr(0, 2);
			else str = input.substr(idx, 3);
			str = convert3(std::move(str));
			return build(idx - 3, level + 1, 0 < str.length()) + (0 < str.length() ? str + digit2str3[level] : "") + (true == need_space ? " " : "");
		};
		return 0 == num ? "Zero" : build(len - 3, 0, false);
	}
};
/*
Test cases:

105
23
16
6
0
1
12
123
12345
123456
1234567
12345678
123456789
1234567891
2147483647
1000010
1000000
2000500001

Outputs:

"One Hundred Five"
"Twenty Three"
"Sixteen"
"Six"
"Zero"
"One"
"Twelve"
"One Hundred Twenty Three"
"Twelve Thousand Three Hundred Forty Five"
"One Hundred Twenty Three Thousand Four Hundred Fifty Six"
"One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
"Twelve Million Three Hundred Forty Five Thousand Six Hundred Seventy Eight"
"One Hundred Twenty Three Million Four Hundred Fifty Six Thousand Seven Hundred Eighty Nine"
"One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
"Two Billion One Hundred Forty Seven Million Four Hundred Eighty Three Thousand Six Hundred Forty Seven"
"One Million Ten"
"One Million"
"Two Billion Five Hundred Thousand One"
*/