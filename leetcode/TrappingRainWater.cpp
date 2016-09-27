#include <cassert>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/trapping-rain-water/
/*
42. Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

       M
   M   MM M
_M_MM_MMMMMM

The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water are being trapped.

Observations:
First glance makes me think "skyline" algorithm. A classic algorithm uses a stack:

Put the first non-zero element on the stack, keep pushing elements then on the stack until
there is an element K that is no less than the top of the stack as the right boundary of the basin. Then keeping poping
the element T as the left boundary of the basin from the stack (move backward) to calcuate the area for water between K and T. Because of the way we operate the stack,
at any given moment, the elements on the stack is in a non-increasing order from bottom to the top of the stack. Therefore, the top
of the stack is where the smallest element is located, like a min-heap.

As for the area, the width is Index(K) - Index(T) + 1 and the height is K - T - delta, given delta as the element that was poped up previously
from the stack, which was involved as the height for the calcuation of the area of lower level.


Also don't forget the last round! A typical mistake I could make...It's out of the while loop. We may find the first element on the top of
the stack that is greater than K

Is this good enough? No, well, according to the Leetcode stats. Here is a better one without using
any extra space: https://discuss.leetcode.com/topic/5125/sharing-my-simple-c-code-o-n-time-o-1-space

Two pointers appraoch, one from the left and one from the right. The idea is: if we could find a boundary
on the left side is lower than the max right boundary so far, we can safely count the difference between this left
boundary (maxFromLeft) and the current left as the area for water. Same applies if right boundary is smaller,
we count from right though.

	  M
      M	    M
M     M     M
M     M     M
M     M   M M
M M   M   M M
M M M M M M M
5 2 1 7 1 3 6

For above example, the count will start from left since maxFromLeft is 5 and rightFromRight is 6. We are confident
to say: at height[1] = 2, (5 - 2) will contain water for sure. This continues to be true until height[3], where we will
find a new maxFromLeft. At this moment, maxFromRight = 6 is smaller, we could tell, at heigt[5] = 3, (6 -3) will be all
under the water.
*/
class SolutionTrappingRainWater {
public:
	//O(N) time, 6ms and O(1) space
	int trap(const vector<int>& height) {
		long long ans = 0LL;
		int left = 0, right = height.size() - 1, maxFromLeft = -1, maxFromRight = -1;
		/*
		it appears '<=' between left and right will slow than the whole algorithm based upon
		the test cases on Leetcode. Actually, the '==' condition is redundant
		*/
		while (left < right) {
			if (height[left] <= height[right]) {
				maxFromLeft = std::max(maxFromLeft, height[left]);
				ans += maxFromLeft - height[left++];
			}
			else {
				maxFromRight = std::max(maxFromRight, height[right]);
				ans += maxFromRight - height[right--];
			}
		}
		return ans;
	}
	//O(N) time, 12ms and O(N)space
	int trap1(const vector<int>& height) {
		long long ans = 0LL;
		int dist = -1, delta = 0;
		/*
		Is pair really necessary? No, by theory. A stack<int> is sufficient: we only
		need to store index and the height can always be retrived through height[stk.top()].
		However, it could be 10 ms slower if we do so. This could contribute to slow
		array random access in C++ and also more obviously, if we put pair on stack, we could
		save the extra access to the array...Anyway, we double the extra storage to buy some
		extra time...
		*/
		stack <std::pair<int, int>> stk;
		for (int h : height) {
			++dist;
			if (stk.empty() && h == 0)continue;
			if (stk.empty() || stk.top().second > h)stk.emplace(dist, h);
			else {
				delta = stk.top().second;stk.pop();
				while (false == stk.empty() && stk.top().second <= h) {
					//if delta == stk.top().second, we have elements with the same height on stack, no need for calcuation.
					if (stk.top().second - delta > 0) {
						//We only calculate the area above the previous calucation. The previous baseline is stored in delta.
						ans += std::min(stk.top().second - delta, h - delta) * (dist - stk.top().first - 1);
						delta = stk.top().second;
					}
					stk.pop();
				}
				/*
				Extra care for the situation stk.top().second > h, which forms the leftmost
				boundary of the current basin if exists.
				*/
				if (false == stk.empty())ans += (h - delta) * (dist - stk.top().first - 1);
				stk.emplace(dist, h);
			}
		}
		return ans;
	}
};
void TestTrappingRainWater() {
	SolutionTrappingRainWater so;
	assert(0 == so.trap(vector<int>{0}));
	assert(0 == so.trap(vector<int>{27}));
	assert(0 == so.trap(vector<int>{2, 2}));
	assert(0 == so.trap(vector<int>{3, 8}));
	assert(2 == so.trap(vector<int>{10, 8, 10}));
	assert(9 == so.trap(vector<int>{4, 2, 0, 1, 5}));
	assert(6 == so.trap(vector<int>{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
	assert(0 == so.trap(vector<int>{0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 1, 0}));
	assert(8 == so.trap(vector<int>{3, 1, 1, 1, 1, 3}));
	assert(7 == so.trap(vector<int>{3, 1, 1, 2, 1, 3}));
	assert(6 == so.trap(vector<int>{3, 1, 2, 2, 1, 3}));
	assert(5 == so.trap(vector<int>{3, 2, 2, 2, 1, 3}));
	assert(4 == so.trap(vector<int>{3, 2, 2, 2, 2, 3}));
	assert(27 == so.trap(vector<int>{0, 3, 2, 1, 3, 5, 2, 0, 1, 3, 3, 2, 2, 6, 2, 3, 1, 2, 0}));
}