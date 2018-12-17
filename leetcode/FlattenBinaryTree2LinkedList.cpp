//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
/*
114. Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

1
/ \
2   5
/ \   \
3   4   6
The flattened tree should look like:

1
\
2
\
3
\
4
\
5
\
6

Observations:

The description is short, but if one play with the test case a bit, it can be confirmed that the link list
is generated using tree node's right child pointer, the left child pointer shall be reset to null once the
node is flatten.

From the output of the list, it appears the traversal should be pre-order. But after a second look,
especially thinking through how the list is generated:

Move Node N's left child as N's right child, the original N's right child is linked as the right child of the N's new right child's rightmost child

Post-order traversal is ideal. flatten1 is such an implementation using recursion.

A way smarter solution is still using post-order recursively. But, it traverses right child tree first and keeps tracking
the last visited node coz the next visited node's right child is current visited node in such a traversal order. See flatten.

You can also do this in an iterative way with O(1) space. I did it by reconstructing trees while traversal, sort of like Morris Traversal.
See flatten0. An extra tree is maintained from breaking right child tree from original tree. If all remaining nodes on the original tree
is visited, the extra tree is the next root to parse. This process continues until no extra tree is available.

But there is actually a more elegant solution:

https://leetcode.com/problems/flatten-binary-tree-to-linked-list/discuss/37010/Share-my-simple-NON-recursive-solution-O(1)-space-complexity!
*/
namespace FlattenBinaryTree2LinkedList {
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
		TreeNode *prev = nullptr;
	public:
		//Recursive, post-order, right child first
		void flatten(TreeNode* root) {
			if (nullptr == root) return;
			flatten(root->right);
			flatten(root->left);
			root->left = nullptr;
			root->right = prev;
			prev = root;
		}
		//Iterative, no stack
		void flatten0(TreeNode* root) {
			TreeNode *proot1 = nullptr, *prev = nullptr, *tmp = nullptr;
			while (nullptr != root) {
				if (nullptr != root->right) {
					if (nullptr == proot1) proot1 = root->right;
					else {
						tmp = root->right;
						while (nullptr != tmp->right) tmp = tmp->right;
						tmp->right = proot1, proot1 = root->right;
					}
				}
				root->right = root->left, root->left = nullptr;
				if (nullptr != root->right) root = root->right;
				else root->right = proot1, root = proot1, proot1 = nullptr;
			}
		}
		//Naive recursive post-order, ugly
		void flatten1(TreeNode* root) {
			TreeNode *ans = nullptr;
			auto postorder = [](TreeNode *pnode, const auto& fun) -> TreeNode* {
				if (nullptr == pnode) return nullptr;
				TreeNode* ltail = fun(pnode->left, fun);
				TreeNode* rtail = fun(pnode->right, fun);
				if (nullptr == ltail && nullptr == rtail) return pnode;
				else if (nullptr != ltail && nullptr != rtail) {
					TreeNode* tmp = pnode->right;
					pnode->right = pnode->left, ltail->right = tmp, pnode->left = nullptr;
					return rtail;
				}
				if (nullptr != ltail) {
					pnode->right = pnode->left, pnode->left = nullptr;
					return ltail;
				}
				else return rtail;
			};
			postorder(root, postorder);
		}
	};
}
/*
Test cases:

[7,-10,2,-4,3,-8,null,null,null,null,-1,11]
[1,2,3,4,5]
[1,2,5,3,4,null,6]
[1,2,5,3,4,null,6,7]
[1,2,5,3,4,null,6,7,8,null,null,9,10,null,11]
[1,2,null,3,null]
[1,null,2,null,3]
[1]
[]
[1,null,2,3,null,4,5,6,null,7]

Outputs:

[7,null,-10,null,-4,null,3,null,-1,null,2,null,-8,null,11]
[1,null,2,null,4,null,5,null,3]
[1,null,2,null,3,null,4,null,5,null,6]
[1,null,2,null,3,null,7,null,4,null,5,null,6]
[1,null,2,null,3,null,7,null,11,null,8,null,4,null,5,null,6,null,9,null,10]
[1,null,2,null,3]
[1,null,2,null,3]
[1]
[]
[1,null,2,null,3,null,4,null,6,null,5,null,7]
*/