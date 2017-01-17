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
*/
class SolutionMinimumSizeSubarraySum{
public:
	int minSubArrayLen(int s, vector<int>& nums) {
	    int len = (int)nums.size();
            int ans = len + 1, sum = 0, l = 0;
            for(int i = 0; i < len; ++i) {
                sum += nums[i];
                while(sum >= s) {
                    ans = std::min(ans, i - l + 1);
               	    sum -= nums[l++];
            	}
       	    }
            return ans == len + 1 ? 0 : ans;	
	}
	int minSubArrayLen1(int s, vector<int>& nums) {
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
