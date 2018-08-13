#include <stack>

using namespace std;

//https://leetcode.com/problems/leaf-similar-trees/
/*
872. Leaf-Similar Trees

Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence.

3
/ \
5     1
/ \   / \
6  2  9   8
/ \
7   4

For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

Two binary trees are considered leaf-similar if their leaf value sequence is the same.

Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.

Note:

- Both of the given trees will have between 1 and 100 nodes.

Observations:

It's straightforward to carry out a solution based upon DFS by storing all leave nodes somehow (array or string) and then compare
the results from two trees.

There is actually a better way to do this with only O(logN) space by using stack.

The stack keeps tracking all previous visited nodes during pre-order traversal and function nextLeaf only returns if a leaf node
is discovered. At the end of the search, if two trees have all same leaves, two stacks shall both be empty. Or, one tree
has more leaves than the other.
*/
namespace LeafSimilarTrees {
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
	public:
		bool leafSimilar(TreeNode* root1, TreeNode* root2) {
			stack<TreeNode*> stk1, stk2;
			auto nextLeaf = [](stack<TreeNode*> &stk) {
				TreeNode *node = nullptr;
				while (false == stk.empty()) {
					node = stk.top(), stk.pop();
					if (nullptr != node->left) stk.push(node->left);
					if (nullptr != node->right) stk.push(node->right);
					if (nullptr == node->left && nullptr == node->right) break;
				}
				return nullptr == node ? -1 : node->val;
			};
			stk1.push(root1), stk2.push(root2);
			while (false == stk1.empty() && false == stk2.empty())
				if (nextLeaf(stk1) != nextLeaf(stk2)) return false;
			return true == stk1.empty() && true == stk2.empty();
		}
	};
}