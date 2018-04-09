//https://leetcode.com/problems/symmetric-tree/
/*
101. Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following [1,2,2,null,3,null,3] is not:

 1
/ \
2  2
 \  \
  3  3

Note:
Bonus points if you could solve it both recursively and iteratively.

Observations:

I always believe that constructing recursive solution for tree problem is tricky, sometimes more difficult than iterative solution.

This one is not. Symmetric here is defined as mirrored along the center. The recursion in this case doesn't start from the root, it starts
from the children of the given root.

If such a tree is symmetric, the two trees formed by the two children of given root shall always show the same element during the DFS traversal if and only if:

- Traversal on left tree always visits left node before right node;

- Traversal on right tree always visits right node before left node;

It's intutive to apply pre-order DFS, but it actually works on in-order and post-order as well as long as the above two rules are honored.

As for BFS solution, mantaining a dequeue that can extracts values from both side should do. At each level, make sure the count of the dequeue are even and
the elements popped from two sides are always equal.
*/
namespace SymmetricTree {
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
	private:
		bool auxPre(TreeNode* root1, TreeNode* root2) {
			if (nullptr == root1 && nullptr == root2) return true;
			if (nullptr == root1 || nullptr == root2) return false;
			return root1->val == root2->val && true == this->auxPre(root1->left, root2->right) && true == this->auxPre(root1->right, root2->left);
		}
		bool auxIn(TreeNode* root1, TreeNode* root2) {
			if (nullptr == root1 && nullptr == root2) return true;
			if (nullptr == root1 || nullptr == root2) return false;
			return true == this->auxIn(root1->left, root2->right) && root1->val == root2->val && true == this->auxIn(root1->right, root2->left);
		}
		bool auxPost(TreeNode* root1, TreeNode* root2) {
			if (nullptr == root1 && nullptr == root2) return true;
			if (nullptr == root1 || nullptr == root2) return false;
			return true == this->auxPost(root1->left, root2->right) && true == this->auxPost(root1->right, root2->left) && root1->val == root2->val;
		}
	public:
		bool isSymmetric(TreeNode* root) {
			return nullptr == root || true == this->auxPre(root->left, root->right);
		}
	};
}