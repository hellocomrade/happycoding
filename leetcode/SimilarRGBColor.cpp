#include <string>

using namespace std;

//https://www.lintcode.com/problem/similar-rgb-color/description
/*
800 Similar RGB Color

Description

In the following, every capital letter represents some hexadecimal digit from 0 to f.

The red-green-blue color "#AABBCC" can be written as "#ABC" in shorthand. For example, "#15c" is shorthand for the color "#1155cc".

Now, say the similarity between two colors "#ABCDEF" and "#UVWXYZ" is -(AB - UV)^2 - (CD - WX)^2 - (EF - YZ)^2.

Given the color "#ABCDEF", return a 7 character color that is most similar to #ABCDEF, and has a shorthand (that is, it can be represented as some "#XYZ")

Note:

- Color is a string of length 7.
- Color is a valid RGB color: for i > 0, color[i] is a hexadecimal digit from 0 to f
- Any answer which has the same (highest) similarity as the best answer will be accepted.
- All inputs and outputs should use lowercase letters, and the output is 7 characters.

Observations:

First of all, this is a problem at leetcode requiring subscription. I don't have it but lintcode offers the same problem for free.
I put this problem under the folder of leetcode simply for consistency.

One may expect a better solution than simply brute force all possible options giving the limited range here:

0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff

They form an arithmetic progression with diff = 0x11.

Therefore, the base of such a closer color code for a given color K (in hex base) can be obtained by (K / 0x11).
Then the reminder (K % 0x11) will decide whether the cloest one is (K / 0x11) or (K / 0x11 + 1). It's not hard to find
out that magic number is 8. Since 0x11 is an odd number, it's no way to make (K / 0x11) - K ==  (K / 0x11 + 1) - K.

If one has trouble to understand this due to the unfamiliar hex base. Here is a good example:

Given dec based number: 125, find the closest number with 0 as the least significant digit. It may take one only half
second to figure using 125 / 10 * 10, then the base line is 120, turn out both 120 and 130 work as the closest number to 125.

The implementation down there doesn't use (K / 0x11 * 0x11) because the output is string. Due to the nature of this arithemtic
progression, one can do i < 10 ? '0' + i : i - 10 + 'a', given i = K / 0x11 + (k % 0x11 > 8 ? 1 : 0).
*/
class SolutionSimilarRGBColor {
public:
	/**
	* @param color: the given color
	* @return: a 7 character color that is most similar to the given color
	*/
	string similarRGB(string &color) {
		for (int i = 1, k; i < 7; i += 2) {
			k = std::stoi(color.substr(i, 2), nullptr, 16);
			k = k / 0x11 + (k % 0x11 > 8 ? 1 : 0);
			color[i] = color[i + 1] = k < 10 ? '0' + k : k - 10 + 'a';
		}
		return color;
	}
};