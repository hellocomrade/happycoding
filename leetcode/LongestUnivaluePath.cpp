#include <algorithm>

//https://leetcode.com/problems/longest-univalue-path/
/*
687. Longest Univalue Path

Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

    5
   / \
  4   5
 / \   \
1   1   5
Output:

2
Example 2:

Input:

    1
   / \
  4   5
 / \   \
4   4   5
Output:

2
Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.

Observations:
Find such two nodes that the path between them is filled with nodes with the same value as these two nodes.
We are asked to find the longest path that meets the requirement above. For example

      1
     / \
    1   0
   / \
  1   1
 /   /
1   1

On the above tree, such a path starts and ends on the two leave nodes with value 1 and the length of such a path
is 4, measured by the number of edge.

Looks like another recursion job using DFS, more precisely, Post-Order traversal. At each node, we get the longest path
from two children and then check if the node's value is equal to either of the children, if so, add 1 onto the result. Then
we have to track the maximum path on each recursion since such a path might well not start from the root.

The maximum path at current node:
- Both children have the same value as current node, then at current node, we have lchild + rchild + 2. This is actually
the case we listed above, you can travel from one leaf to another in order to get the max path;
- One of the two children has the same value as current node, then at current node, we have either lchild + 1 or rchild + 1;
- Neither of children has value equal to its parent, then at current node, there is no path;

In terms of return value at each recursion:
We can't return the max path we just calcuated coz the parent node won't be able to travel from one leaf to another without cross the same edge
twice...Instead, we should return:
- The larger one between the lchild + 1 and rchild + 1 if both are equal to current node;
- The lchild + 1 or rchild + 1 if it's equal to current node by value;
- 0;

The above thought can be simplified: https://leetcode.com/articles/longest-univalue-path/
*/
namespace LongestUnivaluePath {
	/**
	* Definition for a binary tree node.
	*/
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class SolutionLongestUnivaluePath {
	private:
		int ans;
		//_aux1 can be simplified
		int _aux1(TreeNode* root) {
			if (nullptr == root)return 0;
			int cntl = 0, cntr = 0;
			bool bl = (nullptr != root->left && root->left->val == root->val), br = (nullptr != root->right && root->right->val == root->val);
			cntl = _aux(root->left) + (true == bl ? 1 : 0);
			cntr = _aux(root->right) + (true == br ? 1 : 0);
			if (true == bl && true == br) {
				this->ans = std::max(this->ans, cntl + cntr);
				return std::max(cntl, cntr);
			}
			else {
				this->ans = std::max(this->ans, std::max(cntl, cntr));
				if (true == bl)return cntl;
				else if (true == br)return cntr;
			}
			return 0;
		}
		int _aux(TreeNode* root) {
			if (nullptr == root)return 0;
			bool bl = (nullptr != root->left && root->left->val == root->val), br = (nullptr != root->right && root->right->val == root->val);
			int cntl = _aux(root->left);
			int cntr = _aux(root->right);
			cntl = true == bl ? cntl + 1 : 0;
			cntr = true == br ? cntr + 1 : 0;
			this->ans = std::max(this->ans, cntl + cntr);
			return std::max(cntl, cntr);
		}
	public:
		int longestUnivaluePath(TreeNode* root) {
			this->ans = 0;
			this->_aux(root);
			return this->ans;
		}
	};
}