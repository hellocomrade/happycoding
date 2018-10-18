#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

//https://www.lintcode.com/problem/police-distance/
/*
1367. Police Distance

Description
Given a matrix size of n x m, element 1 represents policeman, -1 represents wall and 0 represents empty.
Now please output a matrix size of n x m, output the minimum distance between each empty space and the nearest policeman

Given a matrix size of n x m， n <= 200，m <= 200.
We guarantee that each empty space can be reached by one policeman at least.
Have you met this question in a real interview?

Example

Given mat =

[
[0, -1, 0],
[0, 1, 1],
[0, 0, 0]
]

return [[2,-1,1],[1,0,0],[2,1,1]].

The distance between the policeman and himself is 0, the shortest distance between the two policemen to other empty space is as shown above
Given mat =

[
[0, -1, -1],
[0, -1, 1],
[0, 0, 0]
]

return [[5,-1,-1],[4,-1,0],[3,2,1]]。

The shortest distance between the policemen to other 5 empty space is as shown above.

Observations:

Shortest distance from possible multiple sources on an undirected graph that each node has exactly 4 neighbors.

Naive O(MN) solution is given here using a queue, O(MN) space for using the queue.

Comparing with Dijkstra, no priority queue is used.

1. Put all nodes with value 1 (police) on the queue and set distance as 0. Temporarily rewrite their values on matrix as -2 (min value);
2. BFS, unless the queue is empty, pop every node on the queue and compare its distance (current distance + 1) with 4 possible neighbors.
If neighbor has a longer distance or first time visit, update its distance in matrix directly, then push this neighbor on queue. So, updating
this neighbor's 4 neighbors might be necessary;
3. Exit the loop, reset any node on matrix with value -2 back to 0;
*/
class SolutionPoliceDistance {
public:
	/**
	* @param matrix : the martix
	* @return: the distance of grid to the police
	*/
	vector<vector<int>> policeDistance(vector<vector<int>> &matrix) {
		int rcnt = (int)matrix.size();
		if (rcnt < 1) return vector<vector<int> >();
		int ccnt = (int)matrix[0].size(), m = 0, n = 0, k = 0;
		if (ccnt < 1) return vector<vector<int> >();
		queue<std::tuple<int, int, int> > q;
		std::tuple<int, int, int> tp;
		for (int i = 0; i < rcnt; ++i) for (int j = 0; j < ccnt; ++j) if (1 == matrix[i][j]) matrix[i][j] = -2, q.push(std::make_tuple(i, j, 0));
		while (false == q.empty()) {
			tp = q.front(), q.pop();
			m = std::get<0>(tp), n = std::get<1>(tp), k = std::get<2>(tp);
			if (m - 1 > -1 && (0 == matrix[m - 1][n] || matrix[m - 1][n] > k + 1)) matrix[m - 1][n] = k + 1, q.push(std::make_tuple(m - 1, n, k + 1));
			if (m + 1 < rcnt && (0 == matrix[m + 1][n] || matrix[m + 1][n] > k + 1)) matrix[m + 1][n] = k + 1, q.push(std::make_tuple(m + 1, n, k + 1));
			if (n - 1 > -1 && (0 == matrix[m][n - 1] || matrix[m][n - 1] > k + 1)) matrix[m][n - 1] = k + 1, q.push(std::make_tuple(m, n - 1, k + 1));
			if (n + 1 < ccnt && (0 == matrix[m][n + 1] || matrix[m][n + 1] > k + 1)) matrix[m][n + 1] = k + 1, q.push(std::make_tuple(m, n + 1, k + 1));
		}
		for (int i = 0; i < rcnt; ++i) for (int j = 0; j < ccnt; ++j) if (-2 == matrix[i][j]) matrix[i][j] = 0;
		return matrix;
	}
};