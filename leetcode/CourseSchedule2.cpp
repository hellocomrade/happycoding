#include <vector>
#include <queue>
#include <functional>

using namespace std;

//https://leetcode.com/problems/course-schedule-ii/
/*
210. Course Schedule II

There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

Example 1:

Input: 2, [[1,0]]

Output: [0,1]

Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
			 course 0. So the correct course order is [0,1] .

Example 2:

Input: 4, [[1,0],[2,0],[3,1],[3,2]]

Output: [0,1,2,3] or [0,2,1,3]

Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both
			 courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
			 So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .

Note:

- The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
- You may assume that there are no duplicate edges in the input prerequisites.

Hints:
1. This problem is equivalent to finding the topological order in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
2. Topological Sort via DFS (https://www.coursera.org/specializations/algorithms) - A great video tutorial (21 minutes) on Coursera explaining the basic concepts of Topological Sort.
3. Topological sort could also be done via BFS.

Observations:

As long as one remember topological sort, this problem can be done using either DFS or Kahn’s algorithm (in-degree) using BFS.

https://github.com/hellocomrade/happycoding/blob/master/graph/TopologicalSort.cpp

Since In-degree Kahn deosn't use recursion, it appears to be faster, see findOrder. I have to argue the term "in-degree"
is actually confusing. What it really means is the number of prerequisites this node have. Or, one can consider it's as
the outgoing edges on a directed graph.

In terms of cycle detection, DFS requires to take a look on visiting status. In-degree, on the other hand, will not be
affected by cycle since the loop exit condition is on false == q.empty(). If there is no 0 in-degree node anymore due to
cycling, q will be empty.

Of cource, two approaches will have to check at the end to see if a valid path exists.
*/
class SolutionCourceScheduleII {
public:
	//In-degree Kahn’s algorithm
	vector<int> findOrder(int numCourses, const vector<pair<int, int>>& prerequisites) {
		queue<int> q;
		vector<int> ans;
		vector<int> indegree(numCourses, 0);
		vector<vector<int>> adjt(numCourses, vector<int>());
		for (auto p : prerequisites) {
			adjt[p.second].push_back(p.first);
			++indegree[p.first];
		}
		for (int i = 0; i < numCourses; ++i) if (0 == indegree[i]) q.push(i);
		while (false == q.empty()) {
			ans.push_back(q.front());
			for (int neighbor : adjt[q.front()]) if (0 == --indegree[neighbor]) q.push(neighbor);
			q.pop();
		}
		return ans.size() == numCourses ? ans : vector<int>();
	}
	//DFS
	vector<int> findOrder0(int numCourses, vector<pair<int, int>>& prerequisites) {
		vector<int> ans;
		vector<int> visited(numCourses, 0);
		vector<vector<int>> adjt(numCourses, vector<int>());
		for (auto p : prerequisites) adjt[p.first].push_back(p.second);
		std::function<void(int c)> dfs = [&](int c) {
			for (int neighbor : adjt[c]) {
				if (0 == visited[neighbor]) visited[neighbor] = 1, dfs(neighbor);
				else if (1 == visited[neighbor]) return;
			}
			visited[c] = 2, ans.push_back(c);
		};
		for (int i = 0; i < numCourses; ++i) if (0 == visited[i]) visited[i] = 1, dfs(i);
		return ans.size() == numCourses ? ans : vector<int>();
	}
};
/*
Test cases:

2
[[1,0]]
4
[[1,0],[2,0],[3,1],[3,2]]
3
[[0,1],[1,2],[2,0]]
3
[]
5
[[1,0],[2,0],[1,4],[3,1],[3,2]]

Outputs:

[0,1]
[0,1,2,3]
[]
[0,1,2]
[0,4,2,1,3]
*/