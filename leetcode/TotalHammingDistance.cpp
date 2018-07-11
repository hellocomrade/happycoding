#include <vector>

using namespace std;

//https://leetcode.com/problems/total-hamming-distance
/*
477. Total Hamming Distance

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the given numbers.

Example:

Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.

Note:
- Elements of the given array are in the range of 0 to 10^9
- Length of the array will not exceed 10^4.

Observations:

The naive approach would be caluclating hamming distance between every pair of integer in the array, which will take O(N^2) time.

Does an O(N) time, O(1) space solution possible?

My first thought is: giving the fact that integer is 32 bits here, a counter array with 32 elements is used to count the number of bit 1
at each bit position for all given integers in the array. Then, loop the array again, scan all 32 bits for each integer, with counter available
for that position, we can tell the number of 1 or the number of 0 other than current integer. Extra code must be provided to carefully update
the counter after an integer is examined and remaning available bits have to be counted as well...Total takes O(64N) time.

We actually could get this done in O(32N). See the following array with 3 integers (8 bits only):

10111010
01010001
10011101

If we put all integers in their binary format, it looks like a matrix. Starting from lest significant bit, examine column by column,
in terms of hamming distance, at each bit, the distance = (number of 1 bit) * (number of 0 bit). The final result is done by adding up distances from all
8 bits.

Therefore, we could get the distance calculated in O(32N) time. Note (number of 0 bit) = len(array) - (number of 1 bit).
*/
class SolutionTotalHammingDistance {
public:
	int totalHammingDistance(vector<int>& nums) {
		int len = (int)nums.size(), ans = 0;
		for (int i = 0, cnt = 0; i < 32; cnt = 0, ++i) {
			for (int j : nums)
				if (0 < (j & (1 << i))) ++cnt;
			ans += cnt * (len - cnt);
		}
		return ans;
	}
	int totalHammingDistance1(vector<int>& nums) {
		vector<int> counts(30, 0);
		int pos = 0, len = (int)nums.size(), ans = 0;
		for (int i : nums) {
			pos = 0;
			while (i > 0) {
				if (1 == (i & 1)) ++counts[pos];
				i >>= 1, ++pos;
			}
		}
		for (int i : nums) {
			pos = 0;
			while (i > 0) {
				if (1 == (i & 1)) ans += len - counts[pos]--;
				else ans += counts[pos];
				i >>= 1, ++pos;
			}
			for (int j = pos; j < 30; ++j) ans += counts[j];
			--len;
		}
		return ans;
	}
};