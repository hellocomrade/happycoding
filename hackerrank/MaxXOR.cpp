//https://www.hackerrank.com/challenges/maximizing-xor
/*
Maximizing XOR

Given two integers, L and R, find the maximal value of A xor B, where A and B satisfy the following condition:
L <= A <= B <= R

Input Format

The input contains two lines; L is present in the first line and R in the second line.

Constraints

1 <= L <= R <= 10^3

Output Format

The maximal value as mentioned in the problem statement.

Sample Input

10
15

Sample Output

7

Explanation

Here two pairs (10, 13) and (11, 12) have maximum xor value 7, and this is the answer.

Observations:
By playing with couple examples, it appears by XOR on i and j, you got an number which the hightest
bit position minus 1 is the answer.
15 ^ 10 = 8 = 2^3
the answer is 2^3 - 1 = 7

Now we need to figure out how to find the position of the most significant bit. maxXOR1 is a naive impl.
O(N), find position n then 2^n -1

There is alternative inspired by "Round up to the next highest power of 2" from Bit Twiddling Hacks:
https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

instead of getting the 2^n, we got 2^n - 1 by ignoring the --m, ++m operations...
*/
size_t maxXOR(size_t i, size_t j) {
	size_t m = i^j;
	m |= m >> 1;
	m |= m >> 2;
	m |= m >> 4;
	m |= m >> 8;
	m |= m >> 16;
	return m;
}
size_t maxXOR1(size_t i, size_t j) {
	size_t m = i^j;
	size_t n = 0;
	while (m > 0) {
		m >>= 1;
		++n;
	}
	return (1 << n) - 1;
}
