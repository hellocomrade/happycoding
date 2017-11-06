#include <stdint.h>  // for uint32_t, to get 32bit-wide rotates, regardless of the size of int.
#include <limits.h>  // for CHAR_BIT
//http://lintcode.com/en/problem/rotate-bits-left/
/*
Rotate Bits - Left

Bit Rotation -—— A rotation (or circular shift) is an operation similar to shift except that the bits that fall off at one end are put back to the other end.

In left rotation, the bits that fall off at left end are put back at right end.

Let n is stored using 8 bits. Left rotation of n = 　11100101 by 3 makes n = 00101111 (Left shifted by 3 and first 3 bits are put back in last ). If n is stored using 16 bits or 32 bits then left rotation of n (000…11100101) becomes 00..0011100101000.

In this problem, you can assume that n was stored in 32 Bits

Example
Given n = 123, d = 4
return 183

Observations:
I thought this would be easy for Java developer coz Java has >>>, turn out I totaly misunderstood >> (signed right shift operator) and >>> (unsigned right shift operator), not to mention there is no <<< at all!

https://docs.oracle.com/javase/tutorial/java/nutsandbolts/op3.html

But, who would do bitwise operations using Java? :) In case you want to know why <<< doesn't exist, short answer is that it's as same as <<, long answer is here:

https://www.quora.com/Why-is-there-no-unsigned-left-shift-operator-in-Java

The catch is: whenever you see a rotation by certain number, count in the %, say on a 32-bit integer, it's legal to shift 168 bits...
*/
class SolutionRotateBitLeft {
public:
	/*
	* @param : a number
	* @param : digit needed to be rorated
	* @return: a number
	*/
	//https://en.wikipedia.org/wiki/Circular_shift
	/*
	* Shift operations in C are only defined for shift values which are
	* not negative and smaller than sizeof(value) * CHAR_BIT.
	* The mask, used with bitwise-and (&), prevents undefined behaviour
	* when the shift count is 0 or >= the width of unsigned int.
	*/
	int leftRotate(int n, int d) {
		const unsigned int mask = CHAR_BIT * sizeof(n) - 1;
		d &= mask;
		return (n << d) | (n >> (-d & mask));
	}
	int leftRotate1(int n, int d) {
		return (n << d % 32) | (n >> (32 - d % 32));
	}
	int leftRotate2(int n, int d) {
		int m = ((1 << (d % 32)) - 1) << (32 - (d % 32));
		return ((n & ~m) << (d % 32)) | ((n & m) >> (32 - d % 32));
	}
};