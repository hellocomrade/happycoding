#include "stdafx.h"
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/triangle/
/*
120. Triangle

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
[2],
[3,4],
[6,5,7],
[4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.



Observations:
Since we know this is a DP, we will not consider DFS which will be more complicated in terms of big O

Depending on how you examine this array, the algorithm could start from top or from bottom since starting point and destination
are "obviously" exchangeable. I actually didn't realize that, so I started from top, which ends up a more complicated algorithm due to the edge case.

In terms of storage, you should realize that only the result at row i is needed when we examine row i + 1. Therefore, we will need
at most O(triangle[triangle.size() - 1].size()) space.


If start from top:
Allowing moving to adjacent columns in the next row means: at any given level k with index m, I can moev from [k][m] to either [k + 1][m + 1] and [k + 1][m]
This should be translate to if we have memo for level k and is at level k + 1 to calculate min value for memo:

At any given level k with index m, memo[m] = MIN(triangle[k][m] + memo[m - 1], triangle[k][m] + memo[m])

Index 0 and index triangle[i].size() - 1 are edge cases, memo[triangle[k].size() - 1] is always equal to triangle[k][triangle[k].size() - 1] based upon a simple
fact that the actual size of memo is growing while we top down the triangle.

Index 0 though, could helps us reveal a catch here: when we scan the level k + 1, we should do it backward from triangle[k].size() - 1 to 0. Otherwise, we would
overwrite the memo value that is still needed by the following calculation. For example: when we are at triangle[k + 1][1] to decide the new memo[1], we will need to
examine existing memo[0] and memo[1]. However memo[0] was just modified since we have updated its value when we were on triangle[k + 1][0].

At last, we still have to do a sequential scan on triangle[triangle.size() - 1 elements to find out which one is the min.

Not easy, isn't it?


If we start from bottom:
No edge case
At given level k and index m, memo[m] = triangle[k][m] + min(memo[m], memo[m + 1])

Furthermore, we could actually use triangle vector to store memo values, which give us a O(1) space algorithm. As for time complexity, this is a linear
algorithm since every element on the triangle is scaned exactly once.
*/
class SolutionTriangle {
public:
	/**
	* @param triangle: a list of lists of integers.
	* @return: An integer, minimum path sum.
	*/
	//Bottom up, O(1), not considering int overflow at all
	int minimumTotal(vector<vector<int> >& triangle) {
		size_t len = triangle.size();
		for (int i = len - 2; i >= 0; --i)
			for (int j = 0; j < i + 1; ++j)
				triangle[i][j] += std::min(triangle[i + 1][j], triangle[i + 1][j + 1]);
		return triangle[0][0];
	}
	//"Top down"
	int minimumTotal1(const vector<vector<int> > &triangle) {
		size_t len = triangle.size();
		if (0 == len)return 0;
		vector<long long> memo(len, 0);
		for (size_t i = 0; i < len; ++i) {
			for (int j = i; j > -1; --j) {
				if (0 == j)
					memo[0] += triangle[i][j];
				else if (i == j)
					memo[j] = memo[j - 1] + triangle[i][j];
				else
					memo[j] = std::min(triangle[i][j] + memo[j], triangle[i][j] + memo[j - 1]);
			}
		}
		return (int)*std::min_element(memo.begin(), memo.end());
	}
	//Bottom up, O(N), not considering int overflow at all
	int minimumTotal2(const vector<vector<int> >& triangle) {
		size_t len = triangle.size();
		if (0 == len)return 0;
		vector<int> mini = triangle[len - 1];
		for (int i = len - 2; i >= 0; --i)
			for (int j = 0; j < triangle[i].size(); ++j)
				mini[j] = triangle[i][j] + min(mini[j], mini[j + 1]);
		return mini[0];
	}
};
void testTriangle() {
	SolutionTriangle so;
	//Comment out coz gcc doesn't allow declaring vector using const and send to a method with argument that is not const
	//assert(-10 == so.minimumTotal(vector<vector<int> >{ { -10 }}));
	//assert(11 == so.minimumTotal(vector<vector<int> >{ { 2 }, { 3,4 }, { 6,5,7 }, { 4,1,8,3 } }));
}