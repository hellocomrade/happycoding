#include <cassert>
#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/restore-ip-addresses
/*
93. Restore IP Addresses

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

Example:

Input: "25525511135"

Output: ["255.255.11.135", "255.255.111.35"]

Observations:

Well, since it asks for all possible valid IPs, doing a 4 tiers loop should work. But, as a leetcode person, the first reaction is always: backtracing!

Backtracing can be done using a template. Allways the same approach. Variations here including the concern around C++ temp strings are:

- No string concatenation, I use a vector with length of 16, which is the maximum length for a valid IP;

- How to validate IP segment, which is in range of [0, 255]. I chose the silly way, blacklist all invalid cases;

- Deal with more than one leading zeros, such as "000123", you can't do 00.0.1.23;

- Do we need to recover/erase previous selection after the recursion? Here, it's not necessary. Overwritting is just fine as long as
it starts from the shortest possible segment to longest;

- Can we make recursion stop earlier?
1. Input argument string shall between [4, 12];
2. If the K segment, K in [1, 4] is reached and there are more than (3 * (5 - K)) characters left, it's no need to continue;
3. Can we find a lower bound? idx == length of the input, but K is less than 5;
*/
class SolutionRestoreIPAddresses {
private:
	bool isValid(const string &s, int start, int end) {
		if (end != start && '0' == s[start]) return false;
		else if (end - start > 1) {
			if ('2' < s[start]) return false;
			if ('2' == s[start] && '5' < s[start + 1]) return false;
			if ('2' == s[start] && '5' == s[start + 1] && '5' < s[end]) return false;
		}
		return true;
	}
	void aux(vector<string> &ans, vector<char> &str, const string &s, int idx, int segno, int cur) {
		int len = (int)s.size();
		if (len - idx > 3 * (5 - segno) || (5 > segno && len == idx)) return;
		if (5 == segno) {
			if (len == idx) ans.emplace_back(std::move(string(str.begin(), str.begin() + cur - 1)));
			return;
		}
		for (int i = idx, c = cur; c - cur < 3 && i < len; ++c, ++i) {
			if (false == this->isValid(s, idx, i)) continue;
			str[c] = s[i];
			str[c + 1] = '.';
			this->aux(ans, str, s, i + 1, segno + 1, c + 2);
		}
	}
public:
	vector<string> restoreIpAddresses(string s) {
		int len = (int)s.size();
		vector<string> ans;
		if (len > 3 && len < 13) {
			vector<char> str(16, 0);
			this->aux(ans, str, s, 0, 1, 0);
		}
		return ans;
	}
};
void TestRestoreIPAddresses() {
	SolutionRestoreIPAddresses so;
	vector<string> ret = so.restoreIpAddresses("25525511135");
	assert(2 == ret.size() && "255.255.11.135" == ret[0] && "255.255.111.35" == ret[1]);
	ret = so.restoreIpAddresses("0000");
	assert(1 == ret.size() && "0.0.0.0" == ret[0]);
}
/*
Test cases:

"25525511135"
"0000"
"123234"
"12325678"
"012315178"
"12"
"123123123123123"
"000000"
"123210235"

Outputs:

["255.255.11.135","255.255.111.35"]
["0.0.0.0"]
["1.2.3.234","1.2.32.34","1.23.2.34","1.23.23.4","1.232.3.4","12.3.2.34","12.3.23.4","12.32.3.4","123.2.3.4"]
["1.232.56.78","12.32.56.78","123.2.56.78","123.25.6.78","123.25.67.8"]
["0.123.15.178","0.123.151.78"]
[]
[]
[]
["1.23.210.235","1.232.10.235","1.232.102.35","12.3.210.235","12.32.10.235","12.32.102.35","123.2.10.235","123.2.102.35","123.21.0.235","123.210.2.35","123.210.23.5"]
Runtime: 2 ms
*/