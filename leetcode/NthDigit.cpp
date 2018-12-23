//https://leetcode.com/problems/nth-digit/
/*
400. Nth Digit

Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:

n is positive and will fit within the range of a 32-bit signed integer (n < 231).

Example 1:

Input:

3

Output:

3

Example 2:

Input:

11

Output:

0

Explanation:

The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.

Observations:

1 digit natural numbers are from 1 to 9, total: 9 - 1 + 1 = 9

2 digits natural numbers are from 100 to 999, total: 999 - 100 + 1 = 900

3 digits natrual numbers are from 1000 to 9999, total 9999 - 1000 + 1 = 9000

It's intuitive to derive the following equation:

There are total 9 * 10^(K - 1) * K counts for natural numbers with K digits.

Is there a mathematical algorithm that can solve this in O(1)? The answer seems to be no...

If one steps back a bit, there is a logN solution.

Given a natural number n representing the nth number in the sequence, N is the actual number that nth digit fits in.
Using the formula above iteratively, substract from n till n could turn to negative. By exiting the loop, k is the
number of digits in N and remaining n (still positive) is the relative sequence number from 10^k. Since the formula
grows by 10 times, the while loop takes log10(n). Therefore, the total algorithm takes O(logN) time.

With the relative sequencing number n (10^k is the base) after the loop, one still have to decide:

1. N: this can be done by 10^k + (n - 1) / k;
2. The index of nth digit on N: (n - 1) % k;

Note the index in step 2 is 0 base on most significant digit (leftmost). If one prefers to extract this digit without
converting N to char array, it has to be done by dividing by 10 up to k - (n - 1) % k - 1 times then take modulo.
k - (n - 1) % k - 1 is the 0 base index from least significant digit (rightmost).

Since n could be up to 2^31 - 1 and the exit condition on while calculating the count of next k-digits number ahead of time,
an integer overflow will occur if variable holding 10^k is Integer. Therefore, using long long instead. Of course, one may
try using other way as exit condition, such as division, which will avoid dealing with integer overflow.
*/
class SolutionNthDigit {
public:
	int findNthDigit(int n) {
		long long tens = 1LL;
		int k = 1, val;
		while (n > 9 * tens * k) {
			n -= 9 * tens * k;
			tens *= 10, ++k;
		}
		val = tens + (n - 1) / k;
		n = k - (n - 1) % k;
		while (--n > 0) val /= 10;
		return val % 10;
	}
};
/*
Test Cases:

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
190
191
192
193
4378
88888
235237
9347516
65556915
214748364
894973477
2147483647

Outputs:

1
2
3
4
5
6
7
8
9
1
0
1
1
0
0
1
1
9
2
4
0
2
7
2
*/