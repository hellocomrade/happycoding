#include <limits>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

//http://www.lintcode.com/en/problem/longest-common-prefix/
/*
Longest Common Prefix

Given k strings, find the longest common prefix (LCP).

Example
For strings "ABCD", "ABEF" and "ACEF", the LCP is "A"

For strings "ABCDEFG", "ABCEFG" and "ABCEFA", the LCP is "ABC"
*/
class SolutionLongestCommonPrefix {
public:
	/**
	* @param strs: A list of strings
	* @return: The longest common prefix
	*/
	string longestCommonPrefix(vector<string> &strs) {
		int len = strs.size();
		if (len == 0)return string("");
		if (1 == len)return strs[0];
		string prefix;
		int minLen = std::numeric_limits<int>::max();
		for (auto str : strs)
			minLen = std::min(minLen, (int)str.length());
		int pos = 0;
		char c = 0;
		while (pos < minLen)
		{
			c = strs[0][pos];
			for (int i = 1; i < len; ++i)
			{
				if (strs[i][pos] != c)
					return prefix;
			}
			prefix.push_back(c);
			++pos;
		}
		return prefix;
	}
};