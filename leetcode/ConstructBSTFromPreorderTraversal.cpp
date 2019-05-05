#include <vector>
#include <stack>
#include <functional>
#include <limits>

using namespace std;

//https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
/*
1008. Construct Binary Search Tree from Preorder

Return the root node of a binary search tree that matches the given preorder traversal.

(Recall that a binary search tree is a binary tree where for every node, any descendant of node.
left has a value < node.val, and any descendant of node.right has a value > node.val.
Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)

Example 1:

Input: [8,5,1,7,10,12]

Output: [8,5,10,1,7,null,12]

Note:

- 1 <= preorder.length <= 100
- The values of preorder are distinct

Observations:

Over 70% acceptance rate indicates the fact one may feel gulity if the first submission is rejected :)

Official solution is at: https://leetcode.com/articles/construct-bst-from-preorder-traversal/

It's impressive to me to see the first solution they gave is based upon Construct Binary Tree from Preorder and Inorder  (leetcode 105).
By sorting the given array, one will get the Inorder traversal output. Then apply leetcode 105, totoal time complexity, due to sorting
is O(NlogN)

The interative and recursive solutions presented in the offical solutions are given below as bstFromPreorder and bstFromPreorder1.

Using a stack appears to be a natural response for a BST construction. Root node is constructed before the loop on vector (starts from index 1).
Then based upon the comparsion between vector[i] and root->val, if vector[i] is root's left child (this is based upon the nature of preorder traversal),
push root to the stack, create root's left child, then move root = root->left. If vector[i] > root->val, the elements on the stack (if not empty)
will have to be examined until stack.top()->val > vector[i], then the most recent poped element is the parent of this newly created node based upon
vector[i]. If stack is empty up front, then it's safe to say current root is the parent of this newly created right child.

This is a linear algorithm. Even though in some edge cases, such as: [10,9,8,7,6,5,20,19,18,17,16,15,30,29,28,27,26,25,31], the scanning
on the stack will always go from top to bottom, but due to the nature of BS, the overal visits on nodes are no more than (2N + 1)

Recursive version, it's more elegant by my opinion. My first attempt is the iterative approach coz I was not
sure if recursive solution could end up being a linear algorithm. The idea is: by assigning a MIN_VALUE and MAX_VALUE based upon BST nature,
one can tell if vector[i] could qualify being the left or right child of root. If not, return null, then root doesn't have a left or right
child. If it fits, increase i by 1. At here, i has to be in a "global" scope coz entire recursion depends on it. The recursion function
itself doesn't even take i or vector[i] as an argument because of the fact that it's unknown the value of i at the moment the recursive call
is made. That's why i has to be global. At the very first, MIN_VALUE and MAX_VALUE are set to be INT_MIN - 1L and INT_MAX + 1L.
*/
namespace ConstructBSTFromPreorderTraversal {
	//Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	public:
		TreeNode* bstFromPreorder(vector<int>& preorder) {
			size_t len = preorder.size();
			if (1 > len) return nullptr;
			stack<TreeNode*> stk;
			TreeNode* root = new TreeNode(preorder[0]), *ans = root;
			for (size_t i = 1; i < len; ++i) {
				if (root->val > preorder[i]) {
					root->left = new TreeNode(preorder[i]);
					stk.push(root);
					root = root->left;
				}
				else {
					while (false == stk.empty() && preorder[i] > stk.top()->val) root = stk.top(), stk.pop();
					root->right = new TreeNode(preorder[i]);
					root = root->right;
				}
			}
			return ans;
		}
		TreeNode* bstFromPreorder1(vector<int>& preorder) {
			size_t len = preorder.size(), i = 0;
			function<TreeNode*(long, long)> fun = [&](long min_val, long max_val) -> TreeNode* {
				if (i == len || preorder[i] <= min_val || preorder[i] >= max_val) return nullptr;
				TreeNode* root = new TreeNode(preorder[i++]);
				root->left = fun(min_val, root->val);
				root->right = fun(root->val, max_val);
				return root;
			};
			return fun(numeric_limits<int>::min() - 1L, 1L + numeric_limits<int>::max());
		}
	};
}
/*
Test cases:

[8,5,1,7,10,12]
[2,1,3]
[2,3,4]
[2,4,6]
[]
[1]
[10,5,3,1,2,6,8,9,11]
[10,2,1,4,3,5,15,12,14,16,17,18,21]
[10,9,8,7,6,5,20,19,18,17,16,15,30,29,28,27,26,25,31]

Outputs:

[8,5,10,1,7,null,12]
[2,1,3]
[2,null,3,null,4]
[2,null,4,null,6]
[]
[1]
[10,5,11,3,6,null,null,1,null,null,8,null,2,null,9]
[10,2,15,1,4,12,16,null,null,3,5,null,14,null,17,null,null,null,null,null,null,null,18,null,21]
[10,9,20,8,null,19,30,7,null,18,null,29,31,6,null,17,null,28,null,null,null,5,null,16,null,27,null,null,null,15,null,26,null,null,null,25]
*/