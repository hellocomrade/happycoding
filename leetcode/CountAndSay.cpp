#include <sstream>
#include <string>

using namespace std;

//https://leetcode.com/problems/count-and-say/
/*
The count-and-say sequence is the sequence of integers with the first five terms as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

Example 1:

Input: 1
Output: "1"
Example 2:

Input: 4
Output: "1211"

Observations:
A lot of people dislike this one. I guess it's because the pattern is not intuitive for programmers...

What this does is to use 1 as root, then read it as 'one 1' and write it as '11', then the next iteration, you read
'11' as 'two one' and write it as '21' and keep going.
*/
class SolutionCountAndSay {
public:
	string countAndSay(int n) {
		stringstream ans("1");
		string str;
		int i = 1, cnt = 0, len = 0;
		while (i++ < n) {
			str = ans.str(), ans.str(""), len = str.length();
			for (int j = 0, cnt = 1; j < len; ++j) {
				if (j + 1 < len && str[j] == str[j + 1])
					++cnt;
				else {
					ans << cnt << str[j];
					cnt = 1;
				}
			}
		}
		return ans.str();
	}
};