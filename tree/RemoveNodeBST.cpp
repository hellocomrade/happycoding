//http://www.lintcode.com/en/problem/remove-node-in-binary-search-tree/
/*
Remove Node in Binary Search Tree

Given a root of Binary Search Tree with unique value for each node. Remove the node with given value. If there is no such a node with given value in the binary search tree, do nothing. You should keep the tree still a binary search tree after removal.

Example
Given binary search tree:

5
/ \
3   6
/ \
2   4
Remove 3, you can either return:

5
/ \
2   6
\
4
or

5
/ \
4   6
/
2

Observations:
Classic remove a node from BST. If the target node exits in the BST, you will have 3 scenarios:
1. Target node doesn't have any child: in this case, we can simply disconnect it from the BST;
2. Target node has either left node or right node: in this case, we link target's parent with target's child;
3. Target node has left and right children: in this case, we replace target node with the smallest node in its
right subtree and then remove this smallest node from the tree.
we have 2 possibilities:
A. Right child of the target node doesn't have left subtree, then right child itself is the smallest node;
A. Right child of the target node does have left subtree, then we look for the leftmost node, which is the smallest node;

Special situation: target is the root. The above rules still apply, but for scenario 1, we have to set root = nullptr and for
scenario 2, we replace the root with either its left or right child. No influenece on scenario 3.

Overall time complexity is O(logN)

I did it iteratively. A recursive version might be easier to be written and understood. TODO list.
*/
namespace RemoveNodeBST {
	class TreeNode {
	public:
		int val;
		TreeNode *left, *right;
		TreeNode(int val) {
			this->val = val;
			this->left = this->right = nullptr;
		}
	};
	class SolutionRemoveNodeBST {
	public:
		/**
		* @param root: The root of the binary search tree.
		* @param value: Remove the node with given value.
		* @return: The root of the binary search tree after removal.
		*/
		TreeNode* removeNode(TreeNode* root, int value) {
			// write your code here
			if (root != nullptr) {
				TreeNode *current = root, *target = nullptr, *prev = root;
				while (current != nullptr) {
					if (current->val == value) {
						target = current;
						break;
					}
					prev = current;
					if (current->val < value)
						current = current->right;
					else
						current = current->left;
				}
				if (target != nullptr) {
					TreeNode *delme = target;
					if (target->left == nullptr && target->right == nullptr) {
						if (target == root)root = nullptr;
						else if (target == prev->left)prev->left = nullptr;
						else prev->right = nullptr;
					}
					else if (target->left != nullptr && target->right != nullptr) {
						current = target->right;
						TreeNode *last = target;
						while (current->left != nullptr) {
							last = current;
							current = current->left;
						}
						target->val = current->val;
						if (last == target)last->right = nullptr;
						else last->left = nullptr;
						delme = current;
					}
					else {
						if (target == root)root = target->left != nullptr ? target->left : target->right;
						else if (target == prev->left) prev->left = target->left != nullptr ? target->left : target->right;
						else prev->right = target->left != nullptr ? target->left : target->right;
					}
					delete delme;
				}
			}
			return root;
		}
	};
}
