#include <algorithm>

using namespace std;

//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
/*
235. Lowest Common Ancestor of a Binary Search Tree

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

_______6______
/              \
___2__          ___8__
/      \        /      \
0      _4       7       9
/  \
3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Observations:

LCA on BST, let's assume both p and q are not NULL.
*/
namespace LowestCommonAncestorOnBST {
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
		//Iterative
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
			TreeNode *ans = nullptr;
			int i = std::min(p->val, q->val), j = std::max(p->val, q->val);
			while (nullptr != root && nullptr == ans) {
				if (i == root->val || j == root->val || (i < root->val && j > root->val)) ans = root;
				else if (j < root->val) root = root->left;
				else root = root->right;
			}
			return ans;
		}
		//Recursive
		TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
			if (nullptr == root) return nullptr;
			if (p->val < root->val && q->val < root->val) return lowestCommonAncestor(root->left, p, q);
			else if (p->val > root->val && q->val > root->val) return lowestCommonAncestor(root->right, p, q);
			return root;
		}
	};
}