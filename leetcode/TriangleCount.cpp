#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/valid-triangle-number
/*
611. Valid Triangle Number

Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

Example 1:

Input: [2,2,3,4]

Output: 3

Explanation:

Valid combinations are:

2,3,4 (using the first 2)

2,3,4 (using the second 2)

2,2,3

Note:

- The length of the given array won't exceed 1000.
- The integers in the given array are in the range of [0, 1000].

Observations:

A little bit geometry here: for a valid triangle, any the length sum of two edges shall be greater than the length of third edge.
Therefore, each edge has to be checked, total 3 times.

It's intuitive to sort the array first. In an array with ascending order, given i, j, k as indexes with i < j < k. One only needs
to check nums[i] + nums[j] > nums[k], the other two edges are checked automatically because of sorting, given nums[i] <= nums[j] <= nums[k].
Of course, this is true if and only if nums contains only positive number. Since 0 is valid in nums, it's an edge case. In fact, 0 is not
a valid edge at all.

In terms of implementation, the naive approach will take O(N^3) time if one pick two elements and slide over the array to check the possible third edge.
Since the array is sorted, BS is helpful to find k, which nums[i] + nums[j] <= nums[k], then there should be (k - j - 1) edges valid to form a triangle
with nums[i] and nums[j]. Using BS will decrease the time complexity to O(N^2logN).

After a close look, one may notice that k always move to the right for any nums[i], no matter which nums[j] is picked. The prove is simple:

If k is found to satisify nums[i] + nums[j] <= nums[k], then for (nums[i], nums[j + 1]), all the edges in between (j, k) are still good for a valid triangle.
The scan can safely starts from k for (nums[i], nums[j + 1]). In other word for any given nums[i], k is an accumulated sum.

Therefore, the time complexity is O(N^2) and space compelxity is O(logN) due to quick sort.

Edge case:

[0,0,1,1]. In this case, k - j - 1 may result in a negative integer, one could do std::max(0, k - j - 1). But a more explicit way would be:

if (1 > nums[i]) continue;

Which makes perfect sense since no edge in a triangle could be less than 1 if only integer is allowed.
*/
class SolutionTriangleCount {
public:
	int triangleNumber(vector<int>& nums) {
		int len = (int)nums.size(), ans = 0;
		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < len - 2; ++i) {
			if (1 > nums[i]) continue;
			for (int j = i + 1, k = i + 2; j < len - 1; ++j) {
				while (k < len && nums[i] + nums[j] > nums[k]) ++k;
				//cout << i <<','<<j<<','<<k<<endl;
				//ans += std::max(0, k - j - 1);
				ans += k - j - 1;
			}
		}
		return ans;
	}
};
/*
Test cases:

[2,2,3,4]
[4,4,4,4]
[3,7,2,8,5,3,6]
[]
[0]
[1,2]
[1,2,3]
[0,1,0,1]

Outputs:

3
4
19
0
0
0
0
0
*/