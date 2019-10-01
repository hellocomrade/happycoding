#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

//https://leetcode.com/problems/minimum-height-trees
/*
310. Minimum Height Trees

For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format

The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example 1 :

Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

  0
  |
  1
 / \
2   3

Output: [1]

Example 2 :

Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

0  1  2
\ | /
  3
  |
  4
  |
  5

Output: [3, 4]

Note:
- According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
- The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

Observations:

I can't figure out the solution without looking into the explanation from the author.

(1) A tree is an undirected graph in which any two vertices are
connected by exactly one path.

(2) Any connected graph who has n nodes with n-1 edges is a tree.

(3) The degree of a vertex of a graph is the number of
edges incident to the vertex.

(4) A leaf is a vertex of degree 1. An internal vertex is a vertex of
degree at least 2.

(5) A path graph is a tree with two or more vertices that is not
branched at all.

(6) A tree is called a rooted tree if one vertex has been designated
the root.

(7) The height of a rooted tree is the number of edges on the longest
downward path between root and a leaf.

The key thought I didn't discover is: the root(s) of the minimum height tree is(are) always
the middle point(s) of the longest path. In other words, the root of the MHT is the middle point
of the longest path. If longest path is even, then there will be 2 roots for MHT.

The actual implementation is by keeping removing the leaf node from the graph through BFS. Starting
from the original leaf nodes, once they are removed, decrease leaf nodes' neighbors degree by 1.
Therefore non-leaf nodes could become leaf nodes now. Keep this process until the graph with leaf node(s)
only. The remaining node(s) is(are) guaranteed to be the mid point(s) of the longest path due to the nature
of BFS and therefore, they are the root for the MHT.

***Update on 2019-09-30***
Redo coz leetcode modified the signature of the function:

Only one change made: leaf node should only have one neighor therefore, for loop is not necessary.

for (int neighbor : adjMatrix[leaves.front()])

can be replaced by neighbor = *adjMatrix[leaves.front()].begin();

One may notice that the new leaf pushed onto the queue could be revisited coz it could be a neighbor of
other leaves. Therefore, it's possible the degree of this new leaf could be down to zero before it's examined
at next breadth level.

That has been said, this problem comes with extra, hidden conditions to prevent the above issue from happening.
Since there are at least 3 edges in the loop (n > 2), there is no way to decrease an edge degree to less than one
unless n <= 2 at the end of the inner loop. Therefore, the leaves without any neighbor will never be examined.
Actually, such a leaf/leaves is/are the root of the MHT.
*/
class SolutionMinimumHeightTrees {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		vector<int> ans;
		queue<int> leaves;
		vector<unordered_set<int>> adjMatrix(n, unordered_set<int>());
		for (auto p : edges) adjMatrix[p[0]].insert(p[1]), adjMatrix[p[1]].insert(p[0]);
		for (int i = 0; i < n; ++i) if (1 == adjMatrix[i].size()) leaves.push(i);
		while (2 < n) {
			for (int i = 0, neighbor = 0, cnt = leaves.size(); i < cnt; --n, leaves.pop(), ++i) {
				neighbor = *adjMatrix[leaves.front()].begin();
				adjMatrix[neighbor].erase(leaves.front());
				if (1 == adjMatrix[neighbor].size()) leaves.push(neighbor);
			}
		}
		while (false == leaves.empty()) ans.push_back(leaves.front()), leaves.pop();
		return 0 == edges.size() ? std::move(vector<int>{0}) : ans;
	}
	vector<int> findMinHeightTrees(int n, const vector<pair<int, int>>& edges) {
		vector<int> ans;
		queue<int> leaves;
		vector<unordered_set<int> > adjMatrix(n, unordered_set<int>());
		for (auto p : edges) adjMatrix[p.first].insert(p.second), adjMatrix[p.second].insert(p.first);
		for (int i = 0; i < n; ++i)
			if (1 == adjMatrix[i].size()) leaves.push(i);
		while (2 < n) {
			for (int i = 0, cnt = leaves.size(); i < cnt; ++i) {
				for (int neighbor : adjMatrix[leaves.front()]) {
					adjMatrix[neighbor].erase(leaves.front());
					if (1 == adjMatrix[neighbor].size()) leaves.push(neighbor);
				}
				--n, leaves.pop();
			}
		}
		while (false == leaves.empty()) ans.push_back(leaves.front()), leaves.pop();
		return 0 == edges.size() ? std::move(vector<int>{0}) : ans;
	}
};
void TestMinimumHeightTrees() {
	SolutionMinimumHeightTrees so;
	assert(1 == so.findMinHeightTrees(4, vector<std::pair<int, int> > {make_pair(1, 0), make_pair(1, 2), make_pair(1, 3)})[0]);
	so.findMinHeightTrees(2, vector<std::pair<int, int> > {make_pair(1, 0)});
	so.findMinHeightTrees(6, vector<std::pair<int, int> > {make_pair(0, 3), make_pair(1, 3), make_pair(2, 3), make_pair(4, 3), make_pair(5, 4)});
}
/*
Test cases:

1
[]
2
[[0,1]]
4
[[1,0],[1,2],[1,3]]
6
[[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
8
[[0, 3], [6, 3], [1,3], [2, 3], [4, 3], [5, 4],[5, 7]]
11
[[0,1],[0,2],[2,3],[0,4],[2,5],[5,6],[3,7],[6,8],[8,9],[9,10]]

Outputs:

[0]
[0,1]
[1]
[3,4]
[4]
[5,6]
*/
