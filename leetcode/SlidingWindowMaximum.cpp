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

The idea is: if nums[i] is smaller than the tail on deque, append the element to the deque. Otherwise, pop any element
from deque that is less than nums[i], then push nums[i] to the end of the deque (duplicates are welcome). This is based upon the fact that if nums[i] can be reached in the window with size k,
the previous smaller elements on the deque is useless for determining the max value in the window since i is closer to
current window and future windows. Therefore, those smaller ones can be removed.

In this case, the deque forms a monotonic queue in descending order.

The only complications left are:

- When to remove the front? Well, when it's moved out of the window with size k.
- When to take the front as part of the answer? Any time when the index is no less than (k - 1), which means after the ever first
  window has been formed.

***Update on 2019-06-30***

Redo as maxSlidingWindow. Comparing with the previous maxSlidingWindow0. The major difference is the
condition to pop_front: instead of (i - k + 1) > dq.front(), we do (i - k == deque.front()). It might look less safer,
but exactly the same actually. Since every element will be visited exactly once, it's guaranteed the deque.front() with value
(i - k) will be visited exactly when deque.front() is moved out of the window.

The deque in this problem is maintained as a monotonic queue in descending order from front to tail. For comparsion purpose,
Monotonic Pair (https://github.com/hellocomrade/happycoding/blob/master/MonotonicPair.cpp) uses a monotonic stack.
It boosts the performance from O(NlogN) to O(N). Looks like monotonic array/queue/stack can help solving problem
in linear time.

Since every element is visited twice (in deque once and out deque once), the overall time complexity is O(N).

I also tried to solve this using priority queue. Building a priority queue with size K takes only O(K) time.
However, since there are (N - K) queues to build, time cemplexity is still O((N - K)K).
*/
class SolutionSlidingWindowMaximum {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		int len = (int)nums.size();
		vector<int> ans(0 == len ? 0 : len - k + 1);
		deque<int> deque;
		for (int i = 0, j = 0; i < len; ++i) {
			while (false == deque.empty() && nums[deque.back()] < nums[i]) deque.pop_back();
			deque.push_back(i);
			if (i - k == deque.front()) deque.pop_front();
			if (i >= k - 1) ans[j++] = nums[deque.front()];
		}
		return ans;
	}
	vector<int> maxSlidingWindow0(vector<int>& nums, int k) {
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
	//Slowest one using priority queue
	vector<int> maxSlidingWindow3(vector<int>& nums, int k) {
		int len = (int)nums.size();
		if (0 == len) return vector<int>();
		vector<int> ans(len - k + 1), heap(k);
		for (int i = 0; i <= len - k; ++i) {
			std::copy(nums.begin() + i, nums.begin() + i + k, heap.begin());
			std::make_heap(heap.begin(), heap.end());
			ans[i] = heap.front();
		}
		return ans;
	}
};
/*
Test cases:

[]
0
[1,3,-1,-3,5,3,6,7]
3
[3,8,2,4,1,7,9,1,2,3]
3
[2]
1
[2,3]
2
[2,3,7,2,7,8,6,3,4,2,7,10]
1
[2,3,7,2,7,8,6,3,4,2,7,10]
2
[2,3,7,2,7,8,6,3,4,2,7,10]
3
[2,3,7,2,7,8,6,3,4,2,7,10]
4
[2,3,7,2,7,8,6,3,4,2,7,10]
5
[2,3,7,2,7,8,6,3,4,2,7,10]
6
[2,3,7,2,7,8,6,3,4,2,7,10]
7
[2,3,7,2,7,8,6,3,4,2,7,10]
8
[2,3,7,2,7,8,6,3,4,2,7,10]
9
[2,3,7,2,7,8,6,3,4,2,7,10]
10
[2,3,7,2,7,8,6,3,4,2,7,10]
11
[2,3,7,2,7,8,6,3,4,2,7,10]
12

Outputs:

[]
[3,3,5,5,6,7]
[8,8,4,7,9,9,9,3]
[2]
[3]
[2,3,7,2,7,8,6,3,4,2,7,10]
[3,7,7,7,8,8,6,4,4,7,10]
[7,7,7,8,8,8,6,4,7,10]
[7,7,8,8,8,8,6,7,10]
[7,8,8,8,8,8,7,10]
[8,8,8,8,8,8,10]
[8,8,8,8,8,10]
[8,8,8,8,10]
[8,8,8,10]
[8,8,10]
[8,10]
[10]
*/