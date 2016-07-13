#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

//http://www.lintcode.com/en/problem/topological-sorting/
/*
Topological Sorting

Given an directed graph, a topological order of the graph nodes is defined as follow:

For each directed edge A -> B in graph, A must before B in the order list.
The first node in the order can be any node in the graph with no nodes direct to it.
Find any topological order for the given graph.

Notice

You can assume that there is at least one topological order in the graph.

Example
For graph as follow:

picture

The topological order can be:

[0, 1, 2, 3, 4, 5]
[0, 2, 3, 1, 5, 4]
...

Observations:
Classic topological sort on directed acyclic graph, supposed to use DFS:

https://en.wikipedia.org/wiki/Topological_sorting

TOPOLOGICAL-SORT(G)
1  call DFS(G) to compute finishing times f[v] for each vertex v
2  as each vertex is finished, insert it onto the front of a linked list
3  return the linked list of vertices

On the other hand, this can be done using Breadth First Search as well. Kahn’s algorithm

It would take O(|E|+|V|) time. The idea is to start from any vertex which has in-degree of zero, print that vertex and prune the outgoing edges of it and update in-degrees of its neighbors accordingly. 
Here are the detailed steps which make use of HashMap to store and modify in-degrees.

1.Count in-degree of all vertices.

2.Pick any vertex 'v' which has in-degree of 0.

3.Print 'v'. Remove the vertex 'v' and all edges coming out of it. Decrement in-degrees of all neighbors of vertex 'v' by 1.

4.Repeat steps 2 and 3 till all vertices are removed.

L ← Empty list that will contain the sorted elements
S ← Set of all nodes with no incoming edges
while S is non-empty do
remove a node n from S
add n to tail of L
for each node m with an edge e from n to m do
remove edge e from the graph
if m has no other incoming edges then
insert m into S
if graph has edges then
return error (graph has at least one cycle)
else
return L (a topologically sorted order)
*/
namespace TopologicalSort {
	struct DirectedGraphNode {
	    int label;
	    vector<DirectedGraphNode*> neighbors;
	    DirectedGraphNode(int x) : label(x) {};
	};
	class SolutionTopologicalSort {
	private:
		void dfs(unordered_map<DirectedGraphNode*, int> &colors, vector<DirectedGraphNode*> &ans, DirectedGraphNode *node) {
			colors[node] = 1;
			for (auto neighbor : node->neighbors) {
				if (colors[neighbor] == 0)
					this->dfs(colors, ans, neighbor);
			}
			ans.insert(ans.begin(), node);
		}
	public:
		/**
		* @param graph: A list of Directed graph node
		* @return: Any topological order for the given graph.
		*/
		vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
			int len = graph.size();
			vector<DirectedGraphNode*> ans;
			if (len > 0) {
				unordered_map<DirectedGraphNode*, int> colors;
				for (auto node : graph) {
					colors.emplace(node, 0);
					for (auto neighbor : node->neighbors)
						colors.emplace(neighbor, 0);
				}
				for (auto itor = colors.begin(); itor != colors.end(); ++itor)
					if (itor->second == 0)
						this->dfs(colors, ans, itor->first);
			}
			return ans;
		}
		vector<DirectedGraphNode*> topSort1(vector<DirectedGraphNode*> graph) {
			// write your code here
			int len = graph.size();
			vector<DirectedGraphNode*> ans;
			if (len > 0) {
				unordered_map<DirectedGraphNode*, int> orders;
				auto end = orders.end();
				for (auto node : graph) {
					if (orders.find(node) == end)orders.emplace(node, 0);
					for (auto neighbor : node->neighbors) {
						if (orders.find(neighbor) != end)orders[neighbor]++;
						else orders.emplace(neighbor, 1);
					}
				}
				while (orders.size() > 0) {
					for (auto itor = orders.begin(); itor != orders.end();) {
						if (orders[itor->first] == 0) {
							ans.push_back(itor->first);
							for (auto neighbor : itor->first->neighbors)--orders[neighbor];
							itor = orders.erase(itor);
						}
						else
							++itor;
					}
				}
			}
			return ans;
		}
	};
}
void TestTopologicalSort() {
	TopologicalSort::SolutionTopologicalSort so;
	vector<TopologicalSort::DirectedGraphNode*> graph;
	so.topSort(graph);
}
