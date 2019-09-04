using namespace std;

//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
/*
236. Lowest Common Ancestor of a Binary Tree

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1

Output: 3

Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4

Output: 5

Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Note:

- All of the nodes' values will be unique.
- p and q are different and both values will exist in the binary tree.

Observations:

I don't understand why I never commit it. The reason this came on my radar is because:

https://leetcode.com/discuss/interview-experience/374016/amazon-sde2-aug-2019

It was asked during an Amazon interview. This is actually a pretty good starting question.

https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/

Official resursive solution is too amateur...

Recursively solving this problem is very pretty, only needs few lines and given function signature
perfectly fits the recursion.

The idea is to do DFS and stop recursion if p or/and q is/are found. If at any given level, both p and q
are found from the recursion to the left child and to the right child, LCA is found.

If root is null or root is equal to given p or q, return root directly. This could either mean the end of
the path is reached or p/q is found on root. This also implicitly solves the case when p/q is the parent of
q/p.

Otherwise, DFS on left and right child, the return will carry p, q or LCA. If both p, q are found, root is
the LCA. If either p or q is found, return it respectively. Is it possible both DFSs return null? No, the statement
says both p and q exist in the BS therefore the subtree that doesn't have p,q will never be reached due to earlier
termination on recursion when p, q is/are discovered.
*/
namespace LowestCommonAncestorOfBT {
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
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
			if (nullptr == root || p == root || q == root) return root;
			TreeNode *left = lowestCommonAncestor(root->left, p, q);
			TreeNode *right = lowestCommonAncestor(root->right, p, q);
			if (nullptr != left && nullptr != right) return root;
			return nullptr != left ? left : right;
		}
	};
}
/*
Test cases:

[3,5,1,6,2,0,8,null,null,7,4]
5
1
[3,5,1,6,2,0,8,null,null,7,4]
3
5
[3,5,1,6,2,0,8,null,null,7,4]
7
8
[3,5,1,6,2,0,8,null,null,7,4]
7
2
[3,5,1,6,2,0,8,null,null,7,4]
6
4
[3,5,1,6,2,0,8,null,null,7,4]
5
4
[1,2]
2
1
[1,2]
1
2

Outputs:

3
3
3
2
5
5
1
1
*/