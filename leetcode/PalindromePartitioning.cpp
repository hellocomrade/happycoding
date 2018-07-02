#include <string>
#include <vector>

using namespace std;

//https://leetcode.com/problems/palindrome-partitioning/
/*
131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

Example:

Input: "aab"
Output:
[
["aa","b"],
["a","a","b"]
]

Observations:

Such a complete search problem usualy takes advantage of backtracing. However, the output from given example confused me.
I don't understand why the first result starts with "aa"?! After running the example against "official solution", it's clear
that this is just an editing error. ["a","a","b"] should be the first element, which exactly implies the use of backtracing!

To check if a substring is a palindrome is trivial but the problem is that the same substring might be examined more than once.
Therefore, I put the previous check result in an array, which takes O(N^2) extra space. Such an array has 3 possible values on each
given [i, j] index range for a string:

- 0, substring[i, j] has not been examined yet;

- 1, substring[i, j] is a palindrome;

- 2, substring[i, j] is NOT a palindrome;

This idea comes from those palindrome problems solved by DP, a 2D array is used to store substring status.
*/
class SolutionPalindromePartitioning {
private:
	bool isPalindrome(const string &s, int l, int r, vector<vector<int> > &memo) {
		if (0 != memo[l][r]) return 1 == memo[l][r];
		int il = l, ir = r;
		while (il < ir) {
			if (s[il++] != s[ir--]) {
				memo[l][r] = 2;
				return false;
			}
			if (0 != memo[il][ir]) {
				memo[l][r] = memo[il][ir];
				return 1 == memo[l][r];
			}
		}
		memo[l][r] = 1;
		return true;
	}
	void aux(vector<vector<string>> &ans, vector<string> &ret, int retidx, const string &s, int l, int r, vector<vector<int> > &memo) {
		int len = (int)s.length();
		if (l > r) {
			ans.emplace_back(vector<string>(ret.begin(), ret.begin() + retidx));
			return;
		}
		for (int i = l; i <= r; ++i) {
			if (true == isPalindrome(s, l, i, memo)) {//cout <<s.substr(l, i - l + 1)<<endl;
				ret[retidx] = s.substr(l, i - l + 1);
				aux(ans, ret, retidx + 1, s, i + 1, r, memo);
			}
		}
	}
public:
	vector<vector<string>> partition(string s) {
		int len = (int)s.length();
		vector<vector<string> > ans;
		vector<string> ret(len);
		vector<vector<int> > memo(len, vector<int>(len, 0));
		this->aux(ans, ret, 0, s, 0, len - 1, memo);
		return ans;
	}
};
/*
Test cases:

"aab"
"bbbab"
"baab"
""
"a"
"ab"
"abc"
"aba"
"aaa"
"aaaa"
"aaabbbaba"
"jgojwjgjgorpehigopehgpoehrqgpoeqgpqirnopere"

Outputs:

[["a","a","b"],["aa","b"]]
[["b","b","b","a","b"],["b","b","bab"],["b","bb","a","b"],["bb","b","a","b"],["bb","bab"],["bbb","a","b"]]
[["b","a","a","b"],["b","aa","b"],["baab"]]
[[]]
[["a"]]
[["a","b"]]
[["a","b","c"]]
[["a","b","a"],["aba"]]
[["a","a","a"],["a","aa"],["aa","a"],["aaa"]]
[["a","a","a","a"],["a","a","aa"],["a","aa","a"],["a","aaa"],["aa","a","a"],["aa","aa"],["aaa","a"],["aaaa"]]
[["a","a","a","b","b","b","a","b","a"],["a","a","a","b","b","b","aba"],["a","a","a","b","b","bab","a"],["a","a","a","b","bb","a","b","a"],["a","a","a","b","bb","aba"],["a","a","a","bb","b","a","b","a"],["a","a","a","bb","b","aba"],["a","a","a","bb","bab","a"],["a","a","a","bbb","a","b","a"],["a","a","a","bbb","aba"],["a","a","abbba","b","a"],["a","aa","b","b","b","a","b","a"],["a","aa","b","b","b","aba"],["a","aa","b","b","bab","a"],["a","aa","b","bb","a","b","a"],["a","aa","b","bb","aba"],["a","aa","bb","b","a","b","a"],["a","aa","bb","b","aba"],["a","aa","bb","bab","a"],["a","aa","bbb","a","b","a"],["a","aa","bbb","aba"],["aa","a","b","b","b","a","b","a"],["aa","a","b","b","b","aba"],["aa","a","b","b","bab","a"],["aa","a","b","bb","a","b","a"],["aa","a","b","bb","aba"],["aa","a","bb","b","a","b","a"],["aa","a","bb","b","aba"],["aa","a","bb","bab","a"],["aa","a","bbb","a","b","a"],["aa","a","bbb","aba"],["aa","abbba","b","a"],["aaa","b","b","b","a","b","a"],["aaa","b","b","b","aba"],["aaa","b","b","bab","a"],["aaa","b","bb","a","b","a"],["aaa","b","bb","aba"],["aaa","bb","b","a","b","a"],["aaa","bb","b","aba"],["aaa","bb","bab","a"],["aaa","bbb","a","b","a"],["aaa","bbb","aba"]]
[["j","g","o","j","w","j","g","j","g","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","e","r","e"],["j","g","o","j","w","j","g","j","g","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","ere"],["j","g","o","j","w","j","gjg","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","e","r","e"],["j","g","o","j","w","j","gjg","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","ere"],["j","g","o","j","w","jgj","g","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","e","r","e"],["j","g","o","j","w","jgj","g","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","ere"],["j","g","o","jwj","g","j","g","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","e","r","e"],["j","g","o","jwj","g","j","g","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","ere"],["j","g","o","jwj","gjg","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","e","r","e"],["j","g","o","jwj","gjg","o","r","p","e","h","i","g","o","p","e","h","g","p","o","e","h","r","q","g","p","o","e","q","g","p","q","i","r","n","o","p","ere"]]
*/