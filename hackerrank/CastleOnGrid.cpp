#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

//https://www.hackerrank.com/challenges/castle-on-the-grid/
/*
Castle on the Grid

You are given a grid with both sides equal to n. Rows and columns are numbered from 0 to n - 1. There is a castle on the intersection (startX, startY).
In a single step you move from a point (a, b) to a point (c, d) if there is a straight horizontal line or a straight vertical line connecting these two and not containing any forbidden cell.
Here, "X" denotes a forbidden cell.

Your task is to calculate the minimum number of steps it would take to move the castle from its initial position to the goal position (goalX, goalY).

It is guaranteed that it is possible to reach the goal position from the initial position.

Input Format

The first line contains an integer n, the size of the grid.

The following N lines contains a string of length n that consists of one of the following characters: "X" or ".".

Here, "X" denotes a forbidden cell, and "." denotes an allowed cell.

The last line contains startX, startY, denoting the initial position of the castle, and goalX, goalY, denoting the goal position.

Here, startX, startY, goalX and goalY are space separated.

Constraints

- 1 <= n <= 100

- 0 <= startX, startY, goalX, goalY < n

Output Format

Output an integer denoting the minimum number of steps required to move the castle to the goal position.

Sample Input

3
. X .
. X .
. . .
0 0 0 2

Sample Output

3

Explanation

Here is a path that one could follow in order to reach the destination in 3 steps:

(0, 0) -> (2, 0) -> (2, 2) -> (0, 2)

Observations:

Yes, it's instinct to apply either BFS or DFS on this type of problems. The problem is how?

If we consider each cell as a node, then it has four edges (all weights are 1) connecting with all neighbour nodes. So, we should be able
to apply Breadth First Search directly, easier than Dijkstra since all weights are 1 anyway.

The complication is:

The way the steps are count! For the given example, (0, 0) to (2, 0) is counted as only one step, (2, 0) -> (2, 2) is considered as step 2 since
the turn is made...

The way I look at this is:

- Of course using a Queue to track newly discovered neighbors;

- A grid to track minimum count if vistor comes in from 2 X directions (left/right) and 2 Y directions (up/down);

The missing part is: how could we tell a node is visited? One single visit may not do coz we have minX and minY, not to mention the fact it could come in from 4 directions!

Well, I eventually figured:

- Let the node be available as long as the newly visitor could bring in a shorter distince. If so, we refresh the distince on this neighbor and put it back to the queue so
all neighbor's neighbors can be re-examined for a possible shorter distince...

There is actually a "smarter" way as the offical solution indicates:

Instead of considering each cell having 4 neighbors, the cell actually connect with all cells in four directions as long as there is no block. For example:

Both (1, 0) and (2, 0) are neighbors of (0, 0), and two edges both have the distince/weight of 1!

By doing so, we simplify the problem to a real BFS, of course, we have to build this new graph first since it's not following the original
grid anymore.

This is an O(N^2) time algorithm.

My guess is this problem is familiar to the developers who work in the gaming industry coz path finding is one of the basic algorithms they master.
*/
class SolutionCastleOnGrid {
public:
	void castleOnGrid() {
		int n = 0, startX = 0, startY = 0, goalX = 0, goalY = 0, mx = numeric_limits<int>::max() - 1;
		cin >> n;
		vector<vector<char> > map(n + 2, vector<char>(n + 2, ' '));
		vector<vector<std::pair<int, int> > > memo(n, vector<std::pair<int, int> >(n, std::make_pair(mx, mx)));
		queue<std::pair<int, int> > q;
		std::pair<int, int> coord;
		for (int i = 0; i <= n + 1; map[0][i] = map[i][0] = map[n + 1][i] = map[i][n + 1] = 'X', ++i);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cin >> map[i][j];
		cin >> startX >> startY >> goalX >> goalY;
		q.push(std::make_pair(startX, startY));
		memo[startX][startY].first = memo[startX][startY].second = 1;
		while (false == q.empty()) {
			coord = q.front(), q.pop();
			if ('.' == map[coord.first][coord.second + 1] && memo[coord.first - 1][coord.second].second > std::min(memo[coord.first][coord.second].second, memo[coord.first][coord.second].first + 1)) {
				memo[coord.first - 1][coord.second].second = std::min(memo[coord.first][coord.second].second, memo[coord.first][coord.second].first + 1);
				q.push(std::make_pair(coord.first - 1, coord.second));
			}
			if ('.' == map[coord.first + 2][coord.second + 1] && memo[coord.first + 1][coord.second].second > std::min(memo[coord.first][coord.second].second, memo[coord.first][coord.second].first + 1)) {
				memo[coord.first + 1][coord.second].second = std::min(memo[coord.first][coord.second].second, memo[coord.first][coord.second].first + 1);
				q.push(std::make_pair(coord.first + 1, coord.second));
			}
			if ('.' == map[coord.first + 1][coord.second] && memo[coord.first][coord.second - 1].first > std::min(memo[coord.first][coord.second].first, memo[coord.first][coord.second].second + 1)) {
				memo[coord.first][coord.second - 1].first = std::min(memo[coord.first][coord.second].first, memo[coord.first][coord.second].second + 1);
				q.push(std::make_pair(coord.first, coord.second - 1));
			}
			if ('.' == map[coord.first + 1][coord.second + 2] && memo[coord.first][coord.second + 1].first > std::min(memo[coord.first][coord.second].first, memo[coord.first][coord.second].second + 1)) {
				memo[coord.first][coord.second + 1].first = std::min(memo[coord.first][coord.second].first, memo[coord.first][coord.second].second + 1);
				q.push(std::make_pair(coord.first, coord.second + 1));
			}
		}
		cout << std::min(memo[goalX][goalY].first, memo[goalX][goalY].second) << endl;
	}
};