#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
/*
107. Binary Tree Level Order Traversal II

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:

Given binary tree [3,9,20,null,null,15,7],

3
/ \
9  20
/  \
15   7
return its bottom-up level order traversal as:

[
[15,7],
[9,20],
[3]
]
*/
namespace BTLevelOrderTraversal2 {

	/**
	* Definition for a binary tree node.
	*/
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	class Solution {
	public:
		vector<vector<int>> levelOrderBottom(TreeNode* root) {
			int sz = 0;
			vector<vector<int> > ans;
			if (nullptr == root) return ans;
			queue<TreeNode*> q;q.push(root);
			while (false == q.empty()) {
				sz = q.size();
				vector<int> lvec(sz, 0);
				for (int i = 0; i < sz; ++i) {
					root = q.front(), lvec[i] = root->val;
					if (nullptr != root->left) q.push(root->left);
					if (nullptr != root->right) q.push(root->right);
					q.pop();
				}
				ans.push_back(lvec);
			}
			::std::reverse(ans.begin(), ans.end());
			return ans;
		}
	};
}