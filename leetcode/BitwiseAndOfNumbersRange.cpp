//https://leetcode.com/problems/bitwise-and-of-numbers-range/
/*
201. Bitwise AND of Numbers Range

Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

Example 1:

Input: [5,7]

Output: 4

Example 2:

Input: [0,1]

Output: 0

Observations:

My naive solution, rangeBitwiseAnd1, just a bit better than brute force by narrowing AND operation
in range of 2^k - 2^(k - 1), which is still sub-linear, not to mention all kind of edge cases it may
have to deal with, such as integer overflow...

The trick is: bitwise AND of all numbers in range [m, n] is the common bits of both m and n from MSB end.

m = 1001

n = 1101

common bits from left is 1 after 3 times of right shifts, then move 1 << 3 as the answer.

the last 3 bits are numbers between 001 to 101. AND among them will only generate 0.

The implementation is in rangeBitwiseAnd0. It runs in constant time.

rangeBitwiseAnd might be a more elegant solution. The approach it takes is probably inspired by
the classic "count bits in a number". Instead of getting count, the final result of n & (n - 1) is the answer.

The rational is: by removing the rightmost 1 bit from n, lots of unnecessary AND will be skipped.

For example:

m = 100001
n = 110100

n & (n - 1): 110100 & 110011 = 110000

Again: 110000 & 101111 = 100000

At this moment n = 100000 < m, the common left bits have been found. It runs in constant time as well.
*/
class SolutionBitwiseAndOfNumbersRange {
public:
	// Elegant
	int rangeBitwiseAnd(int m, int n) {
		while (m < n) n = n & (n - 1);
		return n;
	}
	// Straightforward
	int rangeBitwiseAnd0(int m, int n) {
		int cnt = 0;
		while (m != n) m >>= 1, n >>= 1, ++cnt;
		return n << cnt;
	}
	// Naive
	int rangeBitwiseAnd1(int m, int n) {
		if (0 == n) return 0;
		int bcnt = 0;
		long k = n, mm = m;
		for (; 0 != k; ++bcnt) k >>= 1;
		k = 1 << --bcnt;
		if (m < k) return 0;
		k = mm++;
		while (mm <= n) k &= mm++;
		return k;
	}
};
/*
Test cases:

0
0
1
1
2
2
3
3
2
3
2147483646
2147483647
5
7
0
1
1
2147483647
17
38
1254235
57357838
105
127
59
60
50
60
27
31
17
31

Outputs:

0
1
2
3
2
2147483646
4
0
0
0
0
96
56
48
24
16
*/