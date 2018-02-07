#include <stack>
#include <vector>
#include <unordered_set>

using namespace std;

//https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
/*
105. Construct Binary Tree from

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

3
/ \
9  20
/  \
15   7

Observations:

I started straightly from iterative solution. This is not my type of algorithm at all! After couple tries, I finally
came out an "acceptable" solution, but I am still not happen with the exit condition of the while loop, (i < len - 1) looks
sloppy!

I will have to summarize the approach later...
*/
namespace ConstructBinaryTreeFromPreorderAndInorderTraversal {
	//Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	public:
		TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
			int len = (int)preorder.size(), i = 0, j = 0;
			TreeNode *ans = 1 > len ? nullptr : new TreeNode(preorder[0]), *cur = ans;
			stack<TreeNode*> stk;
			while (i < len - 1) {
				if (inorder[j] != cur->val) {
					stk.push(cur);
					cur->left = new TreeNode(preorder[++i]);
					cur = cur->left;
				}
				else {
					++j;
					if (false == stk.empty() && inorder[j] == stk.top()->val)
						cur = stk.top(), stk.pop();
					else {
						cur->right = new TreeNode(preorder[++i]);
						cur = cur->right;
					}
				}
			}
			return ans;
		}
		TreeNode* buildTree1(const vector<int>& preorder, const vector<int>& inorder) {
			int len = (int)preorder.size(), j = 0;
			if (len < 1)return nullptr;
			stack<TreeNode*> stk;
			TreeNode *ans = new TreeNode(preorder[0]), *t = nullptr;
			stk.push(ans);
			for (int i = 0; i < len; t = nullptr, ++i) {
				if (ans->val == inorder[i]) {
					if (nullptr == ans->left)ans->left = ans;
					continue;
				}
				while (inorder[i] != stk.top()->val)
					stk.push(new TreeNode(preorder[++j]));
				t = stk.top(), stk.pop();
				if (nullptr == stk.top()->left)
					stk.top()->left = t;
				else {
					stk.top()->right = t;
					if (stk.top()->left == ans)stk.top()->left = nullptr;
					if (stk.size() > 1)stk.pop();
				}
				if (i + 1 < len && inorder[i + 1] != stk.top()->val) {
					stk.push(t);
					if (nullptr == t->left)t->left = ans;
				}
			}
			if (ans->left == ans)ans->left = nullptr;
			return ans;
		}
		TreeNode* buildTree2(const vector<int>& preorder, const vector<int>& inorder) {
			int j = 0, len = (int)preorder.size();
			if (len < 1)return nullptr;
			TreeNode* ans = new TreeNode(preorder[0]), *t = nullptr;
			stack<TreeNode*> stk;
			unordered_set<int> scanned;
			stk.push(ans);
			for (int i = 0; i < len; scanned.emplace(inorder[i]), ++i) {
				if (inorder[i] == ans->val) {
					t = ans;
					continue;
				}
				if (inorder[i] != stk.top()->val && nullptr != t)
					stk.push(t);
				while (inorder[i] != stk.top()->val)stk.push(new TreeNode(preorder[++j]));
				t = stk.top(), stk.pop();
				if (scanned.count(stk.top()->val) > 0)
					stk.top()->right = t, stk.pop();
				else
					stk.top()->left = t;

			}
			return ans;
		}
	};
}
void TestConstructBinaryTreeFromPreorderAndInorderTraversal() {
	ConstructBinaryTreeFromPreorderAndInorderTraversal::Solution so;
	so.buildTree(vector<int>{1, 2, 3, 4, 5}, vector<int>{2, 1, 4, 3, 5});
	so.buildTree(vector<int>{1}, vector<int>{1});
	so.buildTree(vector<int>{1, 2}, vector<int>{1, 2});
	so.buildTree(vector<int>{1, 2}, vector<int>{2, 1});
	so.buildTree(vector<int>{1, 2, 3}, vector<int>{3, 2, 1});
	so.buildTree(vector<int>{1, 2, 3, 4, 5, 6}, vector<int>{4, 3, 5, 2, 1, 6});
	so.buildTree(vector<int>{3, 9, 20, 15, 7}, vector<int>{9, 3, 15, 20, 7});
}
/*
Test cases:
[3,9,20,15,7]
[9,3,15,20,7]
[1,2]
[2,1]
[1,2]
[1,2]
[1,2,3,4,5,6]
[4,3,5,2,1,6]
[1,2,3]
[3,2,1]
[1]
[1]
[]
[]
[1,2,3,4,5,7,6,8]
[4,3,5,2,7,1,8,6]

Results:
[3,9,20,null,null,15,7]
[1,2]
[1,null,2]
[1,2,6,3,null,null,null,4,5]
[1,2,null,3]
[1]
[]
[1,2,6,3,7,8,null,4,5]
*/