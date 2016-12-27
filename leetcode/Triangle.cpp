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
		//Edge case, vector is empty
		return len > 0 ? triangle[0][0] : 0;
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
/*
The following is from someone at leetcode. Very well explanation
This problem is quite well-formed in my opinion. The triangle has a tree-like structure, which would lead people to think about traversal algorithms such as DFS. However, if you look closely, you would notice that the adjacent nodes always share a 'branch'. In other word, there are overlapping subproblems. Also, suppose x and y are 'children' of k. Once minimum paths from x and y to the bottom are known, the minimum path starting from k can be decided in O(1), that is optimal substructure. Therefore, dynamic programming would be the best solution to this problem in terms of time complexity.

What I like about this problem even more is that the difference between 'top-down' and 'bottom-up' DP can be 'literally' pictured in the input triangle. For 'top-down' DP, starting from the node on the very top, we recursively find the minimum path sum of each node. When a path sum is calculated, we store it in an array (memoization); the next time we need to calculate the path sum of the same node, just retrieve it from the array. However, you will need a cache that is at least the same size as the input triangle itself to store the pathsum, which takes O(N^2) space. With some clever thinking, it might be possible to release some of the memory that will never be used after a particular point, but the order of the nodes being processed is not straightforwardly seen in a recursive solution, so deciding which part of the cache to discard can be a hard job.

'Bottom-up' DP, on the other hand, is very straightforward: we start from the nodes on the bottom row; the min pathsums for these nodes are the values of the nodes themselves. From there, the min pathsum at the ith node on the kth row would be the lesser of the pathsums of its two children plus the value of itself, i.e.:

minpath[k][i] = min( minpath[k+1][i], minpath[k+1][i+1]) + triangle[k][i];
Or even better, since the row minpath[k+1] would be useless after minpath[k] is computed, we can simply set minpath as a 1D array, and iteratively update itself:

For the kth level:
minpath[i] = min( minpath[i], minpath[i+1]) + triangle[k][i]; 
Thus, we have the following solution

int minimumTotal(vector<vector<int> > &triangle) {
    int n = triangle.size();
    vector<int> minlen(triangle.back());
    for (int layer = n-2; layer >= 0; layer--) // For each layer
    {
        for (int i = 0; i <= layer; i++) // Check its every 'node'
        {
            // Find the lesser of its two children, and sum the current value in the triangle with it.
            minlen[i] = min(minlen[i], minlen[i+1]) + triangle[layer][i]; 
        }
    }
    return minlen[0];
}
*/
