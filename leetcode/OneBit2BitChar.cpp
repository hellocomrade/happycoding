#include <vector>

using namespace std;

//https://leetcode.com/problems/1-bit-and-2-bit-characters/
/*
717. 1-bit and 2-bit Characters

We have two special characters. The first character can be represented by one bit 0. The second character can be represented by two bits (10 or 11).

Now given a string represented by several bits. Return whether the last character must be a one-bit character or not. The given string will always end with a zero.

Example 1:
Input: 
bits = [1, 0, 0]
Output: True
Explanation: 
The only way to decode it is two-bit character and one-bit character. So the last character is one-bit character.

Example 2:
Input: 
bits = [1, 1, 1, 0]
Output: False
Explanation: 
The only way to decode it is two-bit character and two-bit character. So the last character is NOT one-bit character.

Note:
- 1 <= len(bits) <= 1000.
- bits[i] is always 0 or 1.

Observations:
Given the fact the last bit is always 0, everything is straightforward. My idea is doing this in a linear scan from left to right:
Given index i
1. Substring ends at i - 1 is a valid string, if bits[i] is 0, then substring ends at i is valid. Or, substring ends at i is not valid;
2. Substring ends at i - 1 is an invalid string, then no matter bits[i] is 0 or 1, substring ends at i is valid.

I reuse the bits to store whether substring ends at i is valid, see isOneBitCharacter2, which turns out to be unnecessary after reading the offical solution:

https://leetcode.com/problems/1-bit-and-2-bit-characters/solution/

Again, official solution beats me...it uses a pointer to mark the end of the valid substring plus 1. Therefore, after the scan stops at len - 2,
if i points to len - 1, then we know answer is true since the last bit is 0 for sure. Or i could be len, that means the last bit 0 must have to
form a valid character with the bit before it. See isOneBitCharacter.

There is actually an alternative: if we check the bits array from right to left starting from len - 2, if bits[k] is 0, then we know the substring
from 0 to k is a valid string for sure. Then we simplify the question to: between the last 0 at len - 1 and index k, homw many continuous 1 in between?
If the number is odd, then we will need the last 0 at len - 1 to form a valid string. Otherwise, the last 0 represents its own character.
See isOneBitCharacter1
*/
class SolutionOneBit2BitChar {
public:
    bool isOneBitCharacter(vector<int>& bits) {
        int len = (int)bits.size(), i = 0;
        while(i < len - 1)
          i += bits[i] + 1;
        return i == len - 1;
    }
    bool isOneBitCharacter1(vector<int>& bits) {
        int len = (int)bits.size(), i = len - 2, cnt1 = 0;
        while(i > -1 && bits[i] > 0)
          --i, ++cnt1;
        return 0 == (cnt1 & 1);
    }
    bool isOneBitCharacter2(vector<int>& bits) {
        int len = (int)bits.size();
        bits[0] = (0 == bits[0]) ? -1 : -2; 
        for(int i = 1; i < len - 1; ++i)
            bits[i] = (1 == bits[i] && -1 == bits[i - 1]) ? -2 : -1;
        return 1 == len || bits[len - 2] == -1;
    }
};
