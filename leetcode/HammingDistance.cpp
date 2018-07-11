//https://leetcode.com/problems/hamming-distance
/*
461. Hamming Distance

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 231.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
↑   ↑

The above arrows point to positions where the corresponding bits are different.

Observations:

Hamming distance: https://en.wikipedia.org/wiki/Hamming_distance

It asks counting bits set on XOR of two integer. I used the trick at:

https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
*/
class SolutionHammingDistance {
public:
	int hammingDistance(int x, int y) {
		int n = x ^ y, ans = 0;
		while (n > 0) {
			++ans;
			n &= (n - 1);
		}
		return ans;
	}
};