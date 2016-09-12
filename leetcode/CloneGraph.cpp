#include <cassert>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/clone-graph/
/*
133. Clone Graph

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

1
/ \
/   \
0 --- 2
/ \
\_/

Observations:
It appears to be inevitable of using a hashmap to track all newly created nodes, no matter BFS or DFS.

Two catches:
1. When you are cloning a nodes, its neighbors may or may not be reached yet. For DFS, this can be resolved naturally by applying
recursion. BFS, on the other hand, is a little bit more complicated since the iteration approach is taken. Newly cloned node
will keep the original neighbor vector and this will be updated at next iteration (while loop) when it's poped from the queue and
its neighbors are examined. Both BFS and DFS use the hashmap as the lookup to see if a neighbor has been visited already.

2. Self Cyclic Graph (see above example): this can be solved smoothly if we put the just-cloned-node on the hashmap immediately after it is created. Then,
when we examine its neighbors, we can recognize the loop by checking the hashmap.

3. Other Cyclic Graph situation: doesn't seem to be bothered as long as we have the hashmap to lookup all visited newly created nodes.
*/
namespace CloneGraph {
	struct UndirectedGraphNode {
		int label;
		vector<UndirectedGraphNode*> neighbors;
		UndirectedGraphNode(int x) : label(x) {};
	};

	class SolutionCloneGraph {
	private:
		UndirectedGraphNode* aux(unordered_map<int, UndirectedGraphNode*>& notes, UndirectedGraphNode* node) {
			UndirectedGraphNode *newnode = nullptr, *neighbor = nullptr;
			if (nullptr != node) {
				auto end = notes.end();
				newnode = new UndirectedGraphNode(node->label);
				notes.emplace(newnode->label, newnode);
				for (auto n : node->neighbors) {
					if (end == notes.find(n->label)) neighbor = this->aux(notes, n);
					else neighbor = notes.find(n->label)->second;
					newnode->neighbors.push_back(neighbor);
				}
			}
			return newnode;
		}
	public:
		/**
		* @param node: A undirected graph node
		* @return: A undirected graph node
		*/
		//BFS
		UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
			UndirectedGraphNode *ans = nullptr, *current = nullptr, *neighbor = nullptr;
			if (nullptr != node) {
				unordered_map<int, UndirectedGraphNode*> notes;
				auto nend = notes.end();
				queue<UndirectedGraphNode*> q;
				int size = 0;
				ans = new UndirectedGraphNode(node->label);
				ans->neighbors = node->neighbors;
				q.push(ans);
				notes.emplace(node->label, ans);
				while (false == q.empty()) {
					size = q.size();
					for (int i = 0;i < size; ++i) {
						current = q.front(); q.pop();
						vector<UndirectedGraphNode *> vec;
						for (auto n : current->neighbors) {
							if (nend == notes.find(n->label))
							{
								neighbor = new UndirectedGraphNode(n->label);
								//will take the original neighbors vector for the time being
								neighbor->neighbors = n->neighbors;
								q.push(neighbor);
								notes.emplace(n->label, neighbor);
							}
							else
								neighbor = notes.find(n->label)->second;
							vec.push_back(neighbor);
						}
						current->neighbors = vec;
					}
				}
			}
			return ans;
		}
		//DFS
		UndirectedGraphNode *cloneGraph1(UndirectedGraphNode *node) {
			UndirectedGraphNode *ans = nullptr;
			if (nullptr != node) {
				unordered_map<int, UndirectedGraphNode*> notes;
				ans = this->aux(notes, node);
			}
			return ans;
		}
	};
}
void TestCloneGraph() {
	using Graph = CloneGraph::UndirectedGraphNode;
	using Solution = CloneGraph::SolutionCloneGraph;
	Solution so;
	Graph zero(0), one(1), two(2);
	zero.neighbors.push_back(&one);
	zero.neighbors.push_back(&two);
	one.neighbors.push_back(&two);
	two.neighbors.push_back(&two);
	Graph *ng = so.cloneGraph1(&zero);
	assert(ng->label == zero.label && ng != &zero);
	assert(ng->neighbors[0]->label == one.label && ng->neighbors[0] != &one);
	assert(ng->neighbors[0]->neighbors[0]->label == two.label && ng->neighbors[0]->neighbors[0] != &two);
	assert(ng->neighbors[1]->label == two.label && ng->neighbors[1] != &two);
	assert(ng->neighbors[1]->label == ng->neighbors[1]->neighbors[0]->label && ng->neighbors[1] == ng->neighbors[1]->neighbors[0]);
}