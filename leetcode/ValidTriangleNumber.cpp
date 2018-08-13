#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/valid-triangle-number/
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

The geometry nature of a triangle rquires the sum of length for any 2 edges shall be greater than the third edge.
For given index i, j, k, the following three conditions have to be met to form a valid triangle:

nums[i] + nums[j] > nums[k];

nums[i] + nums[k] > nums[j];

nums[k] + nums[j] > nums[i];

If nums is an array with ascending order, then only one of three conditions shall be checked:

nums[i] + nums[j] > nums[k], given i < j < k;

Applying two pointers here, by any given i and j, finding valid ks takes O(N^2) time and overall is O(N^3) for all i, j pairs.

Can we reduce the time complexity here a bit? Well, since nums is sorted now, it's nature to think of using BS. Once could
find k' by std::lower_bound() against nums[i] + nums[j] in range of [j + 1, nums.end()), then the valid count is k' - j - 1.
Time complexity here is O(N^2logN).

Is there a better solution like 3sum? Taking a closer look, one may find that if k has been found for nums[i] + nums[j] == nums[k],
the search for the next k for nums[i] + nums[j + 1] can start right at current k for (i, j) simply because nums[j + 1] >= nums[j]. Therefore,
no need to restart the search from (j + 2) for k. So, k actually only goes toward right for any given i on searching (j, k). So, this can be
done in O(N) and overall is O(N^2) with O(logN) space due to quick sort.

The edge case is number 0. Zero is not a valid edge length for a triangle, it might be wise to remove it from searching up front. Or, one could
tolerate it and rules it out in the inner loop. Instead of

ans += k - j - 1;

Have to do:

ans += std::max(0, k - j - 1);

With 0 involded, k - j - 1 could be less than zero.
*/
class SolutionValidTriangleNumber {
public:
	int triangleNumber(vector<int>& nums) {
		int len = (int)nums.size(), ans = 0;
		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < len - 2; ++i) {
			if (1 > nums[i]) continue;
			for (int j = i + 1, k = i + 2; j < len - 1; ++j) {
				while (k < len && nums[i] + nums[j] > nums[k]) ++k;
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