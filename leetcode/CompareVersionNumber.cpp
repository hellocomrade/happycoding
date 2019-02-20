#include <string>
#include <functional>

using namespace std;

//https://leetcode.com/problems/compare-version-numbers
/*
165. Compare Version Numbers

Compare two version numbers version1 and version2.
If version1 > version2 return 1; if version1 < version2 return -1;otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.

The . character does not represent a decimal point and is used to separate number sequences.

For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.

You may assume the default revision number for each level of a version number to be 0. For example, version number 3.4 has a revision number of 3 and 4 for its first and second level revision number. Its third and fourth level revision number are both 0.


Example 1:

Input: version1 = "0.1", version2 = "1.1"

Output: -1

Example 2:

Input: version1 = "1.0.1", version2 = "1"

Output: 1

Example 3:

Input: version1 = "7.5.2.4", version2 = "7.5.3"

Output: -1

Example 4:

Input: version1 = "1.01", version2 = "1.001"

Output: 0

Explanation: Ignoring leading zeroes, both “01” and “001" represent the same number “1”

Example 5:

Input: version1 = "1.0", version2 = "1.0.0"

Output: 0

Explanation: The first version number does not have a third level revision number, which means its third level revision number is default to "0"

Note:

- Version strings are composed of numeric strings separated by dots . and this numeric strings may have leading zeroes.
- Version strings do not start or end with dots, and they will not be two consecutive dots.

Observation:

Converting substring between dots to number is the first one I ruled out simply because integer overflow using C++.

This is a so-called "implementation" problem. 3 assumptions:

1. String is not empty;
2. String doesn't start or end with dot;
3. Leading zeros may exist on each version section, for example 0001.000001.01;

Let's define the rules then:

A. Loop 2 strings and find version sections bewteen dots or at the end of strings;
B. Compare version sections and only continue the loop if the two version sections are equal;
C. For the comprasion function:
1. Remove leading zeros on both version sections;
2. If remaining sections are not equal on length, the longer one is consider larger for sure;
3. If equal on size, find the first not equal digits. If such a digits doesn't exist, they are equal,
Otherwise version1[l1] < version2[l2] ? -1 : 1;

My first attempt failed because I didn't think through. It failed on the following case:

"1.2"
"1.10"

Even though 2 is greater than 1, 10 is larger than 2. So the idea of comparing digits at same position does
NOT work unless they have equal size.

I should try other fun implementations using stol or stringstream even though I don't think they are valid.
That has been said, using similar approach in other languages such as Python is doable since those don't have
concern on integer overflow.
*/
class SolutionCompareVersionNumber {
public:
	int compareVersion(string version1, string version2) {
		int i = 0, j = 0, m = 0, n = 0, len1 = (int)version1.length(), len2 = (int)version2.length(), ans = 0;
		function<int(int, int, int, int)> comp = [&](int l1, int r1, int l2, int r2) -> int {
			while (l1 < r1 && '0' == version1[l1]) ++l1;
			while (l2 < r2 && '0' == version2[l2]) ++l2;
			if (r1 - l1 > r2 - l2) return 1;
			else if (r1 - l1 < r2 - l2) return -1;
			while (l1 < r1 && version1[l1] == version2[l2]) ++l1, ++l2;
			if (l1 == r1) return 0;
			else return version1[l1] < version2[l2] ? -1 : 1;
		};
		while ((i < len1 || m < len2) && 0 == ans) {
			while (j < len1 && '.' != version1[j]) ++j;
			while (n < len2 && '.' != version2[n]) ++n;
			ans = comp(i, j, m, n);
			i = ++j, m = ++n;
		}
		return ans;
	}
};
/*
Test cases:

"0.1"
"1.1"
"1.0.1"
"1"
"7.5.2.4"
"7.5.3"
"1.01"
"1.001"
"1.0"
"1.0.0"
"000.0.1"
"0.0.1"
"12"
"123"
"0001.0001.1"
"001.1.10"
"0001.0001.1"
"001.1.1"
"001.0100.000"
"001.100"
"001.0100.100"
"1.100.10"
"1.2"
"1.10"

outputs:

-1
1
-1
0
0
0
-1
-1
0
0
1
-1
*/