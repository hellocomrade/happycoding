#include <string>

using namespace std;

//https://leetcode.com/problems/rotate-string/
/*
796. Rotate String

We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to the rightmost position. For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. Return True if and only if A can become B after some number of shifts on A.

Example 1:

Input: A = 'abcde', B = 'cdeab'

Output: true

Example 2:

Input: A = 'abcde', B = 'abced'

Output: false

Note:

A and B will have length at most 100.

Observations:

This is an interview question that has been floating around for a decade! Everyone knows the trick is to concatenate A
with itself, then check if B is a substring of this newly constructed string.

But, I'd like to point out the default O(N^2) solution which literally scans all possibility has some delicate design on how
to index array element with the index number that is actually larger than len - 1 using Modulus Operator.

The official solution, as we speak, has not been completed yet, suggested:

Other than brute force, we talked about above, there are two other solutions:

- Rolling hash

- KMP
*/
class SolutionRotateString {
public:
	//O(N) time and O(N) space, thanks for string.find() impl in O(N), probably a KMP
	bool rotateString(string A, string B) {
		string t = A + A;
		return A.length() == B.length() && string::npos != t.find(B);
	}
	//O(N^2) time and O(1) space
	bool rotateString1(string A, string B) {
		int len = (int)A.length();
		if (B.length() != len)return false;
		bool ans = false;
		for (int i = 0; i < len && false == ans; ++i) {
			ans = true;
			for (int j = 0; j < len && true == ans; ++j)
				if (B[(i + j) % len] != A[j]) ans = false;
		}
		return ans;
	}
};
/*
Test cases:

"abcde"
"cdeab"
"abcde"
"abced"
""
""
"abc"
"def"
"ab"
"b"

Outputs:

true
false
false
false
false
*/