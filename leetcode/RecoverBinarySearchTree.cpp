#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/recover-binary-search-tree/
/*
99. Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Example 1:

Input: [1,3,null,null,2]

1
/
3
\
2

Output: [3,1,null,null,2]

3
/
1
\
2

Example 2:

Input: [3,1,4,null,null,2]

3
/ \
1   4
/
2

Output: [2,1,4,null,null,3]

2
/ \
1   4
/
3
Follow up:

- A solution using O(n) space is pretty straight forward.
- Could you devise a constant space solution?

Observations:

If BST is mentioned, in-order traversal should always be considered first. Given the following BST:

  3
/   \
1    5
\   / \
2  4   6

You may have 3 situations due to the break of increasing order in an in-order traversal on BST:

 [1]
/   \
1    5
\   / \
[3] 4   6

Only 1 pair involved and they are next to each other in an in-order traversal: 3->1


 [1]
/   \
[3]  5
\   / \
[2] 4   6

2 pairs involved with one element overlapped in an in-order traversal: 3->2, 2->1


  3
/    \
[5]   [1]
\     / \
[2] [4]  6

2 paris involved in an in-order traversal: 5->2, 1->4

So, there will be at least 2 and at most 4 elements invovled and it appears the troublesome elements are awlays the min and
max among possible 2, 3, 4 elements. Here is recoverTree1.

In fact, the vector in recoverTree1 is unnecessary. Only 2 variable is needed to track the min and max with
the help from the fact: in a pair that doesn't follow BST in-order traversal, prev->val > current->val.
Therefore, max is always the first element as prev and the min is always the last element as root.

The follow up question is to reduce space complexity from O(Depth of BST) to O(1), which means no recursion or stack.
This is doable using Morris Traversal.
*/
namespace RecoverBinarySearchTree {
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
		void recoverTree(TreeNode* root) {
			TreeNode *prev = nullptr, *p1 = nullptr, *p2 = nullptr;
			auto inorder = [&prev, &p1, &p2](TreeNode* root, const auto& fun) {
				if (nullptr == root) return;
				fun(root->left, fun);
				if (nullptr != prev && prev->val > root->val) p2 = root, p1 = (nullptr == p1) ? prev : p1;
				prev = root;
				fun(root->right, fun);
			};
			inorder(root, inorder);
			std::swap(p1->val, p2->val);
		}
		void recoverTree1(TreeNode* root) {
			TreeNode *prev = nullptr;
			vector<TreeNode*> pnodes;
			auto inorder = [&prev, &pnodes](TreeNode* root, const auto& fun) {
				if (nullptr == root) return;
				fun(root->left, fun);
				if (nullptr != prev && prev->val > root->val) pnodes.push_back(prev), pnodes.push_back(root);
				prev = root;
				fun(root->right, fun);
			};
			inorder(root, inorder);
			TreeNode *p1 = *std::min_element(pnodes.begin(), pnodes.end(), [](const auto p1, const auto p2) { return p1->val < p2->val; });
			TreeNode *p2 = *std::max_element(pnodes.begin(), pnodes.end(), [](const auto p1, const auto p2) { return p1->val > p2->val; });
			std::swap(p1->val, p2->val);
		}
	};
}
/*
Test cases:

[1,3,null,null,2]
[3,1,4,null,null,2]
[3,4,5,null,2,1,6]
[3,2,5,null,1,4,6]
[1,2,5,null,3,4,6]
[3,1,5,null,6,4,2]
[3,5,1,null,2,4,6]
[0,1,null,2]
[1,2,null,0]
[2,0,null,1]
[1,2]
[2,null,1]

Outputs:

[3,1,null,null,2]
[2,1,4,null,null,3]
[3,1,5,null,2,4,6]
[3,1,5,null,2,4,6]
[3,2,5,null,1,4,6]
[3,1,5,null,2,4,6]
[3,1,5,null,2,4,6]
[2,1,null,0]
[2,1,null,0]
[2,1,null,0]
[2,1]
[1,null,2]
*/