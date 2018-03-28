#include <cassert>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/largest-rectangle-in-histogram/
/*
84. Largest Rectangle in Histogram

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

6
5 -
- -
- -   3
2 1 - - 2 -
-   - - - -
- - - - - -

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

6
5 -
- -
- -
- -
- -
- -

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.

Observations:

OK, I knew I will need to use a stack coz I found this one through HackerRank, which already categorized this one under Stack.

Then, how should we take advantage of stack?

Take a close look on the definition of largest rectangle: it's formed by the common least heights. For example:

Let's leave alone the "largest" for the time being,

Given [1, 3, 4, 2] can forms a rectangle with the width of 2 if the height of the rectangle is 3;
However, if starting from index 0, height = 1, [1, 3, 4, 2] can forms a rectangle with the width of 4;

Therefore, if we apply greedy approach here by checking on how far each bar can go in terms of width to form a rectangle with the height of this bar, we
shall have a solution. By using Bar A's height H as the edge (height) of the rectangle, such a rectangle can be extended as much as it can till
a new bar B, with a height H1, which H1 < H. At this moment, the largest rectangle starting from A is found and it ends at the bar before B.

Stack appears to be perfect for this job since we can't tell if B is discovered for A when we reach A in the loop.

- Put bar onto the stack as long as it's height is no less than the top of the stack. Therefore, the heights on the stack maintains in an ascending order on the stack,
we actually only need to put the index of heights on the stack, so we can access the height on the stack by heights[stk.top()];

- If the current bar's height is less than the top of the stack, "largest rectangles" can be concluded now. Therefore pop any element that is greater than
the current bar's height and caculate their area; This pop operation is done once the remaining bars on the stack is no greater than current height. Then,
we push current height onto the stack. Why? We use greedy here, those heights on the bar may form larger rectangles if the bar down the road is higher.

- While poping from the stack, calculate the max area, this is the tricky part. With the height decided, now it's time to find out the width:

Given current index i that meets heights[i] < heights[stack.top()], the possible largest rectangle is calculated by (i - the index of the next to the top of the stack - 1) * heights[stack.top()]

In plain language: each height on the stack can form the largest rectangle with the width from its current index till the index of the previous minimum.

In case of the index at the bottom of the stack, say k, heights[k] is the smallest height till index i, in this case, its width is i no matter where index k is, of course, k < i.


In terms of implementation, after pushing the last element in heights onto stack, we will have to examine the stack after the loop exits, which looks ugly. The way
I solved this is by intentionally allowing loop running till len(heights). At i = len(heights), we know the elements on the stack is in ascending order for sure. Therefore,
same logic can be applied for the case (false == stk.empty() && heights[i] < heights[stk.top()]).

I saw other people solving this by prepending or appending elements onto heights...

This is a linear solution with O(N) space that can be considered as greedy algorithm. I also saw others using divide and conquer, which is interesting but probably suffers
a penalty on time complexity.
*/
class SolutionLargestRectangleInHistogram {
public:
	int largestRectangleArea(const vector<int>& heights) {
		stack<int> stk;
		int ans = 0, len = (int)heights.size();
		for (int i = 0, j = 0; i <= len; ++i) {
			while (false == stk.empty() && (len == i || heights[i] < heights[stk.top()])) {
				j = stk.top(), stk.pop();
				ans = std::max(ans, (i - 1 - (false == stk.empty() ? stk.top() : -1)) * heights[j]);
			}
			if (i < len) stk.push(i);
		}
		return ans;
	}
};
void TestLargestRectangeleInHistogram() {
	SolutionLargestRectangleInHistogram so;
	assert(10 == so.largestRectangleArea(vector<int>{2, 1, 5, 6, 2, 3}));
	assert(16 == so.largestRectangleArea(vector<int>{2, 1, 2, 2, 2, 5, 6, 2, 3, 2}));
	assert(3 == so.largestRectangleArea(vector<int>{2, 1, 2}));
	assert(8 == so.largestRectangleArea(vector<int>{1, 5, 2, 3, 2}));
	assert(24 == so.largestRectangleArea(vector<int>{10, 8, 8, 1, 4, 5, 6, 2}));
	assert(24 == so.largestRectangleArea(vector<int>{10, 8, 8, 1, 4, 5, 6, 2, 3, 3, 6}));
}
/*
Test cases:

[2,1,5,6,2,3]
[2,1,2,2,2,5,6,2,3,2]
[]
[1]
[0]
[1,2]
[2,1]
[1,2,1]
[1,1,1]
[2,1,2]
[10,8,8,1,4,5,6,2]
[1,2,3,4]
[3,2,1,4]
[4,3,2,1]
[2,4,1,3]
[4,5,1,2,3]
[1,5,2,3,2]
[10,8,8,1,4,5,6,2,3,3,6,7,8,4,5,5,2,6,7,3]
[10,19,18,18,16,23,17,18,19,20,20,15,8,16,16,23,15,11,22]
[10,8,8,7,9,7,6,5,8,0,3,4,2,1,4,4,5,6,0,6,6,8,9,5,10,7,7,7,3,3,3,0,0,0,7,8,9,10]

Outputs:

10
16
0
1
0
2
2
3
3
3
24
6
4
6
4
8
8
32
165
45
*/