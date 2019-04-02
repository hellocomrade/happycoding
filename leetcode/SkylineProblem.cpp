#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/the-skyline-problem/
/*
218. The Skyline Problem

A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance.
Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to
output the skyline formed by these buildings collectively (Figure B).

Figure A: https://leetcode.com/static/images/problemset/skyline1.jpg

Figure B: https://leetcode.com/static/images/problemset/skyline2.jpg

Buildings Skyline Contour

The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi],
where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height.
It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded
on an absolutely flat surface at height 0.

For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .

The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline.
A key point is the left endpoint of a horizontal line segment. Note that the last key point, where the rightmost building ends,
is merely used to mark the termination of the skyline, and always has zero height. Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].

Notes:

- The number of buildings in any input list is guaranteed to be in the range [0, 10000].
- The input list is already sorted in ascending order by the left x position Li.
- The output list must be sorted by the x position.
- There must be no consecutive horizontal lines of equal height in the output skyline.
  For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]

Observations:

A classic problem that can be solved by sweep line and a data structure. In this case, such a data structure is
a max heap. These are just general ideas.

In order to apply sweep line algorithm, array has to be sorted on either X or Y. For this case, given array building is
guaranteed sorted by X. Then the only questions left are:

1. What should be put onto max heap, just height, that's a very obvious thought?
2. Is existing array, buildings, good eoungh to be used as the target for sweeping line?
   In other words, is an extra array necessary for this purpose?
3. When and how to decide a point should be taken as part of the answer.

After couple rounds of tweaks, it has been decided that the object on max heap should be a pair:
(height, the right edge of the building). The latter one indicates how far this height can reach.

The existing input array, building can be used as the target for sweep line. But it has to be used
together with the max heap. Building array is only for getting the left edge of the building. At meantime,
the height of the building along with the right edge is pushed onto max heap. They will be used later
at certain conditions as targets for sweep line. More precisely, the line sweeps the building array from left to right.

1. If a new building (has not be examined) is available, its left edge goes to answer if and only if its height
   is greater than the height on top of max heap. Then, this building's height plus its right edge shall
   be pushed onto max heap for further evaluation. One edge case is [[1,2,1],[1,2,2],[1,2,3]], in this case,
   all 3 buildings having the same left edge, only the last one should be part of the skylines. Therefore,
   if the left edge on top of the max heap is as same as the one that is going to be inserted, update the left edge
   instead of inserting new one.

2. When should the elements on the max heap be evaluated? This is the most compolicated part of the algorithm:
   It happens Either after every building has be examined and max heap is not empty Or current building's left
   edge has exceed the reach of the top height on the max heap. In this case, multiple elements on the heap will
   have to be removed until heap is empty or the current top height on the heap has overlap with current building.

   Among these to-be-removed elements, only the ones (from top) having the max right edge should be part of the answer.
   For example, among (7,8), (6, 7), (5, 6), (5, 10). Only (7, 8) and (5, 10) are taken as (8, 5) and (10, 0). The 2 in
   between are thrown away since they won't contribute to build the right side edges of skylines.

In order to simplify the algorithm, two assumptions are made:

1. (0, INT_MAX) is put first on the heap. So the heap is never empty;
2. When index i is equal to len(buildings), the loop is still on so no need to write extra duplicated pieces
   after the loop to take care remaining elments on the heap;

Another edge case I failed:

[[0,2,3],[2,5,3]]

Two buildings are actually touched. This affects how elements are removed from heap: it occurs if and only if
current building's left edge is greater than the right edge on top of the heap.

Since the array, buildings, is scanned only once and any operations on a max heap is O(logN), the overall
time complexity is O(NlogN).

There should be a divide and conque algorithm for this as well. I should get it done later on.
*/
class SolutionSkylineProblem {
public:
	vector<pair<int, int>> getSkyline(const vector<vector<int>>& buildings) {
		vector<pair<int, int>> ans;
		int len = (int)buildings.size();
		pair<int, int> lastPop;
		std::priority_queue<pair<int, int>> heap;
		heap.push(std::make_pair(0, numeric_limits<int>::max()));
		for (int i = 0; i <= len; ++i) {
			while (1 < heap.size() && (len == i || buildings[i][0] > heap.top().second)) {
				lastPop = heap.top(), heap.pop();
				while (1 < heap.size() && lastPop.second >= heap.top().second) heap.pop();
				ans.push_back(std::make_pair(lastPop.second, heap.top().first));
			}
			if (i < len) {
				if (buildings[i][2] > heap.top().first) {
					if (0 < ans.size() && ans[ans.size() - 1].first == buildings[i][0]) ans[ans.size() - 1].second = buildings[i][2];
					else ans.push_back(std::make_pair(buildings[i][0], buildings[i][2]));
				}
				heap.push(std::make_pair(buildings[i][2], buildings[i][1]));
			}
		}
		return ans;
	}
};
void TestSkylineProblem() {
	SolutionSkylineProblem so;
	so.getSkyline(vector<vector<int>> { {2, 9, 10}, { 3, 7, 15 }, { 5, 12, 12 }, { 15, 20, 10 }, { 19, 24, 8 } });
	so.getSkyline(vector<vector<int>> { {1, 10, 2}, { 3, 6, 5 } });
	so.getSkyline(vector<vector<int>> { {0, 2, 3}, { 2, 5, 3 } });
}
/*
Test cases:

[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
[[2,9,10]]
[[2,9,10],[11,12,1]]
[[1,10,8],[3,6,5]]
[[1,10,8],[3,10,5]]
[[1,10,2],[3,6,5]]
[[1,10,8],[3,6,5],[5,11,7]]
[[1,10,8],[3,12,6],[5,11,7]]
[[1,10,5],[2,12,5],[15,16,1]]
[[1,15,5],[3,8,7],[6,9,10]]
[[0,2,3],[2,5,3]]
[[1,2,1],[1,2,2],[1,2,3]]

Outputs:

[[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
[[2,10],[9,0]]
[[2,10],[9,0],[11,1],[12,0]]
[[1,8],[10,0]]
[[1,8],[10,0]]
[[1,2],[3,5],[6,2],[10,0]]
[[1,8],[10,7],[11,0]]
[[1,8],[10,7],[11,6],[12,0]]
[[1,5],[12,0],[15,1],[16,0]]
[[1,5],[3,7],[6,10],[9,5],[15,0]]
[[0,3],[5,0]]
[[1,3],[2,0]]
*/