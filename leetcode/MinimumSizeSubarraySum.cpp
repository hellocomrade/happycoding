#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/minimum-size-subarray-sum/
/*
209. Minimum Size Subarray Sum

Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

click to show more practice.

More practice:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).

Observation:
My initial thought is using prefix sum. And then we will have a non decreasing array considering the fact
that all elements are positive. And then, we could find the lower_bound of nums[i] - s on this prefix sum
array and pick the closest interval from i to that position. Overall is O(NlogN) time and O(1) space if
reusing the input array for prefix sum.

However, if you take a close look, again all elements are positive, you could solve this using two pointers
in O(N) time and O(1) space.

At beginning, both left and right pointers are at index 0, then increase right point until the sum between
left poniter and right pointer is no less than s. We then examine if this right - left is smaller. Then, we
increase the left pointer, which give we a small sum and see if this smaller sum is still no less than s. If so,
we find a closer interval. Keep this going until right pointer is equal to the lengh of the array.

Note, in the inner while loop, we didn't bother to check if pointer l exceeds i or len because s is guaranteed to be
positive and all elements in nums are positive. Therefore, when l catches up with i, the sum for sliding window is zero.
The loop will exit.

Update on 6/25/2018

Other than using sliding window template, we could use prefix sum plus binary search as I mentioned above.
We could take advantage of std::lower_bound. Prefix sum can be done in place which ignore the possibility of integer overflow though.
This is a O(NLogN) solution with O(1) space.
*/
class SolutionMinimumSizeSubarraySum {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		int len = (int)nums.size(), ans = len + 1, l = 0;
		long long sum = 0LL;
		for (int i = 0; i < len; ++i) {
			sum += nums[i];
			while (sum >= s) {
				ans = std::min(ans, i - l + 1);
				sum -= nums[l++];
			}
		}
		return ans == len + 1 ? 0 : ans;
	}
	int minSubArrayLen1(int s, vector<int>& nums) {
		int len = (int)nums.size(), ans = len + 1;
		for (int i = 1; i < len; ++i) nums[i] += nums[i - 1];
		for (int i = 0; i <= len; ++i) {
			auto itor = std::lower_bound(nums.begin() + i, nums.end(), s + (0 == i ? 0 : nums[i - 1]));
			if (itor != nums.end()) ans = std::min(ans, (int)std::distance(nums.begin() + i, itor + 1));
		}
		return len + 1 == ans ? 0 : ans;
	}
	int minSubArrayLen2(int s, vector<int>& nums) {
		int len = nums.size(), ans = len + 1;
		long long sum = 0;
		if (len < 1)return 0;
		int i = 0, j = 0;
		while (j <= len) {
			if (sum >= s) {
				ans = std::min(ans, j - i);
				sum -= nums[i++];
			}
			else {
				if (j == len)break;
				sum += nums[j++];
			}
		}
		return ans == len + 1 ? 0 : ans;
	}
};
