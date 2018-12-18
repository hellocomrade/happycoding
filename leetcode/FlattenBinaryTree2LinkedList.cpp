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

You can also do this in an iterative way with O(1) space and O(N) time. I did it by reconstructing trees while traversal, sort of like Morris Traversal.
See flatten0. An extra tree is maintained from breaking right child tree from original tree. If all remaining nodes on the original tree
is visited, the extra tree is the next root to parse. This process continues until no extra tree is available. See flatten000.

flatten00 is also O(N) time and O(1) space. But it follows a different idea:
Given any no-null node root->right, it should be reattched onto a place in the left branch of root:

1. The rightmost leaf node on the closest right branch to root->left;
2. If such a node doesn't exist, the leftmost leaf node will do (Either on the nearest right branch or not);

Once the move is done, being moved right branch is set.

But there is actually a more elegant solution:

https://leetcode.com/problems/flatten-binary-tree-to-linked-list/discuss/37010/Share-my-simple-NON-recursive-solution-O(1)-space-complexity!

See flatten0, comparing with my flatten00, it doesn't pursue relocating the right branch to the correct location by one move. Instead,

1. If root->left has right branch, move root->right to the rightmost leaf node of root->left->right;
2. Otherwise, temporarily move root->right as root->left->right;

The operation 2 is very clever: it doesn't solve the problem but it defer the problem to root->left->left. So root->right will keep sinking
till a right branch on root->left's subtree emerges or it will be eventually hooked up with leftmost leaf node of root->left.

One may question the time complexity of these three iterative solutions. It appears the inner while loop might scan at least half of the node on the branch
repeatly so the overall time complexity could be O(N^2). However, after a closer look, one should realize this is not true. Those inner while loop is only
triggered in certain condition, i.e., root->left is not None or root->right is not None. So, a node will be visited at most twice if it's a left child.
Therefore, O(N) time.

leetcode 114 is a really interesting problem coz it can be implemented using different approaches and ideas.
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
		/*

		*/
		void flatten0(TreeNode* root) {
			TreeNode *pnode = nullptr;
			while (nullptr != root) {
				if (nullptr != root->left) {
					pnode = root->left;
					while (nullptr != pnode->right) pnode = pnode->right;
					pnode->right = root->right;
					root->right = root->left;
					root->left = nullptr;
				}
				root = root->right;
			}
		}
		//Iterative, no stack
		void flatten00(TreeNode* root) {
			TreeNode *pnode = nullptr;
			while (nullptr != root) {
				if (nullptr != root->left) {
					pnode = root->left;
					while (nullptr != pnode->left || nullptr != pnode->right)
						pnode = nullptr != pnode->right ? pnode->right : pnode->left;
					pnode->right = root->right;
					root->right = root->left;
					root->left = nullptr;
				}
				root = root->right;
			}
		}
		//Iterative, no stack
		void flatten000(TreeNode* root) {
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