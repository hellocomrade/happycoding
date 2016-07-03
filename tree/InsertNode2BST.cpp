//http://www.lintcode.com/en/problem/insert-node-in-a-binary-search-tree/
/*
Insert Node in a Binary Search Tree

Given a binary search tree and a new tree node, insert the node into the tree. You should keep the tree still be a valid binary search tree.

Notice

You can assume there is no duplicate values in this tree + node.

Example
Given binary search tree as follow, after Insert node 6, the tree should be:

2             2
/ \           / \
1   4   -->   1   4
/             / \
3             3   6
*/
namespace InsertNode2BST {
	class TreeNode {
	public:
		int val;
		TreeNode *left, *right;
		TreeNode(int val) {
			this->val = val;
			this->left = this->right = nullptr;
		}
	};

	class SolutionInsertNode2BST {
	public:
		/**
		* @param root: The root of the binary search tree.
		* @param node: insert this node into the binary search tree
		* @return: The root of the new binary search tree.
		*/
		TreeNode* insertNode(TreeNode* root, TreeNode* node) {
			// write your code here
			if (root != nullptr && node != nullptr) {
				TreeNode *current = root;
				TreeNode *prev = nullptr;
				while (current != nullptr) {
					if (node->val == current->val)
						return root;
					prev = current;
					current = node->val < current->val ? current->left : current->right;
				}
				if (node->val < prev->val)prev->left = node;
				else prev->right = node;
			}
			else
				root = node;
			return root;
		}
	};
}