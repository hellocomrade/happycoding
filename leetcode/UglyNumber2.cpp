#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/ugly-number-ii
/*
264. Ugly Number II

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number, and n does not exceed 1690.

Observations:
Without peeking the hints, I was addicted in the idea of using Sieve of Eratosthenes to solve this one. But ugly numbers
are way less than prime numbers, so I have to use bitset<INT_MAX>, which exceeds the memory limit...and of course, time
complexity is ugly as well...

After the peek, I knew that ugly number list shall be built on the fly in one run in increasing order starting from 1:

[1] <-- 2 * 1, 3 * 1, 5 * 1
Since 2 is the smallest one, put 2 on ugly number list and factor 2 is going to multiply the second number on ugly number list.
Why so? coz 2 * 1 has just been pushed onto the list already, no duplicates!

[1, 2] <-- 2 * 2, 3 * 1, 5 * 1
3 * 1 is the winner! Adding 3 * 1 to the list and bump up 3's mate to the second in the list, which is 2

[1, 2, 3] <-- 2 * 2, 3 * 2, 5 * 1
2 * 2 is the winner.

[1, 2, 3, 4] <-- 2 * 3, 3 * 2, 5 * 1
5 * 1 is the winner

[1, 2, 3, 4, 5] <-- 2 * 3, 3 * 2, 5 * 2
In this case both 2 * 3 and 3 * 2 win, then we move 2's next ugly number to 5 and 3's next ugly number to 3

[1, 2, 3, 4, 5, 6] <-- 2 * 4, 3 * 3, 5 * 2
2 * 4 is the winner!

...

O(N) time and O(N) space
*/
class Solution {
public:
	int nthUglyNumber(int n) {
		if (n < 1)return 0;
		vector<int> uglies(n, 0), indexes(3, 0);
		int c2, c3, c5, minc, cnt = 1;
		uglies[0] = 1;
		while (cnt < n) {
			c2 = uglies[indexes[0]] * 2;
			c3 = uglies[indexes[1]] * 3;
			c5 = uglies[indexes[2]] * 5;
			minc = std::min(c2, std::min(c3, c5));
			if (c2 == minc)++indexes[0];
			if (c3 == minc)++indexes[1];
			if (c5 == minc)++indexes[2];
			uglies[cnt++] = minc;
		}
		return uglies[cnt - 1];
	}
};