#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/integer-to-roman
/*
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.


https://en.wikipedia.org/wiki/Roman_numerals

Observations:
Since we have a farely small, finite numbers, we could do lookup table.

But, no fun on that at all! So, I did an interation version, which have to completely generate a mirror of the
final result and then reverse. Why? C++ doesn't have a good data structure allowing prepending.

Silly you! Why don't you start from the most significant bit? Here, is 1000! Then you don't have to do mirror and reverse!
Well, again, where is the fun :)
*/
class SolutionInteger2Roman {
public:
	string intToRoman(int num) {
		string r1[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
		string r2[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
		string r3[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
		string r4[] = { "", "M", "MM", "MMM" };
		stringstream ss;
		ss << r4[num / 1000] << r3[num % 1000 / 100] << r2[num % 1000 % 100 / 10] << r1[num % 1000 % 100 % 10];
		return ss.str();
	}
	string intToRoman1(int num) {
		unordered_map<int, char> dict = { { 1, 'I' },{ 5, 'V' },{ 10, 'X' },{ 50, 'L' },{ 100, 'C' },{ 500, 'D' },{ 1000, 'M' } };
		int i = 0, cnt = 0, n = 0;
		stringstream ss;
		while (num > 0) {
			i = num % 10;
			n = pow(10, cnt);
			if (i < 4)
				while (i-- > 0)ss << dict[n];
			else {
				if (9 == i)
					ss << dict[10 * n] << dict[n];
				else {
					while (i > 5 && i-- > 5)ss << dict[n];
					ss << dict[5 * n];
					if (4 == i)ss << dict[n];
				}
			}
			++cnt;
			num /= 10;
		}
		string ans = ss.str();
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
};