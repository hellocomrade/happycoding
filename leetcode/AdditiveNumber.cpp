#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>

using namespace std;

//https://leetcode.com/problems/additive-number/
/*
306. Additive Number

Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Example 1:

Input: "112358"

Output: true

Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8.

			 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

Example 2:

Input: "199100199"

Output: true

Explanation: The additive sequence is: 1, 99, 100, 199.

			 1 + 99 = 100, 99 + 100 = 199

			 Follow up:

How would you handle overflow for very large input integers?

Observations:

It appears to be a DP or BT problem. I thought it's BT since only Yes or No is needed as answer. However,
by playing with it for a while, I had a hard time to establish any overlapped optimized sub-problem. Therefore,
BT is the way to go.

Edge case is mentioned in decription: a valid number should not have leading zero. So, it could be a condition for BT
for early termination.

Early termination is always a key design question for any back tracing problem. Due the large number of recursion,
any early termniation could greatly improve the performance. Other than no leading zero for a number, here are
one more condition for early termination:

At any moment, if current the number of digits of current sum is greater than remaining digits in num, there is
no need to continue. This is implemented in function "bt" in a very straightforward way. It's also implemented
in main function in a different way (could be the same approach, but I took a different view there).

In main function, the routine to start the BT is based upon the description that the first two numbers of given
combination in num don't have to follow Fibonacci sequence (I can't figure out a way to put this piece into function "bt").
Therefore, a 2 level loop is needed to pick first 2 seeds, val1 and val2. In this case, if
MAX(len(val1), len(val2) > len(num) - len(val1) - len(val2), there is no need to start BT at all since remaining
digits in num are not enough to reach the number of digits for (val1 + val2). For exampe, "12345",
if val1 = "12", val2 = "34", no need to go BT coz remaining digit '5' is not long enough to hold the addition
of val1 and val2. By doing so, we don't have to calculate val1 + val2 unless it's necessary. This can partially
answer the follow-up question: what if input integer is very large...

The exit condition of BT is: if startIndex is pointing to the end plus 1 of num.

For BT itself, arguments sent to the recursive function are: the previous val, previous sum and the start index
for calculating the possible value which will be compared with previous sum. The BT continues only if previous sum
is equal to current calculated value and this calculated value plus previous val will be the new sum for next recursion and new previous
value is the calcuate value.
*/
class SolutionAdditiveNumber {
public:
	bool isAdditiveNumber(string num) {
		bool ans = false;
		int len = (int)num.size();
		unordered_map<string, long long> memo;
		function<long long(int, int)> substr2ll = [&](int start, int sz) -> long long {
			long long ans = 0;
			for (int i = start, j = start + sz; i < j; ++i) ans = 10 * ans + (int)(num[i] - '0');
			return ans;
		};
		function<int(long long)> digitCount = [](long long n) {
			if (0 == n) return 1;
			int ans = 0;
			while (n > 0) ++ans, n /= 10;
			return ans;
		};
		function<bool(long long, long long, int)> bt = [&](long long prevVal, long long sum, int startIdx) -> bool {
			if (len == startIdx) return true;
			int dc = digitCount(sum);
			if (dc > len - startIdx || (1 < dc && '0' == num[startIdx])) return false;
			long long val = 0;
			string key = std::to_string(startIdx) + "," + std::to_string(dc);
			if (0 == memo.count(key)) memo.emplace(key, substr2ll(startIdx, dc));
			val = memo[key];
			return (val == sum) ? bt(val, val + prevVal, startIdx + dc) : false;
		};
		long long val1, val2;
		for (int i = 1; false == ans && i < len; ++i) {
			if ('0' == num[0] && 1 < i) break;
			val1 = substr2ll(0, i);
			for (int j = 1; false == ans && std::max(i, j) <= len - i - j; ++j) {
				if ('0' == num[i] && 1 < j) break;
				val2 = substr2ll(i, j);
				ans = bt(val2, val1 + val2, i + j);
			}
		}
		return ans;
	}
};
/*
Test cases:

"112358"
"1101121"
"199100199"
"00000"
"123"
"1203"
"01001"
"12587"
"459729759407123"

Outputs:

true
true
true
true
true
false
false
false
false
*/