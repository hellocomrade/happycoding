#include <stack>
#include <string>
#include <sstream>

using namespace std;

//https://leetcode.com/problems/simplify-path
/*
71. Simplify Path

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:

- Did you consider the case where path = "/../"?
In this case, you should return "/".
- Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".

Observations:

By pointing out the the corner cases up front, leetcode simplifies the complexity of the problem!

Since a ".." will trigger a rewind, it appears stack is the best data struture which allows popping up from top.

I use two pointers here: pointer l indicates the index of the first character that is not '/', pointer r indicates the index of the next '/'.
Therefore, [l, r - 1] is the content between '/'s. We have to use while loop for finding l and r to clean up multiple slashes, such as "///a//b/"

After finding l and r, we will examine the result if r < len or '/' != path[r - 1]. The latter one is for the possible tail case, such as "/a/b/c".
'c' will not be picked up if we only check if r is less than len.

There are three cases for a valid l, r pair:

- path[l : r] == '.', do nothing, continue;

- path[l : r] == "..", we have to move one level up, which means remove the top element on the stack if stack is not empty;

- path[l : r] is something else, then we push (l, r - 1) as a pair onto stack. C++ is not very good on handing strings in terms of performance,
so I only store substring indexes;

After the linear loop, if stack is empty, we know that there are probably too many ".." in path and it shall be resolved as root, "/";

If stack is not empty, then the folder structure is stored up side down. I reverse it using another stack. Then popping up elements from the second
stack to restore the simplified path. Note that there should be no trailing slash.

I saw the code in discussion sections with two features:

1. Using std::getline, which functions like Java's split, by using getline with "/" as delimiter, you don't have to worry about multiple slashes,
but you will have to filter out empty string on your own. Besides, it generates too many temp strings...

2. Using string prepend to create the final result. Again, too many temp strings...It hurts not only space complexity but time complexity as well.
*/
class SolutionSimplifyPath {
public:
	string simplifyPath(string path) {
		int len = (int)path.length(), l = 0, r = 0;
		if (0 == len) return "";
		stack<std::pair<int, int> > stk1, stk2;
		stringstream ss;
		while (r < len) {
			while (r < len && '/' == path[r]) ++r;
			l = r;
			while (r < len && '/' != path[r]) ++r;
			if (r < len || '/' != path[r - 1]) {
				if (r - 1 == l && '.' == path[l]) continue;
				if (r - 1 == l + 1 && '.' == path[l] && '.' == path[l + 1]) {
					if (false == stk1.empty())
						stk1.pop();
				}
				else stk1.push(std::make_pair(l, r - 1));
			}
		}
		if (true == stk1.empty()) return "/";
		while (false == stk1.empty()) {
			stk2.push(stk1.top());
			stk1.pop();
		}
		while (false == stk2.empty()) {
			ss << '/' << std::move(path.substr(stk2.top().first, stk2.top().second - stk2.top().first + 1));
			stk2.pop();
		}
		return ss.str();
	}
};
/*
Test cases:

"/home/"
"/home"
"/a/b/c"
"/a/b/c/"
""
"/a/./b/../../c/"
"/a/../"
"/home//foo/"
"/abc/d././eg/wet/../../cke/./"
"/.././"
"////../.abc//gw/124/.//w/../dge/.//../././../////"
"/../..abc/.d//"
"/ab/cd../..f/g./.e/ww/./../c"

Outputs:

"/home"
"/home"
"/a/b/c"
"/a/b/c"
""
"/c"
"/"
"/home/foo"
"/abc/d./cke"
"/"
"/.abc/gw"
"/..abc/.d"
"/ab/cd../..f/g./.e/c"
*/