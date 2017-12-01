#include <queue>

using namespace std;

//https://leetcode.com/problems/same-tree/
/*
100. Same Tree

Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.


Example 1:

Input:
1         1
/ \       / \
2   3     2   3

[1,2,3],   [1,2,3]

Output: true
Example 2:

Input:
1         1
/           \
2             2

[1,2],     [1,null,2]

Output: false
Example 3:

Input:
1         1
/ \       / \
2   1     1   2

[1,2,1],   [1,1,2]

Output: false

Observations:
I started with non recursion solution and noticed the significant amount of coding I have to do using BFS with 1 or 2 queues.

Then, compare with recursive version, 1 line...
*/
namespace SameTree {
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
	private:
		bool equal(TreeNode* n1, TreeNode* n2) {
			return (nullptr == n1 || nullptr == n2) ? nullptr == n1 && nullptr == n2 : n1->val == n2->val;
		}
		bool isLeaf(TreeNode* n) {
			return nullptr != n && nullptr == n->left && nullptr == n->right;
		}
	public:
		bool isSameTree(TreeNode* p, TreeNode* q) {
			return (nullptr == p || nullptr == q) ? p == q : p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}
		bool isSameTree1(TreeNode* p, TreeNode* q) {
			int sz = 0;
			queue<TreeNode*> q1, q2;
			q1.push(p), q2.push(q);
			while (false == q1.empty() && false == q2.empty()) {
				if (q1.size() != q2.size())break;
				sz = q1.size();
				while (sz-- > 0) {
					if (false == this->equal(q1.front(), q2.front())) {
						q1.pop();
						break;
					}
					if (nullptr != q1.front() && false == this->isLeaf(q1.front()))q1.push(q1.front()->left), q1.push(q1.front()->right);
					if (nullptr != q2.front() && false == this->isLeaf(q2.front()))q2.push(q2.front()->left), q2.push(q2.front()->right);
					q1.pop(), q2.pop();
				}
			}
			return true == q1.empty() && true == q2.empty();
		}
	};
}