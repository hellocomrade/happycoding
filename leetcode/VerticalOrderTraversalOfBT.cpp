#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
/*
987. Vertical Order Traversal of a Binary Tree

Given a binary tree, return the vertical order traversal of its nodes values.

For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).

Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we report the values
of the nodes in order from top to bottom (decreasing Y coordinates).

If two nodes have the same position, then the value of the node that is reported first is the value that is smaller.

Return an list of non-empty reports in order of X coordinate.  Every report will have a list of values of nodes.

Example 1:

Input: [3,9,20,null,null,15,7]

Output: [[9],[3,15],[20],[7]]

Explanation:

- Without loss of generality, we can assume the root node is at position (0, 0):
- Then, the node with value 9 occurs at position (-1, -1);
- The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
- The node with value 20 occurs at position (1, -1);
- The node with value 7 occurs at position (2, -2).

Example 2:

Input: [1,2,3,4,5,6,7]

Output: [[4],[2],[1,5,6],[3],[7]]

Explanation:

The node with value 5 and the node with value 6 have the same position according to the given scheme.
However, in the report "[1,5,6]", the node value of 5 comes first since 5 is smaller than 6.


Note:

- The tree will have between 1 and 1000 nodes.
- Each node's value will be between 0 and 1000.

Observations:

This problem came to my attention because of a trends post on leetcode for a Google SE L4/L5 interview:

https://leetcode.com/discuss/interview-experience/303008/google-software-engineering-l4l5-at-mountain-view-california

During phone screening, this question was asked. I am surprised that this one was picked coz it may require
a bit more time than usual to understand the question even though the description itself tries hard to give hints...

The question asking a traversal on a binary tree following a custom order, which is defined by a node's X and Y coordinates.

1. This [X, Y] coordinate is not a nature of binary tree and therefore, it must be assigned on nodes during a regular BST traversal.
   During this recursive traveral (PreOrder is used here), along with the child node, X and Y are also passed along.

   "its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1)"

   And the node'value plus its (X, Y) is stored in a vector V of std::tuple.

2. Sort V using a custom comp lambda: by X first (the smaller X wins) then Y (the greater Y wins), if still tie, comparing values of two nodes (the less one wins).

3. Iterating sorted V by X and prepare the final result accordingly.

Leetcode suggest Hash Table, I don't know how it could fly without sorting. Lots of solutions in discussion area do use Hash Table,
however, the value is Set, which will sort the element. Besides, I didn't see any statement saying there is no duplicates
in given binary tree, so a Set may not work at all.

Time complexity is N(logN) due to sorting, space complexity is O(N)

Based upon the questions in that interview, it feels like a position that is going to focus on location based service?
*/
namespace VerticalOrderTraversalOfBT {
	/**
	* Definition for a binary tree node.
	**/
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	public:
		vector<vector<int>> verticalTraversal(TreeNode* root) {
			int i = -1000;
			vector<vector<int>> ans;
			vector<tuple<int, int, int>> nodes;
			function<void(TreeNode*, int, int)> preOrder = [&](TreeNode *root, int i, int j) -> void {
				if (nullptr == root) return;
				nodes.push_back(std::make_tuple(i, j, root->val));
				preOrder(root->left, i - 1, j - 1);
				preOrder(root->right, i + 1, j - 1);
			};
			preOrder(root, 0, 0);
			std::sort(nodes.begin(), nodes.end(), [](const auto& t1, const auto& t2) -> bool {
				if (std::get<0>(t1) != std::get<0>(t2)) return std::get<0>(t1) < std::get<0>(t2);
				if (std::get<1>(t1) != std::get<1>(t2)) return std::get<1>(t1) > std::get<1>(t2);
				return std::get<2>(t1) < std::get<2>(t2);
			});
			for (const auto& t : nodes) {
				if (std::get<0>(t) != i) i = std::get<0>(t), ans.push_back(vector<int>());
				ans.back().push_back(std::get<2>(t));
			}
			return ans;
		}
	};
}
/*
Test cases:

[3,9,20,null,null,15,7]
[1,2,3,4,5,6,7]
[1]
[1,null,2,3,null,null,4,5,null,7,8]
[1,2,null,3,null,4,null,5,null,6]
[1,null,2,null,3,null,4]
[0,5,1,9,null,2,null,null,null,null,3,4,8,6,null,null,null,7]

Outputs:

[[9],[3,15],[20],[7]]
[[4],[2],[1,5,6],[3],[7]]
[[1]]
[[7],[1,3,5],[2,4,8]]
[[6],[5],[4],[3],[2],[1]]
[[1],[2],[3],[4]]
[[9,7],[5,6],[0,2,4],[1,3],[8]]
*/