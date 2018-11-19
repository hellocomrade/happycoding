//https://leetcode.com/problems/path-sum/
/*
112. Path Sum

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

	 5
	/ \
   4   8
  /   / \
 11  13  4
/  \      \
7   2      1

return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

Observations:

DFS, more precisely Pre-Order-Traversal, is the way to go:

The sum at each node can be passed to its children and once a leaf node is reached, check if
total is equal to sum, which is hasPathSum0 or equal to zero, which is hasPathSum.

hasPathSum is slightly better coz sum doesn't have to be passed to the recursion function.
*/
namespace PathSum {
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
		bool hasPathSum(TreeNode* root, int sum) {
			auto fun = [](const TreeNode *pnode, const int s, const auto& f) {
				if (nullptr == pnode) return false;
				if (nullptr == pnode->left && nullptr == pnode->right) return s == pnode->val ? true : false;
				return true == f(pnode->left, s - pnode->val, f) || true == f(pnode->right, s - pnode->val, f);
			};
			return true == fun(root, sum, fun);
		}
		bool hasPathSum0(TreeNode* root, int sum) {
			auto fun = [sum](const TreeNode *pnode, const int s, const auto& f) {
				if (nullptr == pnode) return false;
				if (nullptr == pnode->left && nullptr == pnode->right) return sum == s + pnode->val ? true : false;
				return true == f(pnode->left, pnode->val + s, f) || true == f(pnode->right, pnode->val + s, f);
			};
			return true == fun(root, 0, fun);
		}
	};
}
/*
Test cases:

[5,4,8,11,null,13,4,7,2,null,null,null,1]
22
[]
10
[1]
1
[1]
2
[1,2,null,3,4,null,5,6,7,8]
11
[1,2,null,3,4,null,5,6,7,8]
19

Outputs:

true
false
true
false
false
true
*/