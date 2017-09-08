#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//https://www.hackerrank.com/challenges/cut-the-tree/problem
/*
Cut the Tree

Anna loves graph theory! She has an n-vertex tree, t, where each vertex u:

- Is indexed with a unique integer from 1 to n.
- Contains a data value, data(u).

Anna observes that cutting any edge, u <-> v, in t results in the formation of two separate trees denoted by t1 and t2.
She also defines the following:

- The sum of a tree is the sum of the data(u) values for all vertices in the tree.
- The difference between two trees created by cutting edge u <-> v is denoted by d(u, v) = ABS(sum(t1), sum(t2)).

Given the definition of tree t, remove some edge u <-> v such that the value of d(u, v) is minimal.
Then print the value of the minimum possible d(u<->v) as your answer.

Note: The tree is always rooted at vertex 1.

Input Format

The first line contains an integer, n, denoting the number of vertices in the tree.
The second line contains n space-separated integers where each integer u denotes the value of data(u).
Each of the n - 1 subsequent lines contains two space-separated integers,  u and v, describing edge u <-> v in tree .

Constraints

- 3 <= n <= 10^5
- 1 <= data(u) <= 1001, where 1 <= u <= n.

Output Format

A single line containing the minimum d(u<->v) possible for tree t.

Sample Input

6
100 200 100 500 100 600
1 2
2 3
2 5
4 5
5 6
Sample Output

400
Explanation

We can visualize the initial, uncut tree as:
	100
	 \
	200
	/  \
      100  100
      /  \
    500  600

There are n - 1 = 5 edges we can cut:

1. Edge 1<->2 results in d(1<->2) = 1500 - 100 = 1400
2. Edge 2<->3 results in d(2<->3) = 1500 - 100 = 1400
3. Edge 2<->5 results in d(2<->5) = 1200 - 400 = 800
4. Edge 4<->5 results in d(4<->5) = 1100 - 500 = 600
5. Edge 5<->6 results in d(5<->6) = 1000 - 600 = 400

We then print the minimum of 1400, 1400, 800, 600, and 400 as our answer, which is 400.

Observations:
Well, this is a sick one! The way the input is given is very wrong! You will have to use the means for building
a graph to construct a tree!

Why it's not a graph? Coz there are only n - 1 edges on a n node graph and by its description, all nodes should be
connected...

OK, so we have a DFS on a tree which is stored in a structure usually used by a graph... What a perfect chaos!

During tree/graph building, we can get the total sum, then during DFS, we get sum on node i, if node i is the root
of the new tree. Therefore, we can tell the diff if tree/graph is cut at node i.

Wait, what if we have more than n - 1 edges? Well, if so, then there is no way to guarantee by cutting at node i, you
can always break the graph in two pieces:

	100
	 \
	200
	/  \
      100  100
      /  \ /
    500  600

Breaking edges between 100 and 600 won't generate two trees...
*/
namespace CutTree {
	struct GraphNode {
		vector<int> neighbors;
		int val;
		int color;
		GraphNode() :neighbors() {
			this->val = 0;
			this->color = 0;
		}
	};
	class SolutionCutTree {
	private:
		vector<GraphNode> graph;
		long long total;
		long long ans;
		long long dfs(int i) {
			long long sum = this->graph[i].val;
			this->graph[i].color = 1;
			for (int j : this->graph[i].neighbors) {
				if (0 == this->graph[j].color)
					sum += this->dfs(j);
			}
			this->graph[i].color = 2;
			this->ans = std::min(this->ans, std::abs(this->total - 2 * sum));
			return sum;
		}
	public:
		SolutionCutTree(int n) : graph(n) { this->total = 0LL; }
		void buildGraph() {
			int n = this->graph.size(), i, j, m;
			for (int k = 0; k < n; ++k) {
				cin >> m;
				graph[k].val = m;
				this->total += m;
			}
			for (int k = 1; k < n; ++k) {
				cin >> i >> j;
				graph[i - 1].neighbors.push_back(j - 1);
				graph[j - 1].neighbors.push_back(i - 1);
			}
		}
		int cut() {
			this->ans = this->total;
			dfs(0);
			return static_cast<int>(this->ans);
		}
	};
}
int TestCutTree() {
	int n = 0;
	cin >> n;
	CutTree::SolutionCutTree so(n);
	so.buildGraph();
	cout << so.cut() << endl;
	return 0;
}
/*
Test cases:
6
100 200 100 500 100 600
1 2
2 3
2 5
4 5
5 6
Expected result: 400


50
716 365 206 641 841 585 801 645 208 924 920 286 554 832 359 836 247 959 31 322 709 860 890 195 575 905 314 41 669 549 950 736 265 507 729 457 91 529 102 650 805 373 287 710 556 645 546 154 956 928
14 25
25 13
13 20
20 24
43 2
2 48
48 42
42 5
27 18
18 30
30 7
7 36
37 9
9 23
23 49
49 15
31 26
26 29
29 50
50 21
41 45
45 10
10 17
17 34
28 47
47 44
44 11
11 16
3 8
8 39
39 38
38 22
19 32
32 12
12 40
40 46
1 35
35 4
4 33
33 6
25 2
2 27
7 37
15 50
21 10
17 28
16 39
38 19
40 1
Expected result: 525
*/
