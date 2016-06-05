//http://www.lintcode.com/en/problem/update-bits/
/*
Update Bits

Given two 32-bit numbers, N and M, and two bit positions, i and j. Write a method to set all bits between i and j in N equal to M (e g , M becomes a substring of N located at i and starting at j)

Notice

In the function, the numbers N and M will given in decimal, you should also return a decimal number.

Clarification
You can assume that the bits j through i have enough space to fit all of M. That is, if M=10011， you can assume that there are at least 5 bits between j and i. You would not, for example, have j=3 and i=2, because M could not fully fit between bit 3 and bit 2.

Example
Given N=(10000000000)2, M=(10101)2, i=2, j=6

return N=(10001010100)2

Challenge
Minimum number of operations?

Observations:
The description of the problem is a bit confusing. What it's exactly asking is to replace certain
bits in N with M, i is the LSB pos(on right), j is the MSB. You will need to clear up bits from i to j
to zero and then fill them with bits in M, giving j - i + 1 is wider than M. The extra bits should remain
zero.

The concern here is:
1. Negative number, MSB filled with 1 (postion 31);
2. What if j - i == 31? since we need j - i + 1, it's an overflow for bitwise shift;
3. Arithmetic vs logical bit shift
4. Bit operator has a lower precedence than +, -, *, /, you may need a lot of brackets

First, we need to make the mask:
1 << n - 1 -- this will make lower n bits with 1:
for example 1 << 5 - 1, you will get 000000000000000000000000000100000 then minus 000000000000000000000000000011111

We should do ((1 << (j - i + 1)) - 1).This is the width we need to clear out the section in N.

Then we align these 1 bits on N: ((1 << (j - i + 1)) - 1) << i

Next, we flip them to zero as the mask: ~(((1 << (j - i + 1)) - 1) << i)

Clear N with the mask: n & (~(((1 << (j - i + 1)) - 1) << i))

Finally, apply M onto N: n & (~(((1 << (j - i + 1)) - 1) << i)) | (m << i)

Special case is when j - i == 31, in this case, we will 1 << 32, which in C++, get 1 itself as the result.
this will break the following << i, since we are not moving anything other than 0. When you flip it, you will
get 32 bits with 1, which will NOT clear up anything on N.

So, notice the fact that j - i == 31 actually means zero out N completely, all left is simply m << i
*/
class SolutionUpdateBits {
public:
	/**
	*@param n, m: Two integer
	*@param i, j: Two bit positions
	*return: An integer
	*/
	int updateBits(int n, int m, int i, int j) {
		if (i < 0 || j < 0 || i > 31 || j > 31)return -1;
		if (j - i == 31) return m << i;
		return (n & (~(((1 << (j - i + 1)) - 1) << i))) | (m << i);
	}
};