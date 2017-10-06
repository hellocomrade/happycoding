#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/letter-combinations-of-a-phone-number/
/*
17. Letter Combinations of a Phone Number

Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.



Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Observations:
A straightforward combination algorithm using backtracing.

Note, due to the implementation of the algirthm, the digits like "911" will not return anything even '9'
has mapped to "wxyz", since '1' doesn't have any mapping, the algorithm never reach the stage to collect the
result! This can be considered as a 'flaw', but leetcode has the same return...
*/
class SolutionLetterCombinationOfPhoneNumber {
private:
	vector<vector<char> > dict{ {},{},{ 'a', 'b', 'c' },{ 'd', 'e', 'f' },{ 'g', 'h', 'i' },{ 'j', 'k', 'l' },{ 'm', 'n', 'o' },{ 'p', 'q', 'r', 's' },{ 't', 'u', 'v' },{ 'w', 'x', 'y', 'z' } };
	void _aux(const string& digits, vector<string>& ans, string& str, int i) {
		if (i == digits.length()) {
			ans.push_back(string(str));
			return;
		}
		vector<char>& chars = this->dict[digits[i] - '0'];
		for (int m = 0; m < chars.size(); ++m) {
			str[i] = chars[m];
			this->_aux(digits, ans, str, i + 1);
		}
	}
public:
	vector<string> letterCombinations(string digits) {
		vector<string> ans;
		string str(digits.size(), ' ');
		this->_aux(digits, ans, str, 0);
		return ans;
	}
};