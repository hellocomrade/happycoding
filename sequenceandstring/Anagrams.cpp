#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

//http://www.lintcode.com/en/problem/anagrams/
/*
Anagrams

Given an array of strings, return all groups of strings that are anagrams.

Notice

All inputs will be in lower-case

Example
Given ["lint", "intl", "inlt", "code"], return ["lint", "inlt", "intl"].

Given ["ab", "ba", "cd", "dc", "e"], return ["ab", "ba", "cd", "dc"].
*/
class SolutionAnagrams {
public:
	/**
	* @param strs: A list of strings
	* @return: A list of strings
	*/
	vector<string> anagrams(vector<string> &strs) {
		// write your code here
		unordered_map<string, string> map;
		auto end = map.end();
		string dummy = "A";
		vector<string> anag;
		for (auto str : strs)
		{
			string tmp = str;
			std::sort(str.begin(), str.end());
			if (end == map.find(str))
				map[str] = tmp;
			else
			{
				if (map[str] != dummy)
				{
					anag.emplace_back(map[str]);
					map[str] = dummy;
				}
				anag.emplace_back(tmp);
			}
		}
		return anag;
	}
};
