#include <algorithm>

using namespace std;

//https://leetcode.com/problems/balanced-binary-tree/
/*
110. Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

3
/ \
9  20
/  \
15   7

Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

1
/ \
2   2
/ \
3   3
/ \
4   4

Return false.

Observations:

This can be translated as:

ABS(depth(root->left) - depth(root->right)) < 2 && isBalanced(root->left) && isBalanced(root->right);

However, by doing so, there will be too much overlap, a perfect demo for not using DP :)

Instead, we could do this in bottom up approach, using -1 to indicate the discovery of unbalance.
*/
namespace BalancedBinaryTree {
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
		int height(TreeNode* root) {
			if (nullptr == root) return 0;
			int lh = height(root->left), rh = height(root->right);
			if (-1 == lh || -1 == rh) return -1;
			else if (std::abs(lh - rh) > 1) return -1;
			else return std::max(lh, rh) + 1;
		}
	public:
		//A compact version using lambda
		bool isBalanced(TreeNode* root) {
			bool ans = true;
			auto f = [&ans](TreeNode* root, auto& fun) {
				if (false == ans || nullptr == root) return 0;
				int l = fun(root->left, fun);
				int r = fun(root->right, fun);
				if (1 < std::abs(l - r)) ans = false;
				return std::max(l, r) + 1;
			};
			f(root, f);
			return ans;
		}
		bool isBalanced0(TreeNode* root) {
			return -1 != this->height(root);
		}
	};
}
/*
Test cases:

[3,9,20,null,null,15,7]
[1,2,2,3,3,null,null,4,4]
[]
[1]
[1,2,3]
[1,2,3,4,5,null,6,7]
[1,2]
[1,2,null,3]
[1,2,3,4,null,null,5,null,null,null,6]

Outputs:

true
false
true
true
true
true
true
false
false
*/