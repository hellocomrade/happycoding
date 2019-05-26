#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/number-of-digit-one/
/*
233. Number of Digit One

Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

Example:

Input: 13

Output: 6

Explanation: Digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.

Observations:

I have to commit that this is a buring brain problem for me... The official "mathematical" solution is here:

https://leetcode.com/problems/number-of-digit-one/solution/

Mine is a bit different:

The first observation is: at any given position, if digit is 1, there should be a special handling for counting 1s.

Therefore:

- Precalculate count of 1 for all n-digit numbers and stored them in an array, with memo[0] = 1, memo[1] = 1, memo[2] = 20,
  which 0, 1, 2,... represents the number of digits. So, memo[2] = 20 means all numbers in 2 digits (10 to 99) have 20 occurrences of 1;
- Then examine the given number n from its most significant digit (leftmost). At any given position, say pos = i, the digit is k:
  - We can safely add 1s of all (i - 1) digits numbers first
  - If k > 1, the count shall include all extra 1s when 1 at position i, which is pow(10, i - 1);
  - If k == 1, only portion of extra 1s should be counted, they are: (m % j + 1), for example:
	given 156, 156 % 100 + 1 = 57, is the count. This includes number from 101 to 156 plus 100;
  - If k == 0, nothing needs to be done

So, this is how I actually count 1s, given number 2216, partition it to:

2000
+
 200
+
  10
+
   6

First counting numbers of 1s in 2000, this covers all 1s contributed from 1000 to 2000;

Then counting numbers of 200, this covers all 1s contributed from 100 to 200;

Next counting 10, this covers all 1s contributed from 10 to 16;

Finally 6, this covers all 1s contributed from 1 to 6;

The edge case is when numbers reach INT_MAX, therefore, the final answer and the memo array have to be with long type.
Also, non-positive integer should be ruled out up front.
*/
class SolutionNumberOfDigitOne {
public:
	int countDigitOne(int n) {
		if (1 > n) return 0;
		int digitCnt = 0, m = n;
		long ans = 0;
		while (m > 0) m /= 10, ++digitCnt;
		vector<long> memo(digitCnt + 1, 0);
		memo[0] = 0, m = n;
		for (int i = 1; i <= digitCnt; ++i) memo[i] = 10 * memo[i - 1] + pow(10, i - 1);
		for (int i = digitCnt, j = pow(10, digitCnt - 1), k = m / j; i > 0; m %= j, j /= 10, k = m / std::max(1, j), --i) {
			ans += k * memo[i - 1];
			if (1 < k) ans += pow(10, i - 1);
			else if (1 == k) ans += m % j + 1;
		}
		return static_cast<int>(ans);
	}
};
void TestNumberOfDigitOne() {
	SolutionNumberOfDigitOne so;
	so.countDigitOne(2147483647);
}
/*
Test cases:

-7
0
1
6
15
23
95
10
100
101
127
189
209
210
12345
9075736
54620761
690825727
1111111111
2147483647

Outputs:

0
0
1
1
8
13
20
2
21
23
61
129
141
142
8121
6440754
48818257
653520753
1111111120
-1323939513
*/