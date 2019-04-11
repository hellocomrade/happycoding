#include <functional>

using namespace std;

//https://leetcode.com/problems/count-complete-tree-nodes/
/*
222. Count Complete Tree Nodes

Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far
left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example:

Input:
	1
   / \
  2   3
 / \  /
4  5 6

Output: 6

Observations:

In a naive way, this can be done in O(N) using either BFS and DFS. However, it's possible to get a TLE since there is a better solution
only takes O(logN*logN).

countNodes1 is a "naive" way to implement this "Binary Search Greedy" like alogirthm. Given a tree's height as H (root level is 0), there are at most
2^H leaf nodes. One can do a BS to check the existence of the leaf node. However, in order to get to the leaf node that is going to be checked,
the iteration has to be done to go through (H - 1) level of the tree. Since H = logN, total time complexity is O(logN*logN). The remaining question
is: how to navigate through (H - 1) level to get to a specific leaf node? Say leaf nodes are numbered from 1 to 2^H, moving from root to one of
its children, half of the leaf nodes are ignored (2^(H - 1)). Moving to the next level, (2^(H - 2)) are ignored. One can compare the number of
the leaf node in [1, 2^H] with the to be ignored count. If the number of lefa node is no greater than to be ignored, it's on the left subtree. Otherwise,
it's on the right subtree and its number will have to be substracted by 2^h as well so the numbering system her is always 1 based. Using this approach,
the location of the "leaf node" with the number will be reached. If it exists, l of BS should be this number plus one; Otherwise, do the same to r of BS.

There is actually a more "intuitive" BS solution taking advantage of the nature of height of a complete tree, see countNodes: the difference between heights on any
subtree rooted at given node will be no more than 1. StefanPochmann has a very good explanation on this in a recursive way, see countNodes0:

The height of a tree can be found by just going left. Let a single node tree have height 0. Find the height h of the whole tree. If the whole tree is empty, i.e., has height -1, there are 0 nodes.

Otherwise check whether the height of the right subtree is just one less than that of the whole tree, meaning left and right subtree have the same height.

- If yes, then the last node on the last tree row is in the right subtree and the left subtree is a full tree of height h-1. So we take the 2^h-1 nodes of the left subtree plus the 1 root node plus recursively the number of nodes in the right subtree.
- If no, then the last node on the last tree row is in the left subtree and the right subtree is a full tree of height h-2. So we take the 2^(h-1)-1 nodes of the right subtree plus the 1 root node plus recursively the number of nodes in the left subtree.

Since I halve the tree in every recursive step, I have O(log(n)) steps. Finding a height costs O(log(n)). So overall O(log(n)^2).
*/
namespace CountCompleteTreeNodes {
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
		int countNodes(TreeNode* root) {
			function<int(TreeNode*)> height = [](TreeNode* root) {
				int ans = -1;
				while (nullptr != root) ++ans, root = root->left;
				return ans;
			};
			int ans = 0, depth = height(root);
			while (nullptr != root) {
				if (depth - 1 == height(root->right)) {
					ans += 1 << depth--;
					root = root->right;
				}
				else { //right subtree depth is depth - 2
					ans += 1 << --depth;
					root = root->left;
				}
			}
			return ans;
		}
		int countNodes0(TreeNode* root) {
			function<int(TreeNode*)> height = [&](TreeNode* root) {
				return nullptr == root ? -1 : 1 + height(root->left);
			};
			int h = height(root);
			return -1 == h ? 0 : (h - 1 == height(root->right) ? (1 << h) + countNodes0(root->right) : (1 << --h) + countNodes0(root->left));
		}
		int countNodes1(TreeNode* root) {
			if (nullptr == root) return 0;
			int depth = -1, d = 0, l, r, m, mm, n, cnt = 0;
			TreeNode *pnode = root;
			while (nullptr != pnode) ++depth, pnode = pnode->left;
			l = 1, r = 1 << depth;
			while (l <= r) {
				m = mm = l + (r - l) / 2, d = depth, pnode = root;
				while (0 < d) {
					n = 1 << --d;
					if (m <= n) pnode = pnode->left;
					else m -= n, pnode = pnode->right;
				}
				if (nullptr == pnode) r = mm - 1;
				else cnt = mm, l = mm + 1;
			}
			return cnt - 1 + (1 << depth);
		}
	};
}
/*
Test cases:

[]
[1]
[1,2]
[1,2,3]
[1,2,3,4]
[1,2,3,4,5]
[1,2,3,4,5,6]
[1,2,3,4,5,6,7]
[1,2,3,4,5,6,7,8]
[1,2,3,4,5,6,7,8,9]
[1,2,3,4,5,6,7,8,9,10]
[1,2,3,4,5,6,7,8,9,10,11]
[1,2,3,4,5,6,7,8,9,10,11,12]
[1,2,3,4,5,6,7,8,9,10,11,12,13]
[1,2,3,4,5,6,7,8,9,10,11,12,13,14]
[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]

Outputs:

0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
*/