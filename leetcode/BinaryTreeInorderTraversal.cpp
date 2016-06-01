#include <vector>
#include <stack>

using namespace std;

//https://leetcode.com/problems/binary-tree-inorder-traversal/
/*
94. Binary Tree Inorder Traversal

Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
1
\
2
/
3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?
*/
namespace BinaryTreeInorderTraversal{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class SolutionBinaryTreeInorderTraversal {
	public:
		vector<int> inorderTraversal(TreeNode* root) {
			vector<int> ans;
			if (nullptr == root)return ans;
			stack<TreeNode*> stk;
			TreeNode* node = root;
			stk.push(root);
			while (false == stk.empty())
			{
				while (node)
				{
					if (node->left != nullptr)
						stk.push(node->left);
					node = node->left;
				}
				node = stk.top();
				stk.pop();
				ans.push_back(node->val);
				if (node->right)
				{
					stk.push(node->right);
					node = node->right;
				}
				else
					node = nullptr;
			}
			return ans;
		}
	};
}