#include <stack>
#include <algorithm>

//https://leetcode.com/problems/maximum-depth-of-binary-tree/?tab=Solutions
/*
104. Maximum Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Observations:
Since recursion post order traversal is trival, let's do it in the interative way. Still post-order and catch length at any leave node.
We could also try BFS using a queue. My impl here is a bit different than the one I did before in tree folder, well no one can remember
the code 8 months ago...
*/
namespace MaximumDepthOfBinaryTree {
	using namespace std;

	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class SolutionMaximumDepthOfBinaryTree {
	public:
		int maxDepth(TreeNode* root) {
			if (nullptr == root)return 0;
			size_t ans = 0;
			TreeNode* node = nullptr, *lastVisited = nullptr;
			stack<TreeNode*> stk;
			stk.push(root);
			while (false == stk.empty()) {
				if (nullptr == node) {
					node = stk.top();
					stk.pop();
				}
				while (nullptr == lastVisited && nullptr != node->left) {
					stk.push(node);
					node = node->left;
				}
				if (nullptr != node->right && lastVisited != node->right) {
					stk.push(node);
					node = node->right;
					lastVisited = nullptr;
				}
				else {
					lastVisited = node;
					if (nullptr == lastVisited->left && nullptr == lastVisited->right)
						ans = std::max(ans, stk.size() + 1);
					node = nullptr;
				}
			}
			return (int)ans;
		}
	};
}