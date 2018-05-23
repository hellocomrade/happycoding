#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/rectangle-area/
/*
223. Rectangle Area

Find the total area covered by two rectilinear rectangles in a 2D plane.

Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.

Rectangle Area

Example:

Input: -3, 0, 3, 4, 0, -1, 9, 2

Output: 45

Note:
Assume that the total area is never beyond the maximum possible value of int.

Observations:
Basic computational geometry! Calculate the sum of two rectangles and substract possible overlap area.

The problem is transformed to dedicde the area of overlap.

First of all, how can we decide if two rectangles are intersected?

https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other

(RectA.Left <= RectB.Right && RectA.Right >= RectB.Left && RectA.Top >= RectB.Bottom && RectA.Bottom <= RectB.Top)

The above conditions are always true regardless the relative positions of RectA and RectB.

Then the intersected area RectC, which is a rectangle or square, can be decided by:

If we sort X[A, C, E, G] and Y[B, D, F, H] respectively in ascending order, RectC's right = X[1], left = X[2], bottom = Y[1], bottom = Y[2].

In other words, it's right/left and bottom/top are always the middle two elements of X and Y after sorting.

Therefore we have computeArea2.

The above approach requires sorting on array, which is not necessary due to the fact there is one more constraint:

A <= C, E <= G; B <= D, F <= H

So, the middle two of Xs will be in [MAX(A, E), MIN(C, G)]; the middle two of Ys will be in [MAX(B, F), MIN(D, H)]

Note that the order of middle twos in above two arrays in unknown without knowing if two rectangles are intersected. If they are,
it's guaranteed MAX(A, E) <= MIN(C, G) and MAX(B, F) <= MIN(D, H).

Therefore we have computeArea1.

Actually, since we know the fact that MAX(A, E) > MIN(C, G) and MAX(B, F) > MIN(D, H) are true if and only if two rectangles are NOT intersected,
the check on whether two rects are overlapped can be ignored as long as we make sure (MIN(C, G) - MAX(A, E)) and (MIN(D, H) - MAX(B, F)) are NOT negative.

The exception case comes from integer overflow:

Given RectA [-1500000001, 0], [-1500000000, 1]; RectB [1500000000, 0], [1500000001, 1]

Since MIN(C, G) = -1500000000 and MAX(A, E) = 1500000000, the substraction of them will overflow 4 bytes integer..., in order to keep the "simple" syntax of:

std::max(0L, std::min(C, G) * 1L - std::max(A, E)) * std::max(0L, std::min(D, H) * 1L - std::max(B, F));

We have to make sure the substraction is done between two longs, not ints.
*/
class SolutionRectangleArea {
public:
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		return (C - A) * (D - B) + (G - E) * (H - F) - std::max(0L, std::min(C, G) * 1L - std::max(A, E)) * std::max(0L, std::min(D, H) * 1L - std::max(B, F));
	}
	int computeArea1(int A, int B, int C, int D, int E, int F, int G, int H) {
		int overlap = 0;
		if (A <= G && C >= E && D >= F && B <= H)
			overlap = std::max(0, std::min(C, G) - std::max(A, E)) * std::max(0, std::min(D, H) - std::max(B, F));
		return (C - A) * (D - B) + (G - E) * (H - F) - overlap;
	}
	int computeArea2(int A, int B, int C, int D, int E, int F, int G, int H) {
		int overlap = 0;
		if (A <= G && C >= E && D >= F && B <= H) {
			vector<int> xs{ A, C, E, G }, ys{ B, D, F, H };
			std::sort(xs.begin(), xs.end()), std::sort(ys.begin(), ys.end());
			overlap = (xs[2] - xs[1]) * (ys[2] - ys[1]);
		}
		return (C - A) * (D - B) + (G - E) * (H - F) - overlap;
	}
};
/*
Test cases:

-3
0
3
4
0
-1
9
2
-1
-1
10
8
-4
-2
12
3
0
0
8
7
0
2
4
7
-9
6
-1
8
0
0
2
4

Outputs:

45
135
56
24
*/