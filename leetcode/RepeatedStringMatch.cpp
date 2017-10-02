#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/repeated-string-match/
/*
686. Repeated String Match

Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

Note:
The length of A and B will be between 1 and 10000.

Observations:
It appears there should be a upper limit of such a string built upon A and is able to cover a substring as B.

For exmple, given, A = "abc", B = "abcabc", we will need to have 2 * A = "abcabc", the newly built string seems to be len(B) / len(A);

Given, A = "abc", B = "bcabca", however the newly built string should be 3 * A = "abcabcabc", that is len(B) / len(A) + 1!

So, what's the deal? Let's change the direction a bit: in order to ensure B is a substring of N * A (N >= 1), B's first character
has to be one charcter in A, A[i] ( 0 <= i < len(A)), then starting from there, B keeps matching with this newly built string...

If we first make the newly built string N * A at least as long as B, len(N * A) >= len(B), ceiling of len(B) / len(A), then B could either be covered or we only
need to preprend one more A on to N * A to make (N + 1) * A to cover all cases if B could ever be a substring.

Given M = len(A), N = len(B), this will requires O(M + N) space and O(N * (M + N)) time if the searching of substring
is a brute force. However, most of programming lanague implements this using linear algorithm as KMP, so the practical
time complexity is O(M + N)
*/
class SolutionRepeatedStringMatch {
public:
	int repeatedStringMatch(string A, string B) {
		int alen = A.size(), blen = B.size();
		int cnt = blen / alen + (0 == blen % alen ? 0 : 1);
		stringstream ss;
		for (int i = 0; i < cnt; ++i)ss << A;
		for (int i = 0; i < 2; ++i) {
			if (string::npos != ss.str().find(B))return cnt + i;
			ss << A;
		}
		return -1;
	}
	/*
	This is the brute force version, takes O(M * N) time. It scans every A[i] as the starter to
	match B, then rewind index i if i == M - 1.
	*/
	int repeatedStringMatch1(string A, string B) {
		int alen = A.size(), blen = B.size(), ans = numeric_limits<int>::max(), cnt = 0, j = 0, k = 0;
		for (int i = 0; i < alen; ++i)
		{
			cnt = 0, j = 0, k = i;
			while (k < alen && j < blen && A[k] == B[j]) {
				if (k == alen - 1) {
					k = -1;
					++cnt;
				}
				++k, ++j;
			}
			if (blen == j)
				ans = std::min(cnt + (0 == k ? 0 : 1), ans);
		}
		return ans == numeric_limits<int>::max() ? -1 : ans;
	}
};