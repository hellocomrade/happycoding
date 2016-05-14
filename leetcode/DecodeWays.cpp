//https://leetcode.com/problems/decode-ways/
/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

Observation:
At beginning, I thought I could solve this by divide and conque even after I peeked the hint and knew it's
supposed to be DP.

General concern are:
1. How 0 should be treated? '01' is an invalid case, '20' is another invalid one. You could check if the
sequence is valid in O(N)
2. Other invalid cases since valid codes are in [1, 26]. So, we may have '27', but '17' is vaid. You could
get this done in O(1)

DP or DC:
DC failed me. Even dividing the sequence to half-half seems to be promising, we could have two halfs solved,
mutiply them, then check the edges, they are the last one in the first half and the second one in the second half. If they
form a valid code, we do plus 1. Wait! It's wrong. Given, "3141592", it is partitioned into "3141" and "592"
"3141" results in 2
and
"592" results in 1

since 1, 5 is valid (15), we would have 2*1 + 1 =3, but the correct answer is 4! This is due to the fact
that 14 in 3141 is valid and therefore influeneces the final count. Since DC would never be able to even
examine "314" as a whole, we will not be able to solve this using DC

DP, on the other hand, can solve this in O(N) using O(N) extra space, classic CountEndHere stuff.
Given memo[0] and memo[1] figured out, starting from index i in [2, len - 1]
if str[i] is not 0:
if str[i - 1]str[i] is in [11, 19] or [21, 26]:
memo[i] = memo[i - 2] + memo[i - 1];  memo[i - 2] represents the count taking str[i - 1]str[i] as a whole,
memo[i - 1] is counting str[i] as an individual code.
otherwise:
memo[i] = memo[i - 1]
if str[i] is 0:
memo[i] = memo[i - 2]; since this is the only way to make a 0-valid sequence valid
*/
extern "C"{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
	static inline int noMoreThan26(char l, char h)
	{
		if (l > '0' && ((l == '1' && h != '0') || (l == '2' && h > '0' && h < '7')))
			return 1;
		else
			return 0;
	}
	static int check0(char *s)
	{
		char last = '\0';
		while (0 != *s)
		{
			if (*s == '0' && last != '1' && last != '2')
				return -1;
			else
				last = *s++;
		}
		return 0;
	}
	int numDecodings(char* s) {
		int len = strlen(s);
		if (len > 0 && 0 == check0(s))
		{
			long long *memo = (long long*)malloc(sizeof(long long) * len);
			memo[0] = 1;
			memo[1] = memo[0] + noMoreThan26(s[0], s[1]);
			for (int i = 2; i < len; ++i)
			{
				if ('0' != s[i])
				{
					if (1 == noMoreThan26(s[i - 1], s[i]))
						memo[i] = memo[i - 1] + memo[i - 2];
					else
						memo[i] = memo[i - 1];
				}
				else
					memo[i] = memo[i - 2];
			}
			return memo[len - 1];
		}
		else
			return 0;
	}
	void TestDecodeWays()
	{
		printf("Expect 0: %d\n", numDecodings(""));
		printf("Expect 0: %d\n", numDecodings("0"));
		printf("Expect 1: %d\n", numDecodings("10"));
		printf("Expect 0: %d\n", numDecodings("01"));
		printf("Expect 0: %d\n", numDecodings("1603"));
		printf("Expect 1: %d\n", numDecodings("1203"));
		printf("Expect 2: %d\n", numDecodings("1210"));
		printf("Expect 2: %d\n", numDecodings("17"));
		printf("Expect 1: %d\n", numDecodings("27"));
		printf("Expect 1: %d\n", numDecodings("37"));
		printf("Expect 4: %d\n", numDecodings("3141592"));
		printf("Expect 8: %d\n", numDecodings("3141592653589"));
		printf("Expect 6: %d\n", numDecodings("793238461234"));
		printf("Expect 48: %d\n", numDecodings("3141592653589793238461234"));
	}
}