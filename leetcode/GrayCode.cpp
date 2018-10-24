#include <vector>
#include <bitset>

using namespace std;

/*
89. Gray Code

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

Example 1:

Input: 2

Output: [0,1,3,2]

Explanation:

00 - 0

01 - 1

11 - 3

10 - 2

For a given n, a gray code sequence may not be uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence.

00 - 0

10 - 2

11 - 3

01 - 1

Example 2:

Input: 0

Output: [0]

Explanation: We define the gray code sequence to begin with 0.
A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
Therefore, for n = 0 the gray code sequence is [0].

Observations:

Leetcode categorized this as "Backtracing". That's what I thought at beginning. However, I did have
trouble to implement it coz the current trace is always based upon the most recent inserted answer.
By inserting a new answer, the tracing route is polluted...

The closest one I can find in disussion section is the following:

Recursively flipping bits without backtracing:

0 -> 0 --> 0 : 000
\
\	   --> 1 : 001
\
-> 1 -> 1 : 011
\
-> 0 : 010

1 -> 1 --> 0 : 110
\
\     --> 1 : 111
\
-> 0 -> 1 : 101
\
-> 0 : 100

It's a pretty smart way to construct the sequence recursively. Comparing with backtracing, the change
here on bitset array is NOT recoverable. By doing so, "values differ in only one bit" is fulfilled.
See grayCode1

A non-rescursive version is available on wiki, callsed Reflect-and-prefix, see grayCode0.

0+00
0+01
0+11
0+10
---
1+10
1+11
1+01
1+00

The idea is: the Gray Code array for N always contains the Gray Code array for (N - 1). The other half for GrayCode(N)
is made by adding 2^(N - 1) to the elements backwards in first half (the Gray Code for N - 1 actually) and push them onto the array.
Comparing between first half and second half, it's like mirroring the first half but with 1 as the prefix instead of 0.

The edge case is: when N = 0, the answer is [0].

The "standard" solution is in grayCode: i ^ (i >> 1), given i in [0, 2^n)
*/
class SolutionGrayCode {
public:
	vector<int> grayCode(int n) {
		vector<int> ans;
		for (int i = 0, k = 1 << n; i < k; ++i) ans.push_back(i ^ i >> 1);
		return ans;
	}
	/*
	Reflect-and-prefix method
	https://en.wikipedia.org/wiki/Gray_code#/media/File:Binary-reflected_Gray_code_construction.svg
	*/
	vector<int> grayCode0(int n) {
		vector<int> ans;
		ans.push_back(0);
		for (int i = 1, k = 1; i <= n; k = 1 << i++) {
			for (int j = ans.size() - 1; j > -1; --j)
				ans.push_back(ans[j] + k);
		}
		return ans;
	}
	//"Backtracing-like" without backtracing
	vector<int> grayCode1(int n) {
		bitset<32> bits;
		vector<int> ans;
		auto bt = [&bits, &ans](int i, const auto& fun) -> void {
			if (-1 == i) ans.push_back((int)bits.to_ulong());
			else {
				fun(i - 1, fun);
				bits.flip(i);
				fun(i - 1, fun);
			}
		};
		bt(n - 1, bt);
		return ans;
	}
};
void TestGrayCode() {
	SolutionGrayCode so;
	so.grayCode(2);
}