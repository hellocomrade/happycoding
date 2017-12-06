#include <cassert>
#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/multiply-strings/
/*
43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

1. The length of both num1 and num2 is < 110.
2. Both num1 and num2 contains only digits 0-9.
3. Both num1 and num2 does not contain any leading zero.
4. You must not use any built-in BigInteger library or convert the inputs to integer directly.

Observations:
This is just not my question. Take a while to get first accepted and it (multiply1) takes too much unnecessary steps.
It does multiply first then add two intermediate multiply result together and the output will be waiting for the next multiply
result for addition. Bascially, mimic the way you do it manually.

The extra intermediate actions can actually be eliminated by allocating the space for final result up front, which takes
at most len(n1) + len(n2). Then do multiply accordingly, the outcome will be immediately added to the final result. Therefore,
we don't have to keep intermediate result any more.

Tricks:
- Carry over: it could occur twice. One on multiply, one on adding the carry-over from multiply to final result.
Plus, there could be extra carry-over left outside inner loop;
- Zero: given "10" and "00", the output should be "0" not "00". Extra routine is needed to skip those prepending '0's;

The first one can be simplified if using vector of int instead of char, which will ease the concern of carry-over. But you
will get a larger RAM profile.
*/
class SolutionMultiplyStrings {
private:
	int time(const string &n1, char n2, vector<char> &ans) {
		int carry = 0, tmp = 0, len = n1.length();
		for (int i = len - 1; i > -1; --i) {
			tmp = ((n1[i] - '0') * (n2 - '0') + carry);
			carry = tmp / 10, ans[len - i - 1] = '0' + tmp % 10;
		}
		if (carry > 0)ans[len] = '0' + carry;
		return carry > 0 ? len + 1 : len;
	}
	void addition(vector<char> &ans, int &lena, const vector<char> &buf, int lenb, int offset) {
		int carry = 0, i = offset, j = 0, tmp = 0;
		while (j < lenb) {
			tmp = (ans[i] - '0') + (buf[j++] - '0') + carry;
			carry = tmp / 10, ans[i++] = '0' + tmp % 10;
		}
		if (carry > 0)ans[i++] = '0' + carry;
		lena = i;
	}
public:
	string multiply(const string& num1, const string& num2) {
		int len1 = num1.length(), len2 = num2.length(), tmp1 = 0, tmp2 = 0, m = 0, carry = 0;
		vector<char> ans(len1 + len2, '0');
		for (int i = 0; i < len1; ++i) {
			carry = 0;
			for (int j = 0; j < len2; ++j) {
				m = len1 + len2 - i - 1 - j;
				//tmp1 and tmp2 can be combined, but I would rather keep it this way to understand what happened.
				//You could do though:
				/*
				tmp1 = (ans[m] - '0') + (num1[len1 - i - 1] - '0') * (num2[len2 - j - 1] - '0') + carry;
				ans[m] = '0' + tmp1 % 10;
				carry = tmp1 / 10;
				*/
				tmp1 = (num1[len1 - i - 1] - '0') * (num2[len2 - j - 1] - '0') + carry;
				tmp2 = ans[m] - '0' + tmp1 % 10;
				ans[m] = '0' + tmp2 % 10;
				carry = tmp2 / 10 + tmp1 / 10;
			}
			if (carry > 0)ans[m - 1] = '0' + carry;
		}
		tmp1 = 0;
		while (tmp1 < len1 + len2 && '0' == ans[tmp1])++tmp1;
		return tmp1 == len1 + len2 ? "0" : string(ans.begin() + tmp1, ans.end());
	}
	string multiply1(string num1, string num2) {
		int len1 = num1.length(), len2 = num2.length(), lena = 0, lenb = 0;
		vector<char> buf(len1 + 1, 0), ans(len1 + len2, '0');
		for (int i = len2 - 1; i > -1; --i) {
			lenb = this->time(num1, num2[i], buf);
			this->addition(ans, lena, buf, lenb, len2 - i - 1);
		}
		while (lena > 0 && '0' == ans[lena - 1])--lena;
		return 0 == lena ? "0" : string(ans.rend() - lena, ans.rend());
	}
};
void TestMultiplyStrings() {
	SolutionMultiplyStrings so;
	assert("5535" == so.multiply("123", "45"));
	assert("5535" == so.multiply("45", "123"));
	assert("100800" == so.multiply("140", "720"));
	assert("100940" == so.multiply("721", "140"));
	assert("0" == so.multiply("9133", "0"));
	assert("600" == so.multiply("10", "60"));
	assert("56393704714678875019052100" == so.multiply("1234567890", "45678901234567890"));
}