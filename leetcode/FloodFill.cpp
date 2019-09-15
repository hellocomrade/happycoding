#include <vector>
#include <functional>

using namespace std;

//https://leetcode.com/problems/flood-fill/
/*
733. Flood Fill

An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel,
plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:

Input:

image = [[1,1,1],[1,1,0],[1,0,1]]

sr = 1, sc = 1, newColor = 2

Output: [[2,2,2],[2,2,0],[2,0,1]]

Explanation:

From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.

Note:

- The length of image and image[0] will be in the range [1, 50].
- The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
- The value of each color in image[i][j] and newColor will be an integer in [0, 65535].

Observations:

This problem was presented on an Amazon phone interview:

https://leetcode.com/discuss/interview-experience/379849/amazon-sde2-seattle-aug-2019-offer

A very straightforward DFS problem. Usually you will need a place to track which cell has been visited.
This easy problem doesn't even need that coz old color will be replaced by new color. So a previously visited
cell will not be visited again.

That has been said, I forgot to consider the edge case that newColor is equal to image[sr][sc]. In such a
case, DFS should not be executed otherwise it will go into a infinite loop which leads to a stackoverflow.
*/
class SolutionFloodFill {
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		int lenr = (int)image.size();
		if (0 < lenr && -1 < sr && -1 < sc && sr < lenr) {
			int lenc = (int)image[0].size();
			if (0 < lenc && sc < lenc) {
				function<void(int, int, int)> dfs = [&](int i, int j, int oldColor) -> void {
					if (0 > i || 0 > j || lenr == i || lenc == j || oldColor != image[i][j]) return;
					image[i][j] = newColor;
					dfs(i - 1, j, oldColor), dfs(i + 1, j, oldColor);
					dfs(i, j - 1, oldColor), dfs(i, j + 1, oldColor);
				};
				if (newColor != image[sr][sc]) dfs(sr, sc, image[sr][sc]);
			}
		}
		return image;
	}
};
/*
Test cases:

[[0,0,0],[0,1,1]]
1
1
1
[[1,1,1],[1,1,0],[1,0,1]]
1
1
2
[[1]]
0
0
0
[[0,1,0]]
0
1
2
[[0,1,2],[2,1,0],[1,2,3],[3,2,1]]
2
1
5

Outputs:

[[0,0,0],[0,1,1]]
[[2,2,2],[2,2,0],[2,0,1]]
[[0]]
[[0,2,0]]
[[0,1,2],[2,1,0],[1,5,3],[3,5,1]]
*/