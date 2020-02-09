#include <vector>

using namespace std;

//https://leetcode.com/problems/utf-8-validation/
/*
393. UTF-8 Validation

A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:

For 1-byte character, the first bit is a 0, followed by its unicode code.

For n-bytes character, the first n-bits are all one's, the n+1 bit is 0, followed by n-1 bytes with most significant 2 bits being 10.

This is how the UTF-8 encoding would work:

   Char. number range  |        UTF-8 octet sequence
	  (hexadecimal)    |              (binary)
   --------------------+---------------------------------------------
   0000 0000-0000 007F | 0xxxxxxx
   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

   Given an array of integers representing the data, return whether it is a valid utf-8 encoding.

Note:

The input is an array of integers. Only the least significant 8 bits of each integer is used to store the data. This means each integer represents only 1 byte of data.

Example 1:

data = [197, 130, 1], which represents the octet sequence: 11000101 10000010 00000001.

Return true.

It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte character.

Example 2:

data = [235, 140, 4], which represented the octet sequence: 11101011 10001100 00000100.

Return false.

The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes character.
The next byte is a continuation byte which starts with 10 and that's correct.
But the second continuation byte does not start with 10, so it is invalid.

Hints:

- All you have to do is follow the rules. For a given integer, obtain its binary representation in the string form and work with the rules given in the problem.
- An integer can either represent the start of a UTF-8 character, or a part of an existing UTF-8 character. There are two separate rules for these two scenarios in the problem.
- If an integer is a part of an existing UTF-8 character, simply check the 2 most significant bits of in the binary representation string. They should be 10. If the integer represents the start of a UTF-8 character, then the first few bits would be 1 followed by a 0. The number of initial bits (most significant) bits determines the length of the UTF-8 character.

  Note: The array can contain multiple valid UTF-8 characters.
- String manipulation will work fine here. But, it is too slow. Can we instead use bit manipulation to do the validations instead of string manipulations?
- We can use bit masking to check how many initial bits are set for a given number. We only need to work with the 8 least significant bits as mentioned in the problem.

  ```python
  mask = 1 << 7
  while mask and num:
	  n_bytes += 1
	  mask = mask >> 1
  ```

  Can you use bit-masking to perform the second validation as well i.e. checking if the most significant bit is 1 and the second most significant bit a 0?

- To check if the most significant bit is a 1 and the second most significant bit is a 0, we can make use of the following two masks.

  ```python
  mask1 = 1 << 7
  mask2 = 1 << 6

  if not (num & mask1 and not (num & mask2)):
	  return False
  ```

Observations:

This is an implementation type of problem using bitwise. The description of the problem is hard to understand and
the hints reveal too much information that a solution can be out of it immediately.

1. Each element in the given array is an integer that is no greater than 0xFF;
2. The array might contain multiple UTF-8 encoded characters, ech of them might be represented by 1 to 4 one byte integers;
3. We only need to check if the UTF-8 encoding is valid, the character it carries doesn't matter at all.

validUtf8_1 is a naive solution based upon hints: from the beginning of the array, find out how long
the UTF-8 encoded character is by checking the first integer, up to 5 bits, then check the following bytes
based upon the length of this UTF-8 encoded character. Following the same course, make sure every one byte
long integer is a part of a legit UTF-8 encoded character.

Note: (0 < m && i + m > len) is necessary to make sure every integer in the array is a component of an UTF-8 encoded character.
	  For example: [1, 255], 1 is a valid one byte UTF8 char, but 255 is not, it's supposed to be the header of
	  a four-byte-long UTF8 char. Therefore, the array is not valid.

validUtf8 is a faster version. Instead of using masks, it shifts the integer to match with predefined values based upon
the rules of UTF-8 encoding.

0
0b110
0b1110
0b11110

The performance improvement appears to be contributed by less bitwise operations.
*/
class SolutionUTF8Validation {
public:
	bool validUtf8(vector<int>& data) {
		int len = (int)data.size(), m = 0, n = 0, i = 0;
		while (i < len) {
			n = data[i], m = 0;
			if (0 == (n >> 7)) m = 1;
			else if (0b110 == (n >> 5)) m = 2;
			else if (0b1110 == (n >> 4)) m = 3;
			else if (0b11110 == (n >> 3)) m = 4;
			if (0 == m || i + m > len) return false;
			for (int k = 1; k < m; ++k) if (0b10 != (data[i + k] >> 6)) return false;
			i += m;
		}
		return true;
	}
	bool validUtf8_1(vector<int>& data) {
		int len = (int)data.size(), i = 0, j = 0, n = 0, m = 0;
		while (i < len) {
			n = data[i] & 0xff, j = 7, m = 0;
			while (j > 2 && 0 != ((1 << j--) & n)) ++m;
			if (1 == m || 4 < m || (0 < m && i + m > len)) return false;
			if (0 == m) ++m;
			for (int k = 1; k < m; ++k)
				if (false == (0 != ((1 << 7) & (data[i + k] & 0xff)) && 0 == ((1 << 6) & (data[i + k] & 0xff)))) return false;
			i += m;
		}
		return true;
	}
};
/*
Test cases:

[248,130,130,130]
[255]
[230,136,145]
[197,130,1]
[235, 140, 4]
[]
[1]
[2456, 123]
[250,145,145,145,145]
[16]

Outputs:

false
false
true
true
false
true
true
false
false
true
*/