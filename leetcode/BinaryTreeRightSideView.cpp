#include <vector>
#include <functional>

using namespace std;

//https://leetcode.com/problems/binary-tree-right-side-view/
/*
199. Binary Tree Right Side View

Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]

Output: [1, 3, 4]

Explanation:

1            <---
/   \
2     3         <---
\     \
5     4       <---

Observation:

The answer will contains K elements, K is the depth of the tree. At each level, the rightmost
node's value will be taken.

Right side view doesn't necessarily mean always take the right child. See below example,
the right side view is [1, 3, 4]

1
/ \
2   3
\
4

The most straightforward means is BFS. Only the last node at each level is visited.

DFS can be applied as well, recursive pre-order appears to be the best choice. Of course, an extra variable
is needed to indicate the current depth.

My first attempt, rightSideView1, use original pre-order logical, which is left child first then right child.
In this case, on each level, if the previous value was taken on this level, the most recent visit on the node
at the same level will have its value replace the existing one. If this node is the first visited node on this
level, push_back has to used instead.

However, this conditional adding logical on the array can be simplified, if right child is visited first. In this
case, the first visited node on each level is the rightmost node on this level. Therefore, only push_back is needed.
For all other nodes at this level, they can be ruleed out by checking the length of the array.

BFS solution is not given here.
*/
namespace BinaryTreeRightSideView {
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
		vector<int> rightSideView(TreeNode* root) {
			vector<int> ans;
			function<void(int, TreeNode*)> dfs = [&](int level, TreeNode *root) {
				if (nullptr == root) return;
				if (ans.size() == level) ans.push_back(root->val);
				dfs(level + 1, root->right);
				dfs(level + 1, root->left);
			};
			dfs(0, root);
			return ans;
		}
		vector<int> rightSideView1(TreeNode* root) {
			vector<int> ans;
			function<void(int, TreeNode*)> dfs = [&](int level, TreeNode *root) {
				if (nullptr == root) return;
				if (ans.size() > level) ans[level] = root->val;
				else ans.push_back(root->val);
				dfs(level + 1, root->left);
				dfs(level + 1, root->right);
			};
			dfs(0, root);
			return ans;
		}
	};
}
/*
Test cases:

[1,2,3,null,5,null,4]
[1]
[]
[1,2,3]
[1,2,3,4]
[1,2,null,3,null,null,4]
[1,null,2,3,null,null,4]
[1,2,3,4,5,6,null,7,null,null,8,null,null,null,9]
[1,2,3,null,4,5,null,null,6,7,8,9,null,10,11,null,null,null,null,12]

Outputs:

[1,3,4]
[1]
[]
[1,3]
[1,3,4]
[1,2,3,4]
[1,2,3,4]
[1,3,6,8,9]
[1,3,5,8,11,12]
*/