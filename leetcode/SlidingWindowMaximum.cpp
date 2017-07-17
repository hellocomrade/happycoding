#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

//https://leetcode.com/problems/sliding-window-maximum/
/*
239. Sliding Window Maximum

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7      3
1 [3  -1  -3] 5  3  6  7       3
1  3 [-1  -3  5] 3  6  7       5
1  3  -1 [-3  5  3] 6  7       5
1  3  -1  -3 [5  3  6] 7       6
1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's size for non-empty array.

Follow up:
Could you solve it in linear time?

Observation:
Well, it appears this can be done anyway in linear time, even we use the naive approach, in maxSlidingWindow2.
We do k comparison for (n - k) times. The total is O(k(N - k)), given 1 <= k <= N, it's O(N)

Well, can we make it faster? Using deque!

The idea is: if nums[i] is smaller than the tail on deque, append the element to the deque. Or, pop any element
from deque that is less than nums[i]. This is based upon the fact that if nums[i] can be reached in the window with size k,
the previous smaller elements on the deque is useless for determining the max value in the window since nums[i] will be a
better candidate by far. Therefore, those smaller ones can be removed.

In this setup, the deque forms a monotonic descending array.

The only complications left are:

- When to remove the front? Well, when it's moved out of the window
- When to take the front as part of the answer? any time when the index is no less than (k - 1), which means the ever first
window has been built.
*/
class SolutionSlidingWindowMaximum {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		size_t len = nums.size(), idx = 0;
		vector<int> ans;
		if (len > 0 && k > 0 && k <= len) {
			deque<int> dq;
			for (size_t i = 0; i < len; ++i) {
				while (false == dq.empty() && nums[dq.back()] < nums[i])dq.pop_back();
				dq.push_back(i);
				if (i - dq.front() + 1 > k)dq.pop_front();
				if (i >= k - 1)ans.push_back(nums[dq.front()]);
			}
		}
		return ans;
	}
	//std::pair is not necessary, storing index is sufficient
	vector<int> maxSlidingWindow1(vector<int>& nums, int k) {
		size_t len = nums.size(), idx = 0;
		vector<int> ans;
		if (len > 0 && k > 0 && k <= len) {
			deque<std::pair<int, int>> dq;
			for (size_t i = 0; i < len; ++i) {
				while (false == dq.empty() && dq.back().first < nums[i])dq.pop_back();
				dq.push_back(std::make_pair(nums[i], i));
				if (i - dq.front().second + 1 > k)dq.pop_front();
				if (i >= k - 1)ans.push_back(dq.front().first);
			}
		}
		return ans;
	}
	//Slowest one, but still a linear algorithm...
	vector<int> maxSlidingWindow2(vector<int>& nums, int k) {
		size_t len = nums.size(), start = 0;
		vector<int> ans;
		if (len > 0 && k > 0 && k <= len) {
			while (start + k <= len) {
				ans.push_back(*max_element(nums.begin() + start, nums.begin() + start + k));
				++start;
			}
		}
		return ans;
	}
};