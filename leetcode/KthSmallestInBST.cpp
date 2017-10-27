#include <stack>

using namespace std;

//https://leetcode.com/problems/kth-smallest-element-in-a-bst/
/*
230. Kth Smallest Element in a BST

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Observations:
A In-Order Traversal should do it, stop at k. Did it iterative way. Time complexity O(N), space O(N)

Don't really understand the follow up, doing too much insert/delete on BST? Is it even a balanced tree? Anyway, I guess what
the follow up means is to enlight us using BS? If we could store the size of the tree at any given node as if it's the root,
we could do a binary search around it and overall time complexity is O(logN), no extra space is needed.
*/
namespace KthSmallestInBST {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class SolutionKthSmallestInBST {
	public:
		int kthSmallest(TreeNode* root, int k) {
			int ans = 0;
			stack<TreeNode*> stk;
			TreeNode* node = root;
			while (nullptr != node || false == stk.empty()) {
				if (nullptr != node) {
					stk.push(node);
					node = node->left;
				}
				else {
					node = stk.top();
					stk.pop();
					if (0 == --k) {
						ans = node->val;
						break;
					}
					node = node->right;
				}
			}
			return ans;
		}
	};
}