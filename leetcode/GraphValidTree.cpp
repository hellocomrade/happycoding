#include <vector>
#include <queue>

using namespace std;

//https://www.lintcode.com/problem/graph-valid-tree
/*
261. Graph Valid Tree

Description
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Example

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Observations:

This is leetcode 261, which is not a free question on leetcode. Fortunately, lintcode offers it for free.

I finished leetcode 310 (Minimum Height Trees) before this. According to that question, one may know:

If a graph is qualified as a tree (A tree is an undirected graph in which any two vertices are
connected by exactly one path.), there will be exact (N - 1) edges given N nodes;

If this is a "sufficient and necessary condition", the check might be as simple following:

int len = (int)edges.size();
if(1 > n || len + 1 != n) return false;
for(auto es : edges) if(es[0] == es[1]) return false; //check if a node connects with itself
return true;

However, leetcode 310 indicates all test cases are undirected acyclic graph (UAG). Here, cyclic has to be dealt with!

For example:

4
[[0,1],[1,2],[1,3]]

is a graph having 3 edges (4 - 1) but it's not a valid tree due to the cycle from 1 to 3.

After examining all details, here goes the implementation:

One can rule out any graph that doesn't have (n - 1) edges by:

if(1 > n || len + 1 != n) return false;

Then mulitple approaches could be applied to detect cycles:

- BFS, see validTree1, O(N + E), if visited nodes are less than n, the graph is a forest with a cycle.
See the example above;

- DFS

- Disjoint Set, see validTree, O(E), given the fact disjoint set operation is considered as O(1).
The idea is: if a newly discovered edge having 2 nodes share the same root, it's a cycle. It might
not be that intuitive, one can follow the code and draw the operations on the paper, that helps.

This is because a newly added node is supposed to have itself as root. If the root is not itself, then
this node was visited before.
*/
class SolutionGraphValidTree {
public:
	/**
	* @param n: An integer
	* @param edges: a list of undirected edges
	* @return: true if it's a valid tree, or false
	*/
	/**
	* @param n: An integer
	* @param edges: a list of undirected edges
	* @return: true if it's a valid tree, or false
	*/
	bool validTree(int n, vector<vector<int>> &edges) {
		int len = (int)edges.size();
		if (1 > n || len + 1 != n) return false;
		vector<std::pair<int, int> > roots(n, std::make_pair(0, 1));
		for (int i = 0; i < n; ++i) roots[i].first = i;
		auto ds_root = [&roots](int n) {
			while (roots[n].first != n) {
				roots[n].first = roots[roots[n].first].first;
				n = roots[n].first;
			}
			return n;
		};
		auto ds_union = [&roots, &ds_root](const int n1, const int n2) {
			int root1 = ds_root(n1), root2 = ds_root(n2);
			if (root1 == root2) return false;
			if (roots[root1].second >= roots[root2].second) {
				roots[root2].first = root1;
				roots[root1].second += roots[root2].second;
			}
			else {
				roots[root1].first = root2;
				roots[root2].second += roots[root1].second;
			}
			return true;
		};
		for (auto edg : edges)
			if (false == ds_union(edg[0], edg[1])) return false;
		return true;
	}
	bool validTree1(int n, vector<vector<int>> &edges) {
		int len = (int)edges.size(), cnt = 0;
		if (1 > n || len + 1 != n) return false;
		queue<int> q;
		q.push(0);
		vector<bool> visited(n, false);
		vector<vector<int> > adjMatrix(n, vector<int>());
		for (auto es : edges) adjMatrix[es[0]].push_back(es[1]), adjMatrix[es[1]].push_back(es[0]);
		while (false == q.empty()) {
			cnt += q.size();
			for (int i = 0, cnt = q.size(); i < cnt; ++i) {
				visited[q.front()] = true;
				for (int neighbor : adjMatrix[q.front()]) if (false == visited[neighbor]) q.push(neighbor);
				q.pop();
			}
		}
		return n == cnt;
	}
};