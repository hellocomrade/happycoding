#include <vector>
#include <string>

using namespace std;

//https://leetcode.com/problems/binary-tree-paths/
/*
257. Binary Tree Paths

Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

1
/   \
2     3
\
5
All root-to-leaf paths are:

["1->2->5", "1->3"]

Observations:

I was struggle on the fact that I have to send a copy of prefix on each recursive call. But, after a second look, it's guaranteed that
each copy is an answer, so we don't really waste any copy at all.
*/
namespace BinaryTreePaths {
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
		void aux(vector<string> &ans, TreeNode* node, string prefix) {
			if (nullptr == node->left && nullptr == node->right) {
				ans.emplace_back(prefix);
				return;
			}
			if (nullptr != node->left)this->aux(ans, node->left, prefix + "->" + std::to_string(node->left->val));
			if (nullptr != node->right)this->aux(ans, node->right, prefix + "->" + std::to_string(node->right->val));
		}
	public:
		vector<string> binaryTreePaths(TreeNode* root) {
			vector<string> ans;
			if (nullptr != root)this->aux(ans, root, std::to_string(root->val));
			return ans;
		}
	};
}