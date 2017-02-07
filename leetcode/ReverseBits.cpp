#include <cstdint>
#include <bitset>
#include <climits>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/reverse-bits/
/*
190. Reverse Bits

Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?
*/
class SolutionReverseBits {
public:
	//3ms, O(5*logN), N = 32
	//https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
	uint32_t reverseBits(uint32_t n) {
		// swap odd and even bits
		n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
		// swap consecutive pairs
		n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
		// swap nibbles ... 
		n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
		// swap bytes
		n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
		// swap 2-byte long pairs
		n = (n >> 16) | (n << 16);
		return n;
	}
	//6ms, O(N), N = 32
	uint32_t reverseBits1(uint32_t n) {
		unsigned int r = n; // r will be reversed bits of v; first get LSB of n
		int s = sizeof(n) * CHAR_BIT - 1; // extra shift needed at end
		for (n >>= 1; n; n >>= 1)
		{
			r <<= 1;
			r |= n & 1;
			s--;
		}
		r <<= s; // shift when v's highest bits are zero
		return r;
	}
	//6ms, my O(N), N = 32
	uint32_t reverseBits2(uint32_t n) {
		uint32_t ans = 0, one = 1;
		for (int i = 0; i < 4 && n; ++i) {
			if (n & 1)ans |= one << (31 - i * 8);
			if (n & 2)ans |= one << (30 - i * 8);
			if (n & 4)ans |= one << (29 - i * 8);
			if (n & 8)ans |= one << (28 - i * 8);
			if (n & 16)ans |= one << (27 - i * 8);
			if (n & 32)ans |= one << (26 - i * 8);
			if (n & 64)ans |= one << (25 - i * 8);
			if (n & 128)ans |= one << (24 - i * 8);
			n >>= 8;
		}
		return ans;
	}
};
void TestReverseBits() {
	SolutionReverseBits so;
	cout << std::bitset<32>(so.reverseBits(43261596)) << endl;
}
