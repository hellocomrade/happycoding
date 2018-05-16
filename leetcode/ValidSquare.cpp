#include <vector>

using namespace std;

//https://leetcode.com/problems/valid-square
/*
593. Valid Square

Given the coordinates of four points in 2D space, return whether the four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array with two integers.

Example:

Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]

Output: True

Note:

- All the input integers are in the range [-10000, 10000].
- A valid square has four equal sides with positive length and four equal angles (90-degree angles).
- Input points have no order.

Observations:

It appears the most naive way to tell if we have a square is by calculating the distance square on any 3 of 4 points against 1 point, say B, C, D against A.
|AB|^2, |AC|^2, |AD|^2. Then according to the result, if it could be a square, we shall expect two of three have the same length, the other one is longer.
Say |AD|^2 is longer, which indicates the diagonal. Then we repeat the same procedure on checking A, B, C against D.

The official solution offers more details:

https://leetcode.com/problems/valid-square/solution/
*/
class SolutionValidSquare {
public:
	bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
		auto dist_square = [](long d0, long d1, long d2, long d3) {
			return (d0 - d2) * (d0 - d2) + (d1 - d3) * (d1 - d3);
		};
		long l1 = dist_square(p1[0], p1[1], p2[0], p2[1]);
		long l2 = dist_square(p1[0], p1[1], p3[0], p3[1]);
		long l3 = dist_square(p1[0], p1[1], p4[0], p4[1]);
		if (l1 == l2)
			return 0 != l3 && l1 + l2 == l3 && l1 == dist_square(p4[0], p4[1], p2[0], p2[1]) && l1 == dist_square(p4[0], p4[1], p3[0], p3[1]);
		else if (l1 > l2)
			return 0 != l1 && l2 + l3 == l1 && l2 == dist_square(p2[0], p2[1], p3[0], p3[1]) && l2 == dist_square(p2[0], p2[1], p4[0], p4[1]);
		else
			return 0 != l2 && l1 + l3 == l2 && l3 == dist_square(p3[0], p3[1], p2[0], p2[1]) && l3 == dist_square(p3[0], p3[1], p4[0], p4[1]);
	}
};