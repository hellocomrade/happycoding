#include <set>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
/*
1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

Example 1:

Input: nums = [8,2,4,7], limit = 4

Output: 2

Explanation: All subarrays are:

[8] with maximum absolute diff |8-8| = 0 <= 4.

[8,2] with maximum absolute diff |8-2| = 6 > 4.

[8,2,4] with maximum absolute diff |8-2| = 6 > 4.

[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.

[2] with maximum absolute diff |2-2| = 0 <= 4.

[2,4] with maximum absolute diff |2-4| = 2 <= 4.

[2,4,7] with maximum absolute diff |2-7| = 5 > 4.

[4] with maximum absolute diff |4-4| = 0 <= 4.

[4,7] with maximum absolute diff |4-7| = 3 <= 4.

[7] with maximum absolute diff |7-7| = 0 <= 4.

Therefore, the size of the longest subarray is 2.

Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5

Output: 4

Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.

Example 3:

Input: nums = [4,2,2,2,4,4,2,2], limit = 0

Output: 3


Constraints:
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9
- 0 <= limit <= 10^9

Hint1:

Use a sliding window approach keeping the maximum and minimum value using a data structure like a multiset from STL in C++.

Hint2:

More specifically, use the two pointer technique, moving the right pointer as far as possible to the right until the subarray is not valid (maxValue - minValue > limit),
then moving the left pointer until the subarray is valid again (maxValue - minValue <= limit). Keep repeating this process.

Observations:

I picked this problem up because it's used for a Google interview: https://leetcode.com/discuss/interview-experience/723830/google-l4-seattle-june-2020-offer

The problem looks for the max sliding window satisfies that any given element in range diff(nums[i,...j]) <= limit. In other words,
max(nums[i,...j]) - min(nums[i,...j]) <= limit.

So if we apply sliding window, we would need a way to always retrieve max and min inside a sliding window with any size in an efficient way.

My first attempt, following the hint1, using a mutiset (to handle duplicates) which is able to track both min and max, see longestSubarray_multiset_naive. Once the limit is broken,
left pointer needs to be moved after (plus 1) the max/min that is too big/small and therefore it's erased from the set. Any element with index
betwenn previous left pointer and new left pointer should be erased as well. Each element will be inserted and removed from the set exactly once.
However, due to the nature of set, the total time complexity is still O(NlogN).

The code can be simplifed, see longestSubarray_multiset. Instead of explicitly looking for the new left pointer, simply increase the left pointer
until the limit is met. During this iteration, remove all elements in the path from the set. This is still a O(NlogN) algorithm. However,
by using a different data structure with a slightly different logic, we can improve the algorithm to linear.

If remember leetcode 239 (Sliding Window Maximum), https://github.com/hellocomrade/happycoding/blob/master/leetcode/SlidingWindowMaximum.cpp

Using a deque to maintain an ordered list for storing max/min, see longestSubarray. In this version, 2 deques are used to maintain the max and min
list for current sliding window. When limit is broken, shrinking the window from left and remove any element on the deques that is out of shrinked
window. Again, this is a linear solution.

Much better solutions are covered here: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/discuss/609771/JavaC%2B%2BPython-Deques-O(N)
*/
class SolutionLongestContinuousSubarrayAbsDiffLimit {
public:
	int longestSubarray(vector<int>& nums, int limit) {
		int len = (int)nums.size(), ans = 1, l = 0;
		deque<int> qmax, qmin;
		for (int i = 0; i < len; ++i) {
			while (false == qmax.empty() && qmax.back() < nums[i]) qmax.pop_back();
			qmax.push_back(nums[i]);
			while (false == qmin.empty() && qmin.back() > nums[i]) qmin.pop_back();
			qmin.push_back(nums[i]);
			while (qmax.front() - qmin.front() > limit) {
				if (qmax.front() == nums[l]) qmax.pop_front();
				if (qmin.front() == nums[l]) qmin.pop_front();
				++l;
			}
			ans = std::max(ans, i - l + 1);
		}
		return ans;
	}
	int longestSubarray_multiset(vector<int>& nums, int limit) {
		int ans = 1, len = (int)nums.size();
		multiset<int> mset;
		for (int i = 0, l = 0; i < len; ++i) {
			mset.insert(nums[i]);
			while (mset.size() > 0 && *mset.rbegin() - *mset.begin() > limit)
				mset.erase(mset.find(nums[l++]));
			ans = std::max(ans, i - l + 1);
		}
		return ans;
	}
	int longestSubarray_multiset_naive(vector<int>& nums, int limit) {
		int ans = 1, len = (int)nums.size();
		multiset<pair<int, int>> mset;
		for (int i = 0, l = 0, prev_l = 0; i < len; ++i) {
			mset.insert(std::make_pair(nums[i], i));
			while (mset.size() > 0 && mset.rbegin()->first - mset.begin()->first > limit) {
				prev_l = l;
				if (mset.rbegin()->second < mset.begin()->second)
					l = mset.rbegin()->second + 1, mset.erase(--mset.end());
				else
					l = mset.begin()->second + 1, mset.erase(mset.begin());
				while (prev_l < l) {
					mset.erase(std::make_pair(nums[prev_l], prev_l));
					++prev_l;
				}
			}
			ans = std::max(ans, i - l + 1);
		}
		return ans;
	}
};
/*
Test cases:

[10]
0
[8,2,4,7]
4
[10,1,2,4,7,2]
5
[4,2,2,2,4,4,2,2]
0
[1,2,5,3,7,6,1]
3

Outputs:

1
2
4
3
3
*/