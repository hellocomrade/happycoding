#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/text-justification
/*
68. Text Justification

Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.

Example 1:

Input:

words = ["This", "is", "an", "example", "of", "text", "justification."]

maxWidth = 16

Output:

[
"This    is    an",
"example  of text",
"justification.  "
]

Example 2:

Input:

words = ["What","must","be","acknowledgment","shall","be"]

maxWidth = 16

Output:

[
"What   must   be",
"acknowledgment  ",
"shall be        "
]

Explanation: Note that the last line is "shall be    " instead of "shall     be",
because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified becase it contains only one word.

Example 3:

Input:

words = ["Science","is","what","we","understand","well","enough","to","explain",
"to","a","computer.","Art","is","everything","else","we","do"]

maxWidth = 20

Output:

[
"Science  is  what we",
"understand      well",
"enough to explain to",
"a  computer.  Art is",
"everything  else  we",
"do                  "
]

Observations:

String munipulation problem. Nothing fancy. If K words are in one line, there will be  K - 1 spots for
padding spaces. According to the rule, space shal lbe distributed as evenly as possible. For example,
if there are 12 padding spaces for 6 words, 5 spots shall be filled.

12 / 5 = 2

Then

[3, 3, 2, 2, 2] will be the numbers of spaces distributed among words from left to right.

This can be calcuated in two pieces:

base = 12 / 5 -- the number of spaces at least should have between two words;

extra = 12 % 5 = 2 -- the total number of extra spaces that should be assigned between words from left;
In order to do "as evenly as possible", extra will be taken by 1 in each spot until
extra is zero;

Two edge cases:

1. The last line, above padding rule doesn't count, 1 space between every two words;
2. One word occupies the entire line. This is due to my implementation, possible divide by zero,
In this case, no space is needed;

The outputs are not given because leetcode output truncates the spaces to 1 between every two words. So, it's meaningless
as results.
*/
class SolutionTextJustification {
public:
	vector<string> fullJustify(const vector<string>& words, int maxWidth) {
		int len = words.size();
		vector<string> ans;
		for (int i = 0, j = 0, k = 0, l = 0, cnt = 0, sps = 0, extra = 0; i <= len; ++i) {
			if (i < len && maxWidth >= cnt + words[i].length() + i - l) cnt += words[i].length();
			else {
				sps = (1 == i - l) ? 0 : ((len == i) ? 1 : (maxWidth - cnt) / (i - l - 1));
				extra = (1 == i - l || i == len) ? 0 : (maxWidth - cnt) % (i - l - 1);
				string str(maxWidth, ' ');
				auto itor = str.begin();
				for (j = l; j < i; ++j) {
					std::copy(words[j].begin(), words[j].end(), itor);
					if (j < i - 1) {
						itor += words[j].length();
						for (k = 0; k < sps; ++k) *itor++ = ' ';
						if (extra-- > 0) *itor++ = ' ';
					}
				}
				ans.push_back(std::move(str));
				l = i, cnt = words[i].length();
			}
		}
		return ans;
	}
};
void TestTextJustification() {
	SolutionTextJustification so;
	so.fullJustify(vector<string> {"abc", "a"}, 3);
	so.fullJustify(vector<string> {"This", "is", "an", "example", "of", "text", "justification."}, 16);
}
/*
Test cases:

["ab"]
5
["a"]
1
["ab", "a"]
4
["abc", "a"]
3
["abc","def"]
17
["This", "is", "an", "example", "of", "text", "justification."]
16
["What","must","be","acknowledgment","shall","be"]
16
["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]
20

Outputs:

*/