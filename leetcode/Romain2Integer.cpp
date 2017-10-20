#include <cassert>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/roman-to-integer/
/*
13. Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

Observations:
Since we have done 12, does it sound straightforward to come out a solution with mapping on every possible combination? Well, it's
actually, technically slower since you will have to try to match [1, 4] charcters on every move. That's romanToInt1. See the extra
check to make sure substr not out of range?

Then a more "straightforward" one is romanToInt2, just add them up, then if you ever see a smaller number ahead of a bigger one, such as XL, substract 2 times of smaller one.

Even fancier one: romanToInt2, do substraction as long as we see dict[s[i]] < dict[s[i + 1]]. In this setup, dict[s[len - 1]] will fall short. Therefore
we have to add it up after the loop, dict[s[len - 1]]. Besides, the loop will not be executed if len(s) == 1, in this case, we also need to append dict[s[len - 1]].
*/
class SolutionRoman2Integer {
private:
	unordered_map<char, int> dict = { { 'I', 1 },{ 'V', 5 },{ 'X', 10 },{ 'L', 50 },{ 'C', 100 },{ 'D', 500 },{ 'M', 1000 } };
	unordered_map<string, int> dict1 = { { "I", 1 },{ "II", 2 },{ "III", 3 },{ "IV", 4 },{ "V", 5 },{ "VI", 6 },{ "VII", 7 },{ "VIII", 8 },{ "IX", 9 },{ "X", 10 },{ "XX", 20 },{ "XXX", 30 },{ "XL", 40 },{ "L", 50 },{ "LX", 60 },{ "LXX", 70 },{ "LXXX", 80 },{ "XC", 90 },{ "C", 100 },{ "CC", 200 },{ "CCC", 300 },{ "CD", 400 },{ "D", 500 },{ "DC", 600 },{ "DCC", 700 },{ "DCCC", 800 },{ "CM", 900 },{ "M", 1000 },{ "MM", 2000 },{ "MMM", 3000 } };
public:
	int romanToInt(string s) {
		int len = s.size(), i = 0, ans = 0;
		while (i + 1 < len) {
			ans += dict[s[i]] < dict[s[i + 1]] ? -1 * dict[s[i]] : dict[s[i]];
			++i;
		}
		return ans + dict[s[len - 1]];
	}
	int romanToInt2(string s) {
		int len = s.size(), i = 0, ans = 0, prev = 0;
		while (i < len) {
			ans += dict[s[i]];
			if (prev < dict[s[i]])
				ans -= 2 * prev;
			prev = dict[s[i++]];
		}
		return ans;
	}
	int romanToInt1(string s) {
		int len = s.length(), i = 0, ans = 0;
		auto end = dict1.end(), itor = dict1.end();
		while (i < len) {
			for (int j = std::min(4, len - i + 1); j > 0; --j) {
				if (end != (itor = dict1.find(s.substr(i, j)))) {
					ans += itor->second;
					i += j;
					break;
				}
			}
		}
		return ans;
	}
};
void TestRoman2Integer() {
	SolutionRoman2Integer so;
	assert(647 == so.romanToInt("DCXLVII"));
	assert(1996 == so.romanToInt("MCMXCVI"));
}