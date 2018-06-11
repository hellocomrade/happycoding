#include <algorithm>

using namespace std;

//https://leetcode.com/problems/minimum-depth-of-binary-tree
/*
111. Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

3
/ \
9  20
/  \
15   7

return its minimum depth = 2.

Observations:

Path here defines as the path from root to the leaf node. Therefore

3
/
2

Depth is 2. Note that node 3 doesn't have right child, so the regular min depth here should be 1. However, as we mentioned above,
path here defines as root to the leaf node. node 3 is NOT a leaf node.

With this in mind, we can develop a recursive solution based upon DFS

Given a node n,

Define d1 as min depth for n->left, d2 as min depth for n->right

- If d1 > 0 and d2 > 0, we shall pick MIN(d1, d2) + 1;

- If d1 is 0 and d2 is 0, node n is a leaf node, we shall return 1;

- Otherwise (either d1 or d2 is 0), then we know node n has either left child or right child. In this case, we shall do
either d1 or d2 that is not 0, plus 1;

This can also be done using BFS without recursion. It's actually more straightforward.
*/
namespace MinimumDepthOfBinaryTree {
	/**
	* Definition for a binary tree node.
	*/
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class Solution {
	public:
		int minDepth(TreeNode* root) {
			if (nullptr == root) return 0;
			int ld = this->minDepth(root->left), rd = this->minDepth(root->right);
			if (0 != ld && 0 != rd) return std::min(ld, rd) + 1;
			else if (0 == ld && 0 == rd) return 1;
			else return std::max(ld, rd) + 1;
		}
	};
}