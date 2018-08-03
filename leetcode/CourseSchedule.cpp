#include <cassert>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/course-schedule/
/*
207. Course Schedule

There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

Example 1:

Input: 2, [[1,0]]

Output: true

Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0. So it is possible.

Example 2:

Input: 2, [[1,0],[0,1]]

Output: false

Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you should
also have finished course 1. So it is impossible.

Note:

- The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
- You may assume that there are no duplicate edges in the input prerequisites.

Observations:

If one is good on graph, topological sorting would be the first thing pop up in mind.

https://en.wikipedia.org/wiki/Topological_sorting

"In the field of computer science, a topological sort or topological ordering of a directed graph is a linear ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering.
For instance, the vertices of the graph may represent tasks to be performed, and the edges may represent constraints that one task must be performed before another;
in this application, a topological ordering is just a valid sequence for the tasks."

Topologicaly sorting requires "no directed cycles", that is, if it is a directed acyclic graph (DAG).

The problem here is to detect the cycle(s). It can be done using the two algorithms that both solve the problem in linear time.

1. DFS: this is a more genearl approach to deal with graph for sure. The key idea is to maintain the status of nodes: unvisited, discovered and visited.
Between discovered and visited, the first one means that a node is in the stack for being visited but the end node of current DFS has not been done yet.
This status is important for this problem coz if a node with discovered status is met in current DFS, one can tell there is a cyclic.

2. Kahn's algorithm: this is based upon BFS and the starting node is any node having zero incoming edge. During the BFS, all neighbors of current nodes will
decrease their incoming edges' count by 1. If any neighbor has zeor incoming edge after the decrement, it will be added onto a queue for tracking all zeor incoming edges.
BFS keeps going until the queue is empty. For this problem, a cyclic exists if there are still nodes with non-zero incoming edges after the queue is empty and BFS is stopped.
*/
class SolutionCourseSchedule {
private:
	bool visit(unordered_map<int, vector<int>>& adjMatrix, unordered_map<int, int>& status, int node) {
		status[node] = 0;
		for (int neighbor : adjMatrix[node]) {
			if (0 == status.count(neighbor) && false == visit(adjMatrix, status, neighbor)) return false;
			else if (0 == status[neighbor])	return false;
		}
		status[node] = 1;
		return true;
	}
public:
	//dfs
	bool canFinish(int numCourses, const vector<pair<int, int>>& prerequisites) {
		unordered_map<int, vector<int>> adjMatrix;
		unordered_map<int, int> status;
		bool ans = true;
		for (auto& p : prerequisites) adjMatrix[p.first].push_back(p.second);
		for (auto& node : adjMatrix)
			if (0 == status.count(node.first) && false == this->visit(adjMatrix, status, node.first)) return false;
		return true;
	}
	//Kahn
	bool canFinish0(int numCourses, const vector<pair<int, int>>& prerequisites) {
		vector<int> incomingEdges(numCourses, 0);
		unordered_map<int, vector<int>> graph;
		queue<int> q;
		int node;
		for (auto& p : prerequisites) {
			graph[p.first].push_back(p.second);
			++incomingEdges[p.second];
		}
		for (int i = 0; i < numCourses; ++i) if (0 == incomingEdges[i] && graph.count(i) > 0) q.push(i);
		while (false == q.empty()) {
			node = q.front(), q.pop();
			for (int neighbor : graph[node]) {
				--incomingEdges[neighbor];
				if (0 == incomingEdges[neighbor]) q.push(neighbor);
			}
		}
		for (int i : incomingEdges) if (i > 0) return false;
		return true;
	}
};
void TestSolutionCourseSchedule() {
	SolutionCourseSchedule so;
	assert(false == so.canFinish(2, vector<pair<int, int>> {std::make_pair(1, 0), std::make_pair(0, 1)}));
	assert(true == so.canFinish(3, vector<pair<int, int>> {std::make_pair(0, 1), std::make_pair(0, 2), std::make_pair(2, 1)}));
}