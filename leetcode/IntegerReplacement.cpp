#include <algorithm>

using namespace std;

//https://leetcode.com/problems/integer-replacement
/*
397. Integer Replacement

Given a positive integer n and you can do operations as follow:

If n is even, replace n with n/2.
If n is odd, you can replace n with either n + 1 or n - 1.
What is the minimum number of replacements needed for n to become 1?

Example 1:

Input:
8

Output:
3

Explanation:
8 -> 4 -> 2 -> 1

Example 2:

Input:
7

Output:
4

Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1

Observations:

This is a fairly interesting problem. It can be solved by either greedy or recursion. I saw quite a few people claim this is a DP.
I don't get it...even DP is an option, it won't out perform other approachs giving such a small scale, log(INT_MAX).

Let's examine the problem first, given any positive interger n in binary, say 1001101 or 1001100 one may discover:

In order to descend to 1, divide a even number by 2 is equal to right shift by 1, which will decrease the number of digits immediately.
However, if n is odd, adding or substracting by 1 will only turns n to an even number, no desecnt at all. In other words, for an odd number,
it will take 2 steps to remove the most insignificant digit. Even number only needs 1 step (by dividing n by 2).

The problem asks for the minimum step for descent, obviously the difference is when n is odd: whether increasing by 1 or decreasing by 1?

Recursive solution integerReplacement0 is kind of brutal, it exactly simulates the problem:

- If n is even, return 1 + integerReplacement(n / 2);

- If n is odd, return 2 + MIN(integerReplacement((n - 1) / 2), integerReplacement((n + 1) / 2));

One may notice the actual implemention is in aux, the issue is the edge case on 2147483647, which is (2^31 - 1). If one keeps all operations
restrictly in positive integer scope, it will take 33 steps from 2147483647 to 1. However, if the scope can be extended to size_t, aka, unsigined int,
one can add 1 to 2147483647, which gives 2^31, and then keep dividing it by 2 for 31 times to get to 1, total 32 steps.

Since leetcode "thinks" 32 is the correct answer, n has to be casted to size_t before any operation just for covering this edge case...

Another approach for this problem is greedy: the more tailing zero in n's binary form, the faster the descent to 1

- If n is even, definitely dividing by 2;

- If n is odd, things got a bit complicated:

1. If (n - 1) is a power of 2 (the fastest descent), n shall be substracted by 1;
2. Otherwise, both (n - 1) and (n + 1) shall be examined. The one with more tailing zero will win. Checking tailing zero takes
constant time given any size_t (at most 31 steps).
3. One may ask, what if (n + 1) is a power of 2? Well, it's a bit vague: for 2147483647, (n + 1) is the way to go; but for 3,
(n + 1) will waste steps, (n - 1) is correct, since 3 + 1 = 4, 3 - 1 = 2. So, in order to take (n + 1), whether (n - 1) is
a power of 2 shall be checked first, which is done in item 1. Considering the fact item 2 will cover the case that (n + 1)
is a power of 2, it's not necessary to have a separated branch for it.
*/
class SolutionIntegerReplacement {
private:
	int aux(size_t n) {
		if (1 == n) return 0;
		if (0 == (n & 1)) return 1 + aux(n / 2);
		else return 2 + std::min(aux((n + 1) / 2), aux((n - 1) / 2));
	}
public:
	int integerReplacement(int n) {
		int ans = 0;
		size_t m = n;
		auto tailingZeros = [](size_t m) {
			int cnt = 0;
			while (0 == (m & 1)) m >>= 1, ++cnt;
			return cnt;
		};
		while (1 != m) {
			if (1 == (m & 1)) {
				if (0 == ((m - 1) & (m - 2))) --m;
				//else if (0 == ((m + 1) & m)) ++m;
				else m = tailingZeros(m - 1) >= tailingZeros(m + 1) ? m - 1 : m + 1;
			}
			else m >>= 1;
			++ans;
		}
		return ans;
	}
	int integerReplacement0(int n) {
		return this->aux(n);
	}
};
/*
Test cases:

2147483647
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
101
235979
9797971515
1000000000
6230976927
2876267
52870762
5877962
12341234

Outputs:

32
0
1
2
2
3
3
4
3
4
4
5
4
5
5
5
4
5
5
6
5
9
26
38
38
43
29
35
31
29
*/