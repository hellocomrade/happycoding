#include <cassert>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/longest-absolute-file-path
/*
388. Longest Absolute File Path

Suppose we abstract our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir

subdir1

subdir2

file.ext

The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir

subdir1

file1.ext

subsubdir1

subdir2

subsubdir2

file2.ext

The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system. If there is no file in the system, return 0.

Note:
- The name of a file contains at least a . and an extension.
- The name of a directory or sub-directory will not contain a ..
- Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path aaaaaaaaaaaaaaaaaaaaa/sth.png.

Observations:

Not much to say, really, a simulation problem. Scanning through the input and tracking the folder levels appear to be
the right way to go. One may also split the input by '\n' first instead of scanning through.

My original solution requires a statck and track current path length based upon the stack. Actually, it's not necessary.
A plain vecto will do. The most recent path length at each dir level can be tracked using an array. One can figure out current
dir level by counting the number of '\t' and the current path length sum can be calculated at the same time.

If a '\n' is met, depending on current level is a file or dir, one can either try to update longest path or put path length at current
level onto the array.
*/
class SolutionLongestAbsoluteFilePath {
public:
	int lengthLongestPath(const string input) {
		int len = (int)input.length(), ans = 0;
		bool isFile = false;
		vector<int> pathMemo;
		for (int i = 0, l = 0, level = 0, pathlen = 0; i <= len; ++i) {
			if (i == len) {
				if (true == isFile) ans = std::max(ans, pathlen + i - l + level);
				continue;
			}
			switch (input[i]) {
			case '\t':
				//For "dir.txt\n\t", level is 0 and pathMemo is empty, therefore
				//extra check has to be done.
				pathlen += level < (int)pathMemo.size() ? pathMemo[level++] : 0, ++l;
				break;
			case '\n':
				if (true == isFile)
					ans = std::max(ans, pathlen + i - l + level);
				else {
					if (level < (int)pathMemo.size()) pathMemo[level] = i - l;
					else pathMemo.push_back(i - l);
				}
				level = pathlen = 0, l = i + 1;
				isFile = false;
				break;
			case '.':
				isFile = true;
				break;
			}
		}
		return ans;
	}
	int lengthLongestPath0(const string& input) {
		int len = (int)input.length(), i = 0, pi = 0, level = 0, t = 0, path = 0, ans = 0;
		bool isFile = false;
		stack<std::pair<int, int>> stk;
		while (i < len) {
			while (i < len && '\n' != input[i]) {
				if ('.' == input[i]) isFile = true;
				++i;
			}
			t = i + 1;
			while (t < len && '\t' == input[t]) ++t;
			while (false == stk.empty() && level <= stk.top().second) {
				path -= stk.top().first;
				stk.pop();
			}
			if (true == isFile)
				ans = std::max(ans, path + i - pi);
			else {
				stk.push(std::make_pair(i - pi + 1, level));
				path += stk.top().first;
			}
			isFile = false;
			level = t - i - 1;
			pi = i = t;
		}
		return ans;
	}
};
void TestLongestAbsoluteFilePath() {
	SolutionLongestAbsoluteFilePath so;
	assert(7 == so.lengthLongestPath("dir.txt\n\t"));
	assert(20 == so.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"));
	assert(37 == so.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext\ndirgageagewgewaegeqqqhqehqhqeyqeyqhh."));
}
/*
Test cases:

"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext\ndirgageagewgewaegeqqqhqehqhqeyqeyqhh."
"dir\n\tsubdir1\n\t\tsubdir2\n\t\tsubdir3\n\t\t\tfile123.abc\n\tsubdir4\n\t\tfile1234.abcd"
"dir"
""
"dir.txt"
"dir.txt\n\t"
"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"

Outputs:

20
37
31
0
0
7
7
20
*/