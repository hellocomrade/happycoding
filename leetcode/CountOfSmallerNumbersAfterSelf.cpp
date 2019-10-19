#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/count-of-smaller-numbers-after-self/
/*
315. Count of Smaller Numbers After Self

You are given an integer array nums and you have to return a new counts array. The counts array has the
property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Input: [5,2,6,1]

Output: [2,1,1,0]

Explanation:

- To the right of 5 there are 2 smaller elements (2 and 1).
- To the right of 2 there is only 1 smaller element (1).
- To the right of 6 there is 1 smaller element (1).
- To the right of 1 there is 0 smaller element.

Observations:

This is a variation of Codility "Array Inversion Count": https://github.com/hellocomrade/happycoding/blob/master/ArrayInversionCount.cpp

Therefore, can be solved using merge sort. I took the "template" from ArrayInversionCount.cpp for
an iterative bottom up merge sort implementation. However, my first attempt was proved less successful
due to the fact that the inner for loop to update count is O(N). So the entire algorithm is close to O(N^2).

The pitfall is the sort is in ascending order however the question asks "smaller than at right". So
the merge sort should be implemented in descending order. In such a way, the counter for each element can
be updated one by one on the fly since every element with index >= ir is smaller than numps[il].

I use two vectors of pair<int, int> for merge sort. The pair is (nums[i], i).

Overall time complexity is NlogN and space complexity is O(N).
*/
class SolutionCountOfSmallerNumbersAfterSelf {
public:
	vector<int> countSmaller(const vector<int>& nums) {
		int len = (int)nums.size();
		vector<int> ans(len, 0);
		vector<std::pair<int, int>> aux(len), numps(len);
		for (int i = 0; i < len; ++i) numps[i] = std::make_pair(nums[i], i);
		function<void(int, int, int)> merge = [&](int l, int m, int r) -> void {
			int il = l, ir = m, ia = l;
			while (il < m && ir < r)
				aux[ia++] = (numps[il].first > numps[ir].first) ? (ans[numps[il].second] += r - ir, numps[il++]) : numps[ir++];
			while (il < m) aux[ia++] = numps[il++];
			while (ir < r) aux[ia++] = numps[ir++];
		};
		for (int i = 1; i < len; std::copy(aux.begin(), aux.end(), numps.begin()), i <<= 1) {
			for (int j = 0; j + i <= len; j += 2 * i)
				merge(j, j + i, std::min(len, j + 2 * i));
		}
		return ans;
	}
	//Really slow, O(N^2) due to the for loop inside while (il < m && ir < r)
	vector<int> countSmaller1(vector<int>& nums) {
		int len = (int)nums.size();
		vector<int> ans(len, 0);
		vector<std::pair<int, int>> aux(len), numps(len);
		for (int i = 0; i < len; ++i) numps[i] = std::make_pair(nums[i], i);
		function<void(int, int, int)> merge = [&](int l, int m, int r) -> void {
			int il = l, ir = m, ia = l;
			while (il < m && ir < r) {
				if (numps[il].first <= numps[ir].first) aux[ia++] = numps[il++];
				else {
					for (int i = il; i < m; ++i) ++ans[numps[i].second];
					aux[ia++] = numps[ir++];
				}
			}
			while (il < m) aux[ia++] = numps[il++];
			while (ir < r) aux[ia++] = numps[ir++];
		};
		for (int i = 1; i < len; std::copy(aux.begin(), aux.end(), numps.begin()), i <<= 1) {
			for (int j = 0; j + i <= len; j += 2 * i)
				merge(j, j + i, std::min(len, j + 2 * i));
		}
		return ans;
	}
};
void TestCountOfSmallerNumbersAfterSelf() {
	SolutionCountOfSmallerNumbersAfterSelf so;
	so.countSmaller(vector<int> {5, 2, 6, 1});
}
/*
Test cases:

[5,2,6,1]
[5,5,5]
[]
[1]
[1,2]
[2,1]
[19,25,11,9,11]
[19,25,11,9,11,25,23,17]

Outputs:

[2,1,1,0]
[0,0,0]
[]
[0]
[0,0]
[1,0]
[3,3,1,0,0]
[4,5,1,0,0,2,1,0]
*/