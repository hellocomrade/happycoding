#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;

//https://leetcode.com/problems/group-anagrams
/*
49. Group Anagrams

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
Note: All inputs will be in lower-case.

Observations:

This is actually a problem described in <Programing Pearls>. You could tackle this using two approaches:

1. Sort individual string and hash;

2. Count letters in each string, then encoding the letter with its count as key for hash;

Supposely, approach 1 will get O(NKlogK) given k is the lenght of string, approach 2 will get O(NK). But the results are shocking!

Approach 1 is 2 or 3 times faster than approach 2 in C++. Considering the fact, both cases use the default hash<std::string>, the difference 
is made on string handling...Since approach 2 has to build the encoded key on the fly using stringstream, it's very very slow...I am sure
if we compare these 2 approaches two using Java, results could be different.
*/
class SolutionGroupAnagrams {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, int> idxs;
        for(string& str : strs) {
            string t = str;
            std::sort(str.begin(), str.end());
            if(0 == idxs.count(str)) {
                ans.push_back(vector<string>());
                idxs.emplace(str, ans.size() - 1);
            }
            ans[idxs[str]].push_back(t);
        }
        return ans;
    }
    vector<vector<string>> groupAnagrams1(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, int> idxs;
        char charcnt[26] = {0};
        for(string& str : strs) {
            stringstream ss;
            for(char c : str)++charcnt[(int)c - 97];
            for(int i = 0; i < 26; ++i) {
                ss << (char)i << ':' << charcnt[i];
                charcnt[i] = 0;
            }
            string t = ss.str();
            if(0 == idxs.count(t)) {
                ans.push_back(vector<string>());
                idxs.emplace(t, ans.size() - 1);
            }
            ans[idxs[t]].push_back(str);
        }
        return ans;
    }
};
