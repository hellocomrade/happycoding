#include <queue>

using namespace std;

//https://leetcode.com/problems/invert-binary-tree/
/*
226. Invert Binary Tree

Invert a binary tree.

Example:

Input:

	 4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

	 4
   /   \
  7     2
 / \   / \
9   6 3   1

Trivia:
This problem was inspired by this original tweet by Max Howell:

Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so f*** off.

Observations:

It appears to be straightforward to solve this using recursion. This can also be done in an interative approach
using level order traversal.

As for Max, I don't blame him. If you never prepared or practice on regular basis, even for an "easy" problem
as Invert Binary Tree could be a puzzle especially during an interview. So a good advice is:
never stop exercising!
*/
namespace InvertBinaryTree {

	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	public:
		TreeNode* invertTree(TreeNode* root) {
			if (nullptr == root) return root;
			TreeNode* ptr = invertTree(root->left);
			root->left = invertTree(root->right);
			root->right = ptr;
			return root;
		}
		TreeNode* invertTree1(TreeNode* root) {
			if (nullptr == root) return root;
			size_t cnt = 0;
			TreeNode *pnode = nullptr, *ptmp = nullptr;
			queue<TreeNode*> q;
			q.push(root);
			while (false == q.empty()) {
				cnt = q.size();
				for (size_t i = 0; i < cnt; ++i) {
					pnode = q.front(), q.pop();
					ptmp = pnode->left, pnode->left = pnode->right, pnode->right = ptmp;
					if (nullptr != pnode->left) q.push(pnode->left);
					if (nullptr != pnode->right) q.push(pnode->right);
				}
			}
			return root;
		}
	};
}
/*
Test cases:

[4,2,7,1,3,6,9]
[]
[1,2,3]
[1,null,2,3,null,4,5,6,null,7]
[1,2,null,3,null,4,null,null,5,6,7,8]

Outputs:

[4,7,2,9,6,3,1]
[]
[1,3,2]
[1,2,null,null,3,5,4,null,7,null,6]
[1,null,2,null,3,null,4,5,null,7,6,null,null,null,8]
*/