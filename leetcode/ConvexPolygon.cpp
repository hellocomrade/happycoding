#include <vector>

using namespace std;

//https://www.lintcode.com/problem/convex-polygon
/*
469. Convex Polygon

Description
Given a list of points that form a polygon when joined sequentially, find if this polygon is convex (Convex polygon definition).

There are at least 3 and at most 10,000 points.
Coordinates are in the range -10,000 to 10,000.
You may assume the polygon formed by given points is always a simple polygon (Simple polygon definition). In other words, we ensure that exactly two edges intersect at each vertex, and that edges otherwise don't intersect each other.
Have you met this question in a real interview?

Example

Given points = [[0, 0], [0, 1], [1, 1], [1, 0]],

return True.

Explanation:
https://lintcode-media.s3.amazonaws.com/problem/E3N5G.png

Given points = [[0, 0], [0, 10], [10, 10], [10, 0], [5, 5]],

return False.

Explanation:
https://lintcode-media.s3.amazonaws.com/problem/E3f02.png

Observations:

Leetcode requires a subscription for this problem. Fortunately, lintcode offers it for free.

This is a simplified version of classic Convext Hull problem. According to the definition of "Convedt Polygon"

https://en.wikipedia.org/wiki/Convex_polygon

All adjacent edges shall make the turn to the same direction, either left or right, depending on the starting vertex.
For example, given the same polygon with different starting vertex:

[[0, 0], [1, 0], [1, 1], [0, 1]]

[[1, 0], [0, 0], [0, 1], [1, 1]]

Adjacent edges in the first one always make left turn and the edges in the second one make right turn.

One can simply loop through all vertexes and check the turning direction for V[i], V[i + 1] and V[i + 2].

How to do it? Cross product.

"Cross products allow us to answer this question without computing the angle. As shown in Figure 33.2, we simply check whether
directed segment P(i)P(i+2) is clockwise or counterclockwise relative to directed segment P(i)P(i+1).
To do this, we compute the cross product (P(i+2) - P(i)) × (P(i+1) - P(i)). If the sign of this cross product is negative,
then P(i)P(i+2) is counterclockwise with respect to P(i)P(i+1), and thus we make a left turn at P(i+1).
A positive cross product indicates a clockwise orientation and a right turn. A cross product of 0 means that points P(i), P(i+1), and P(i+2) are collinear."

(P2 - P0) X (P1 - P0) = (X2 - X0) X (Y1 - Y0) - (X1 - X0) X (Y2 - Y0)
*/
class Solution {
public:
	/**
	* @param point: a list of two-tuples
	* @return: a boolean, denote whether the polygon is convex
	*/
	bool isConvex(vector<vector<int>> &point) {
		point.push_back(point[0]);
		int len = (int)point.size() - 2, cp = (point[2][0] - point[0][0]) * (point[1][1] - point[0][1]) - (point[1][0] - point[0][0]) * (point[2][1] - point[0][1]);
		bool isLeft = (cp != std::abs(cp));
		for (int i = 1; i < len; ++i) {
			cp = (point[i + 2][0] - point[i][0]) * (point[i + 1][1] - point[i][1]) - (point[i + 1][0] - point[i][0]) * (point[i + 2][1] - point[i][1]);
			if ((true == isLeft && cp > 0) || (false == isLeft && cp < 0)) return false;
		}
		return true;
	}
};