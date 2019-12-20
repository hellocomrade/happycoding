#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

//https://leetcode.com/problems/create-maximum-number/
/*
321. Create Maximum Number

Given two arrays of length m and n with digits 0-9 representing two numbers.
Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits
from the same array must be preserved. Return an array of the k digits.

Note: You should try to optimize your time and space complexity.

Example 1:

Input:

nums1 = [3, 4, 6, 5]

nums2 = [9, 1, 2, 5, 8, 3]

k = 5

Output:

[9, 8, 6, 5, 3]

Example 2:

Input:

nums1 = [6, 7]

nums2 = [6, 0, 4]

k = 5

Output:

[6, 7, 6, 0, 4]

Example 3:

Input:

nums1 = [3, 9]

nums2 = [8, 9]

k = 3

Output:

[9, 8, 9]

Observations:

I was struggling between DP and Greedy for a while. Then I realize this code will look messy no matter Greedy or DP.

maxNumber99 may illustrate the naive solution following greedy thoughts:

Find the local max from both nums1 and nums2 as long as the remaining elements from both arrays are still
sufficient to build the max number in the length of k.

Then, depending on the comparison between max(nums1) and max(nums2) in the given index ranges [i1, n - 1], [i2, n - 1],
the max number can be built in a recursive way.

For the case that max(nums1) == max(nums2), both numbers will be picked and two branches will be pursued. The
results that are recursively built from two splits will then be compared and the greater one will be chosen.

Of course, you will get a TLE for this naive solution. Considering DP might be encourged by the case of max(nums1) == max(nums2),
however, it appears to be hard to define transition function. It's more likely to be a memorization trick and
it may be a 3D memo array.

Then, my next attempt is a greedy solution, maxNumber1, it barely passed. The idea is based upon the obseration that
the max number comes from picking the max number out of nums1 with size of m1 and the max number ot of nums2 with size of m2,
given m1 + m2 = k, then theset two max numbers are merged.

Therefore, partition max number with size k to merge from a max number from nums1 in range of [0, MIN(len(nums1), k)]
and a max number from nums2 in range of [MIN(len(nums1), k), 0], if len(nums1) + len(nums2) >= k.

The sub problems are:

1. Finding the max number with size n from a single array;
2. Merge two max numbers into one max number;

maxNumber1 is extremely slow due the fact that sub problem 1 was not solved optimally. The assumption I made up
front is to fill the destination array memo, for max number completely, then for any following digit, on each
iteration, shift the array toward left based upon the leftmost case where memo[j - 1] < memo[j]. This is slow
because the elements in memo could be left shifted on each iteration, lead to a O(k * len(num)) time complexity

The sub problem 2 was solved in a reasonable way: it follows the merge-sort merge approach. Finding the max digit
from both max number arrays memo1 and memo2 using two pointers. The tricky part is agin: solve the equal case.

nums1 = [2, 0]

nums2 = [3, 0, 3]

tie on nums1[1] = nums2[1] = 0

Should output to [3, 2, 0, 3, 0]

but

nums1 = [2, 0, 9]

nums2 = [3, 0, 3]

should be [3, 2, 0, 9, 0, 3]

When a tie occurs, we shall scan the remaining digits from both arrays until nums1[i] != nums2[j] or any
array index is out of scope. Then the 0 from nums1 will be inserted next only if nums1[i] > nums2[j] if both
i and j are valid and vice a versa. For the case one index is out of scope, the one that is not out of scope
should have its zero inserted. If both indexes are out, either zero is OK, coz it means all remaining digits from
both arrays are the same.

maxNumber is the corrected version of maxNumber1. Sub problem 1 is implemented like insertion sort:

If on array num, there are enough digits to fill a max number with size of k, compare the rightmost element on
array memo (for max number), memo[j - 1] with num[i]. If num[i] is bigger, --j. Then keep this loop as long
as n - j < len - i, (n - j) indicates the number of digits needed to fill max number, (len - i) tells the
available digits on num. (n - j < len - i) is the boundary condition that decides how far back j can go even
if num[i] > memo[j] all the way back to the beginning of memo.

For example, given num = [1, 8 ,2], k = 2:

1. i = 0, memo = [1], j = 1;

2. i = 1, num[i] > memo[j - 1] --> --j --> already reach the beginning, therefore memo[0] = num[1], j = 1;

3. i = 2, j = 1 -> memo[1] = num[2] = 2;

Output: [8, 2]

The sub problem 2 was optimized as well. Combining all logic in one while loop. The detail is trick to implement
but the idea remains the same: resolve tie if have to.

The optimized solution of sub problem 1 comes from:

https://leetcode.com/problems/create-maximum-number/discuss/77285/Share-my-greedy-solution
*/
class SolutionCreateMaximumNumber {
public:
	vector<int> maxNumber(const vector<int>& nums1, const vector<int>& nums2, int k) {
		int len1 = (int)nums1.size(), len2 = (int)nums2.size();
		if (k > len1 + len2) return vector<int>(k, 0);
		vector<int> memo1(k, 0), memo2(k, 0), memo3(k, 0), ans(k, 0);
		function<void(const vector<int>&, vector<int>&, int)> maxseq = [&](const vector<int> &num, vector<int> &memo, int n) -> void {
			int len = (int)num.size();
			for (int i = 0, j = 0; n > 0 && i < len; ++i) {
				while (n - j < len - i && 0 < j && memo[j - 1] < num[i]) --j;
				if (j < n) memo[j++] = num[i];
			}
		};
		for (int i = 0, j = std::min(len1, i), l = 0, m = 0, p = 0, q1, q2; i <= k; l = 0, m = 0, p = 0, j = std::min(len1, ++i)) {
			if (k - j > len2) continue;
			maxseq(nums1, memo1, j);
			maxseq(nums2, memo2, k - j);
			while (l < j || m < k - j) {
				q1 = l, q2 = m;
				while (q1 < j && q2 < k - j && memo1[q1] == memo2[q2]) ++q1, ++q2;
				if (j == q1 || (q2 < k - j && memo1[q1] < memo2[q2])) memo3[p++] = memo2[m++];
				else memo3[p++] = memo1[l++];
			}
			ans = std::max(ans, memo3);
		}
		return ans;
	}
	//Barely pass
	vector<int> maxNumber1(vector<int>& nums1, vector<int>& nums2, int k) {
		int len1 = (int)nums1.size(), len2 = (int)nums2.size();
		if (k > len1 + len2) return vector<int>(k, 0);
		vector<int> memo1(k, 0), memo2(k, 0), memo3(k, 0), ans(k, 0);
		function<void(const vector<int>&, vector<int>&, int)> maxseq = [&](const vector<int> &num, vector<int> &memo, int n) -> void {
			int len = (int)num.size();
			for (int i = 0, j = 0; n > 0 && i < len; ++i) {
				if (j < n) memo[j++] = num[i];
				else {
					int l = -1;
					for (int m = n - 1; m > 0; --m)
						if (memo[m] > memo[m - 1])
							l = m - 1;
					for (int m = l; l > -1 && m < n - 1; ++m)
						memo[m] = memo[m + 1];
					if (-1 < l || num[i] > memo[n - 1]) memo[n - 1] = num[i];
				}
			}
		};
		for (int i = 0, j = std::min(len1, i), l = 0, m = 0, p = 0; i <= k; l = 0, m = 0, p = 0, j = std::min(len1, ++i)) {
			if (k - j > len2) continue;
			maxseq(nums1, memo1, j);
			maxseq(nums2, memo2, k - j);
			while (l < j && m < k - j) {
				int q1 = l, q2 = m;
				while (q1 < j && q2 < k - j && memo1[q1] == memo2[q2]) ++q1, ++q2;
				if (j == q1 || memo1[q1] < memo2[q2]) memo3[p++] = memo2[m++];
				else memo3[p++] = memo1[l++];
			}
			while (l < j) memo3[p++] = memo1[l++];
			while (m < k - j) memo3[p++] = memo2[m++];
			ans = std::max(ans, memo3);
		}
		return ans;
	}
	//Tried based upon TLE version, but doesn't work
	vector<int> maxNumber2(const vector<int>& nums1, const vector<int>& nums2, int k) {
		int len1 = (int)nums1.size(), len2 = (int)nums2.size();
		if (k > len1 + len2) return vector<int>(k, 0);
		vector<int> ans(k, -1);
		vector<vector<vector<std::pair<int, int>>>> memo(len1 + 1, vector<vector<std::pair<int, int>>>(len2 + 1, vector<std::pair<int, int>>(k + 1, std::make_pair(-1, -1))));
		function<void(int, int, int)> maxNum = [&](int i, int j, int n) -> void {
			if (1 > n || (len1 == i && len2 == j) || len1 - i + len2 - j < n) return;
			int i1 = i, j1 = j, max1 = i, max2 = j;
			if (-1 != memo[i][j][k].first)
				max1 = memo[i][j][k].first;
			else {
				while (i1 < len1 && len1 - i1 + len2 - j >= n) {
					if (nums1[max1] < nums1[i1++])
						max1 = i1 - 1;
				}
				memo[i][j][k].first = max1;
			}
			if (-1 != memo[i][j][k].second)
				max2 = memo[i][j][k].second;
			else {
				while (j1 < len2 && len1 - i + len2 - j1 >= n) {
					if (nums2[max2] < nums2[j1++])
						max2 = j1 - 1;
				}
				memo[i][j][k].second = max2;
			}
			if (max2 == len2 || (max1 < len1 && nums1[max1] > nums2[max2])) {
				if (max1 < len1 && nums1[max1] >= ans[k - n]) {
					ans[k - n] = nums1[max1];
					maxNum(max1 + 1, j, n - 1);
				}
			}
			else if (max1 == len1 || (max2 < len2 && nums1[max1] < nums2[max2])) {
				if (max2 < len2 && nums2[max2] >= ans[k - n]) {
					ans[k - n] = nums2[max2];
					maxNum(i, max2 + 1, n - 1);
				}
			}
			else {
				if (nums1[max1] >= ans[k - n]) {
					ans[k - n] = nums1[max1];
					maxNum(max1 + 1, j, n - 1);
					vector<int> tmp(ans);
					for (int i = k - n + 1; i < k; ++i) ans[i] = -1;
					maxNum(i, max2 + 1, n - 1);
					ans = std::max(tmp, ans);
				}
			}
		};
		maxNum(0, 0, k);
		return ans;
	}
	//Naive recursive, TLE
	vector<int> maxNumber99(vector<int>& nums1, vector<int>& nums2, int k) {
		int len1 = (int)nums1.size(), len2 = (int)nums2.size();
		if (k > len1 + len2) return vector<int>(k, 0);
		vector<int> ans;
		function<string(int, int, int)> maxNum = [&](int i, int j, int n) -> string {
			if (1 > n || (len1 == i && len2 == j) || len1 - i + len2 - j < n) return "";
			int i1 = i, j1 = j, max1 = i, max2 = j;
			while (i1 < len1 && len1 - i1 + len2 - j >= n) {
				if (nums1[max1] < nums1[i1++])
					max1 = i1 - 1;
			}
			while (j1 < len2 && len1 - i + len2 - j1 >= n) {
				if (nums2[max2] < nums2[j1++])
					max2 = j1 - 1;
			}
			if (max2 == len2 || (max1 < len1 && nums1[max1] > nums2[max2]))
				return std::to_string(nums1[max1]) + maxNum(max1 + 1, j, n - 1);
			else if (max1 == len1 || (max2 < len2 && nums1[max1] < nums2[max2]))
				return std::to_string(nums2[max2]) + maxNum(i, max2 + 1, n - 1);
			else
				return std::to_string(nums1[max1]) + std::max(maxNum(max1 + 1, j, n - 1), maxNum(i, max2 + 1, n - 1));
		};
		string str = maxNum(0, 0, k);
		for (char c : str) ans.push_back(c - '0');
		return ans;
	}
};
void TestCreateMaximumNumber() {
	SolutionCreateMaximumNumber so;
	so.maxNumber(vector<int>{2, 5, 6, 4, 4, 0}, vector<int>{7, 3, 8, 0, 6, 5, 7, 6, 2}, 15);
	so.maxNumber(vector<int>{5, 0, 2, 1, 0, 1, 0, 3, 9, 1, 2, 8, 0, 9, 8, 1, 4, 7, 3}, vector<int>{7, 6, 7, 1, 0, 1, 0, 5, 6, 0, 5, 0}, 31);
	so.maxNumber(vector<int>{1, 6, 5, 4, 7, 3, 9, 5, 3, 7, 8, 4, 1, 1, 4}, vector<int>{4, 3, 1, 3, 5, 9}, 21);
	so.maxNumber(vector<int>{2, 0}, vector<int>{3, 0, 3}, 5);
	so.maxNumber(vector<int>{3, 4, 6, 5}, vector<int>{9, 1, 2, 5, 8, 3}, 1);
	so.maxNumber(vector<int>{3, 4, 6, 5}, vector<int>{9, 1, 2, 5, 8, 3}, 5);
	so.maxNumber(vector<int>{3, 4, 6, 5}, vector<int>{9, 1, 2, 5, 8, 3}, 6);
	so.maxNumber(vector<int>{0, 0, 1}, vector<int>{0}, 3);
	so.maxNumber(vector<int>{2, 5, 6, 4, 4, 0}, vector<int>{7, 3, 8, 0, 6, 5, 7, 6, 2}, 15);
	so.maxNumber(vector<int>{}, vector<int>{1}, 1);
	so.maxNumber(vector<int>{6, 7}, vector<int>{6, 0, 4}, 5);
}
/*
Test cases:

[5,0,2,1,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3]
[7,6,7,1,0,1,0,5,6,0,5,0]
31
[1,6,5,4,7,3,9,5,3,7,8,4,1,1,4]
[4,3,1,3,5,9]
21
[2,5,6,4,4,0]
[7,3,8,0,6,5,7,6,2]
15
[]
[1]
1
[3,4,6,5]
[9,1,2,5,8,3]
11
[3,4,6,5]
[9,1,2,5,8,3]
1
[3,4,6,5]
[9,1,2,5,8,3]
2
[3,4,6,5]
[9,1,2,5,8,3]
3
[3,4,6,5]
[9,1,2,5,8,3]
4
[3,4,6,5]
[9,1,2,5,8,3]
5
[3,4,6,5]
[9,1,2,5,8,3]
6
[3,4,6,5]
[9,1,2,5,8,3]
7
[3,4,6,5]
[9,1,2,5,8,3]
8
[3,4,6,5]
[9,1,2,5,8,3]
9
[3,4,6,5]
[9,1,2,5,8,3]
10
[6, 7]
[6, 0, 4]
5
[3, 9]
[8, 9]
3
[1,1,1,1]
[1,1]
4
[0,0,1]
[0]
3

Outputs:

[7,6,7,5,1,0,2,1,0,1,0,5,6,0,5,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3,0]
[4,3,1,6,5,4,7,3,9,5,3,7,8,4,1,3,5,9,1,1,4]
[7,3,8,2,5,6,4,4,0,6,5,7,6,2,0]
[1]
[0,0,0,0,0,0,0,0,0,0,0]
[9]
[9,8]
[9,8,6]
[9,8,6,5]
[9,8,6,5,3]
[9,8,4,6,5,3]
[9,8,3,4,6,5,3]
[9,6,5,1,2,5,8,3]
[9,4,6,5,1,2,5,8,3]
[9,3,4,6,5,1,2,5,8,3]
[6,7,6,0,4]
[9,8,9]
[1,1,1,1]
[0,1,0]
*/