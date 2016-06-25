#include <stack>

using namespace std;

//
/*
98. Validate Binary Search Tree

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:
2
/ \
1   3
Binary tree [2,1,3], return true.
Example 2:
1
/ \
2   3
Binary tree [1,2,3], return false.

Observation:
It might be more intuitive to use preorder traversal since we are talking comparing a node with its left and
right children. That's definitely doable with careful recursion branches for left and right.

However, since we are talking about BST, one of its attributes is: if we do inorder traversal, all visted nodes
should be in increasing order. Therefore, we can simply compare the current node with the last visted node, if
last visit node's value is less than current, keep moving, otherwise, it's not a BST.

If we do recursion, in order to keep tracking the previous node, we have to use a member variable. Iteration version,
on the other hand, doesn't need it.
*/
namespace ValidateBST {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class SolutionValidateBST {
	private:
		TreeNode* prev;
	public:
		SolutionValidateBST() :prev(nullptr){}
		//Recursion
		bool isValidBST(TreeNode* root) {
			if (nullptr == root)return true;
			bool ret = isValidBST(root->left);
			if (ret == false)return false;
			if (this->prev != nullptr && this->prev->val >= root->val)return false;
			prev = root;
			return isValidBST(root->right);
		}
		//Iteration
		bool isValidBST1(TreeNode* root) {
			if (nullptr == root)return true;
			TreeNode *prevElem = nullptr, *current = root;
			stack<TreeNode*> stk;
			while (current != nullptr || stk.empty() == false) {
				while (current != nullptr) {
					stk.push(current);
					current = current->left;
				}
				current = stk.top();
				stk.pop();
				if (prevElem != nullptr && prevElem->val >= current->val)return false;
				prevElem = current;
				current = current->right;
			}
			return true;
		}
	};
}