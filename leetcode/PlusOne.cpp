#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/plus-one/
/*
66. Plus One

Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:

Input: [1,2,3]

Output: [1,2,4]

Explanation: The array represents the integer 123.

Example 2:

Input: [4,3,2,1]

Output: [4,3,2,2]

Explanation: The array represents the integer 4321.

Observations:

This can be done in place with 1 byte extra space (but potentially O(N) move though).

Adding one to a non-negative integer, we will face either or:

1. A digit less than 9, add 1 to that digit and that's the final result;

2. A digit equal to 9, put 0 there and move to the next digit, keep add-one loop (now add with the carray).

If the loop ends, we can tell the MSD was 9 (0 now). We shall turn MSD to 1 and push an extra 0 at the end of the arry.
*/
class SolutionPlusOne {
public:
	vector<int> plusOne(vector<int>& digits) {
		for (auto i = digits.rbegin(); digits.rend() != i; ++i) {
			if (9 == *i) *i = 0;
			else {
				++*i;
				return digits;
			}
		}
		digits[0] = 1;
		digits.push_back(0);
		return digits;
	}
	vector<int> plusOne1(vector<int>& digits) {
		vector<int> ans;
		int carry = 1, t = 0;
		for (auto i = digits.rbegin(); digits.rend() != i; ++i) {
			t = *i + carry;
			if (t > 9) carry = 1, t = 0;
			else carry = 0;
			ans.emplace_back(t);
		}
		if (1 == carry) ans.emplace_back(1);
		std::reverse(ans.begin(), ans.end());
		return ans;
	}
};
/*
Test cases:

[1,2,3]
[9,9,9,9]
[9,0,9,9]
[0]
[1]
[9]
[9,8,7,6,5,4,3,2,1,0]
[6,1,4,5,3,9,0,1,9,5,1,8,6,7,0,5,5,4,3]

Outputs:

[1,2,4]
[1,0,0,0,0]
[9,1,0,0]
[1]
[2]
[1,0]
[9,8,7,6,5,4,3,2,1,1]
[6,1,4,5,3,9,0,1,9,5,1,8,6,7,0,5,5,4,4]
*/