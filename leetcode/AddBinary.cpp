#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/add-binary/
/*
67. Add Binary

Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"

Output: "100"

Example 2:

Input: a = "1010", b = "1011"

Output: "10101"

Observations:

Supposed to be a very straightforward question. My first try exactly simulates the addition logic if it's done by a human. Pay attention
on the carrier rules.

We could save couple lines of code by recognizing the fact that the value at each position is equal to (a[i] + b[j] + carry) % 2
and the next carry is equal to (a[i] + b[j] + carry) / 2, considering the fact the (a[i] + b[j] + carry) can be at most 3.

An extra move constructor and std::reverse are called to build the final result. It's possible to directly prepend to a string but
that's actually a performance penalty for C++ since string prepend is possibly implemented as an O(N) operation...
*/
class SolutionAddBinary {
public:
	string addBinary(string a, string b) {
		int lena = a.length(), lenb = b.length(), sum = 0;
		stringstream ans;
		for (int i = lena - 1, j = lenb - 1; i > -1 || j > -1; sum /= 2, --i, --j) {
			sum += i > -1 ? a[i] - '0' : 0;
			sum += j > -1 ? b[j] - '0' : 0;
			ans << sum % 2;
		}
		if (1 == sum) ans << 1;
		string s = std::move(ans.str());
		std::reverse(s.begin(), s.end());
		return s;
	}
	string addBinary1(string a, string b) {
		int lena = a.length(), lenb = b.length(), car = 0;
		stringstream ans;
		for (int i = lena - 1, j = lenb - 1, va = 0, vb = 0; i > -1 || j > -1; --i, --j) {
			va = i > -1 ? a[i] - '0' : 0;
			vb = j > -1 ? b[j] - '0' : 0;//cout <<va <<','<<vb<<endl;
			if (1 == va && 1 == vb) ans << car, car = 1;
			else if (0 == va && 0 == vb) ans << car, car = 0;
			else ans << (1 == car ? 0 : 1);
		}
		if (1 == car) ans << 1;
		string s = std::move(ans.str());
		std::reverse(s.begin(), s.end());
		return s;
	}
};
/*
Test cases:

"0"
"0"
"1"
"0"
"0"
"1"
"11"
"1"
"100"
"11101"
"100"
"101111110101"
"101111110101"
"100"
"101100100100100111101"
"111101011011010"

Outputs:

"0"
"1"
"1"
"100"
"100001"
"101111111001"
"101111111001"
"101101100010000010111"
*/