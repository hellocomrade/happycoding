#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

//https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/
/*
889. Construct Binary Tree from Preorder and Postorder Traversal

Return any binary tree that matches the given preorder and postorder traversals.

Values in the traversals pre and post are distinct positive integers.

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]

Output: [1,2,3,4,5,6,7]


Note:

- 1 <= pre.length == post.length <= 30
- pre[] and post[] are both permutations of 1, 2, ..., pre.length.
- It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.

Observations:

This is episode 3 of "Construct BT from 2 of 3 BT Traversals" series. The previous two are leetcode 105 and leetcode 106.

This can be done through both iteration and recursion approaches. I prefer iteration coz it has more fun. But recursion might
be more straightforward to think through.

Both of them are based upon the idea that the BT shall be constructed using pre-order result in a top down way.

1. Recursion, see constructFromPrePost0

Given [1,2,4,5,3,6,7] as pre-order and [4,5,2,6,7,3,1] as post-order result, if one uses pre-order result to guide the build,
it's not hard to find the root and its left and right subtrees by consulting with post-order result:

Root: [1]
Left Child: [2, 4 ,5]
Right Child: [3, 6, 7]

[2] is the root of the left subtree and the end of left subtree can be found by scanning the post-order result until [2] is found.
Therefore, [4, 5, 2] is the post-order result for left subtree and their pre-order result is [2, 4, 5]. Same rule applies on right
subtree after the boundary of left subtree is discovered. [3] is the next element after [2, 4, 5] in pre-order result, since this is
binary tree, one can safely conclude [3, 6 ,7] are the element for the right subtree.

The recursion goes until there is only one element left in the preorder subarray.

Total time complexity O(N^2) due to the linear scanning of root in post-order array in every recusion. Space complexity is
O(logN) due to stack usage for recursion.

2. Iteration, see constructFromPrePost

Obviously, a stack is necessary to convert a recusive solution. constructFromPrePost1 is my first try. An extra unordered_set
is used to tracked visited element in pre-order result. This check is done on post-order array in order to tell the newly met
element is a visited node on stack or a new one that needs to be hooked up with the tree.

There is a more elegant solution posted on leetcode discussion area, constructFromPrePost. The idea is:

- Looping through pre-order result and create new tree node for each element for inseration;

- The new node shall be hooked up with the top node on the stack as left child if left child is NULL, otherwise go with right child;

- The above operation can be done only if the top node on the stack is not the same as the current element of post-order array. If so,
one shall pop such nodes from the stack till the top node is not as same as the current element on post-order array; By doing so, it
guaranteed the top element on the stack is the immediate parent of to be inserted newly created node.

The above approach makes the assumption that the stack is never empty. However, the edge case are empty array or array with 1 element is given.
Therefore, one has to rule out these 2 possibilties up front then push root pre[0] on the stack before the loop.
*/
namespace ConstructBinaryTreeFromPreorderAndPostorderTraversal {
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
		TreeNode* constructFromPrePost(const vector<int>& pre, const vector<int>& post) {
			int len = (int)pre.size();
			if (1 > len) return nullptr;
			else if (1 == len) return new TreeNode(pre[0]);
			TreeNode* pnode = nullptr, *root = new TreeNode(pre[0]);
			stack<TreeNode*> stk;
			stk.push(root);
			for (int i = 1, j = 0; i < len; ++i) {
				pnode = new TreeNode(pre[i]);
				while (stk.top()->val == post[j]) stk.pop(), ++j;
				if (nullptr == stk.top()->left) stk.top()->left = pnode;
				else stk.top()->right = pnode;
				stk.push(pnode);
			}
			return root;
		}
		TreeNode* constructFromPrePost0(const vector<int>& pre, const vector<int>& post) {
			auto f = [&](int preBegin, int preEnd, int postBegin, int postEnd, const auto& fun) {
				if (preBegin > preEnd) return (TreeNode*)nullptr;
				int i = postBegin, j = preBegin + 1;
				TreeNode *root = new TreeNode(pre[preBegin]);
				if (preEnd > preBegin) {
					while (pre[preBegin + 1] != post[i]) ++i, ++j;
					root->left = fun(preBegin + 1, j, postBegin, i, fun);
					root->right = fun(j + 1, preEnd, i + 1, postEnd - 1, fun);
				}
				return root;
			};
			return f(0, pre.size() - 1, 0, post.size() - 1, f);
		}
		TreeNode* constructFromPrePost1(const vector<int>& pre, const vector<int>& post) {
			int postlen = (int)post.size() - 1, i = 0, j = 0;
			TreeNode* root = nullptr, *pnode = nullptr;
			stack<TreeNode*> stk;
			unordered_set<int> visited;
			while (j < postlen) {
				if (0 == visited.count(post[j])) {
					do {
						pnode = new TreeNode(pre[i]);
						visited.insert(pnode->val);
						if (false == stk.empty()) {
							if (nullptr == stk.top()->left) stk.top()->left = pnode;
							else stk.top()->right = pnode;
						}
						stk.push(pnode);
					} while (post[j] != pre[i++]);
				}
				else {
					while (post[j] != stk.top()->val) stk.pop();
					stk.pop();
					++j;
				}
			}
			return true == stk.empty() ? ((0 == postlen) ? new TreeNode(post[0]) : nullptr) : stk.top();
		}
	};
}
void TestConstructBinaryTreeFromPreorderAndPostorderTraversal() {
	ConstructBinaryTreeFromPreorderAndPostorderTraversal::Solution so;
	so.constructFromPrePost(vector<int>(), vector<int>());
	so.constructFromPrePost(vector<int>{ 1 }, vector<int>{ 1 });
	so.constructFromPrePost(vector<int>{1, 2, 3}, vector<int>{3, 2, 1});
	so.constructFromPrePost(vector<int>{1, 3, 2}, vector<int>{3, 2, 1});
	so.constructFromPrePost(vector<int>{1, 2, 4, 5, 3, 6, 7}, vector<int>{4, 5, 2, 6, 7, 3, 1});
}
/*
Test cases:

[1,2,4,5,3,6,7]
[4,5,2,6,7,3,1]
[1,2,4,5,6,3,7,8]
[5,6,4,2,8,7,3,1]
[1,2,4,3,5]
[4,2,5,3,1]
[1]
[1]
[]
[]
[1,2,3]
[3,2,1]
[1,3,2]
[3,2,1]
[3,2,5,4,1]
[5,1,4,2,3]

Outputs:

[1,2,3,4,5,6,7]
[1,2,3,4,null,7,null,5,6,8]
[1,2,3,4,null,5]
[1]
[]
[1,2,null,3]
[1,3,2]
[3,2,null,5,4,null,null,1]
*/