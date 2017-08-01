#include <cstring>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/longest-substring-without-repeating-characters/
/*
3. Longest Substring Without Repeating Characters

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

Observation:
Scanning the array, mark the start point and use a hashtable to track the last occurrence of the current character.
If the index in hashtable for the current char is no less than the start point, we find a duplicate. We need to
check the nonrepeat count and move the cursor back to (start point + 1), which is the index we start the next scan.
and put the index of the current char into the hashtable to mark the location of the current char

If the index in hashtable for the current char is less than the start point, we know it shown up in the previous scan,
so, we simply overwrite it with the index of the current char into the hashtable to mark the location of the current char. Therefore,
we don't have to clean up the hashtable before each scan.

Yes, each time we find a duplicate, we have to backtrace, but overall, this is a linear algorithm

Ref: https://leetcode.com/problems/longest-substring-without-repeating-characters/solution/

A sliding window is an abstract concept commonly used in array/string problems. 
A window is a range of elements in the array/string which usually defined by the start and end indices, i.e. [i, j)[i,j) (left-closed, right-open). 
A sliding window is a window "slides" its two boundaries to the certain direction. For example, if we slide [i, j)[i,j) to the right by 11 element, then it becomes [i+1, j+1)[i+1,j+1) (left-closed, right-open).
*/
class SolutionLongestSubstringNoRepeatingChar {
public:
	int lengthOfLongestSubstring(string s) {
            size_t len = s.length(), start = 0, ans = 0;
            int memo[128] = {0};
            for(size_t i = 0; i < len; ++i) {
                start = std::max(start, (size_t)memo[s[i]]);
                ans = std::max(ans, i - start + 1);
                memo[s[i]] = i + 1;
            }
            return static_cast<int>(ans);
        }
	//This version makes more sense to me but it's slower coz using hashmap
	int lengthOfLongestSubstring1(string s) {
            size_t len = s.length(), start = 0, ans = 0;
            unordered_map<char, int> memo;
            auto end = memo.end();
            for(size_t i = 0; i < len; ++i) {
                start = std::max(start, (size_t)(end == memo.find(s[i]) ? 0 : memo[s[i]] + 1));
                ans = std::max(ans, i - start + 1);
                memo[s[i]] = i;
            }
            return static_cast<int>(ans);
        }
	//Slower, but more flexible
	int lengthOfLongestSubstring3(string s) {
		int len = s.length();
		if (len < 2)return len;
		unordered_map<char, int> map;
		auto end = map.end();
		int head = 0;
		long long cnt = 0, ans = 1;
		for (int i = 0; i < len; ++i)
		{
			auto ret = map.find(s[i]);
			if (ret == end || ret->second < head)
				++cnt;
			else if (ret->second >= head)
			{
				head = map[s[i]] + 1;
				ans = std::max(cnt, ans);
				cnt = i - map[s[i]];
			}
			map[s[i]] = i;
		}
		return std::max(cnt, ans);
	}
	//Faster by assuming all characters are in ASCII tables
	int lengthOfLongestSubstring2(string s) {
		int len = s.length();
		if (len < 2)return len;
		int map[256];
		memset(map, -1, sizeof(int) * 256);
		int head = 0, end = -1, ret;
		long long cnt = 0, ans = 1;
		for (int i = 0; i < len; ++i)
		{
			ret = map[s[i]];
			if (ret == end || ret < head)
				++cnt;
			else if (ret >= head)
			{
				head = ret + 1;
				ans = std::max(cnt, ans);
				cnt = i - ret;
			}
			map[s[i]] = i;
		}

		return std::max(cnt, ans);
	}
};
