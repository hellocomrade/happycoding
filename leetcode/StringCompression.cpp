#include <vector>

using namespace std;

//https://leetcode.com/problems/string-compression/
/*
443. String Compression

Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.


Follow up:

Could you solve it using only O(1) extra space?


Example 1:

Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:

"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".

Example 2:

Input:

["a"]

Output:

Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:

Nothing is replaced.

Example 3:

Input:

["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.

Note:

- All characters have an ASCII value in [35, 126].
- 1 <= len(chars) <= 1000.

Observations:

This problem was mentioned being used as a phone interview question:

https://leetcode.com/discuss/interview-experience/510892/spotify-backend-engineer-ii-stockholm-oct-2019-offer

Simple string manipulation problem using two pointers: one for reading, the other one for writing.
Edge case that could be overlooked is at the end of the array, whatever character or count shall be written back.

Count is done while reading or you may use the substraction of the writing pointer to the reading pointer. Since the count
is asked to be split as chars and O(1) space is preferred, partition digits is used instead of std::to_string(int). However,
this time, the number has to be read from most significant digit. Padding zero after MSD might be needed, therefore
an extra boolean variable as indicator for whether or not the MSD has been discovered.
*/
class SolutionStringCompression {
public:
	int compress(vector<char>& chars) {
		bool msd = true;
		int len = (int)chars.size(), ans = 1;
		for (int i = 1, cnt = 1; i <= len; ++i) {
			if (i < len && chars[i] == chars[i - 1]) ++cnt;
			else {
				if (1 < cnt) {
					if (0 < cnt / 1000) chars[ans++] = '0' + cnt / 1000, cnt %= 1000, msd = false;
					if (0 < cnt / 100 || false == msd) chars[ans++] = '0' + cnt / 100, cnt %= 100, msd = false;
					if (0 < cnt / 10 || false == msd) chars[ans++] = '0' + cnt / 10, cnt %= 10, msd = false;
					chars[ans++] = '0' + cnt, msd = true, cnt = 1;
				}
				if (i < len) chars[ans++] = chars[i];
			}
		}
		return ans;
	}
};
/*
Test cases:

["a","a","b","b","c","c","c"]
["a"]
["a","b"]
["a","b","b","b","b","b","b","b","b","b","b","b","b"]
["b","a","a","c","a","a"]

Outputs:

["a","2","b","2","c","3"]
["a"]
["a","b"]
["a","b","1","2"]
["b","a","2","c","a","2"]
*/