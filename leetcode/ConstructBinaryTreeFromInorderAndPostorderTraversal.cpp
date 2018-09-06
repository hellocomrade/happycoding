#include <vector>
#include <stack>

using namespace std;

//https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
/*
106. Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:

You may assume that duplicates do not exist in the tree.

For example, given

inorder = [9,3,15,20,7]

postorder = [9,15,7,20,3]

Return the following binary tree:

3
/ \
9  20
/     \
15      7

Observations:

If one has completed leetcode 105 (Construct Binary Tree from Preorder and Inorder Traversal), same tech can be applied here.
As for iterative approach, the construction of the tree shall follow the reversely order in postorder array, which can be considered
as a mirror of preorder array. So, the right subtree is visited first and then left subtree in this mirrored world.

Accordingly, inorder array has to be examined in the reversed order as well. Again, right subtree comes first.

Therefore, by changing the loop order and mirroring left, right visiting order, one can easily have the solution.
*/
namespace ConstructBinaryTreeFromInorderAndPostorderTraversal {
	//Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	public:
		TreeNode* buildTree(const vector<int>& inorder, const vector<int>& postorder) {
			int len = (int)inorder.size();
			if (1 > len) return nullptr;
			TreeNode* root = new TreeNode(postorder[len - 1]), *pnode = nullptr, *parentNode = nullptr;
			if (1 == len) return root;
			stack<TreeNode*> stk;
			stk.push(root);
			for (int i = len - 2, j = len - 1; i > -1; parentNode = nullptr, --i) {
				pnode = new TreeNode(postorder[i]);
				while (false == stk.empty() && stk.top()->val == inorder[j]) parentNode = stk.top(), stk.pop(), --j;
				if (nullptr != parentNode) parentNode->left = pnode;
				else stk.top()->right = pnode;
				stk.push(pnode);
			}
			return root;
		}
	};
}
void TestConstructBinaryTreeFromInorderAndPostorderTraversal() {
	ConstructBinaryTreeFromInorderAndPostorderTraversal::Solution so;
	so.buildTree(vector<int> {2, 3, 1}, vector<int>{3, 2, 1});
}
/*
Test cases:

[9,3,15,20,7]
[9,15,7,20,3]
[2,1,3]
[2,3,1]
[3,2,1]
[3,2,1]
[1,2,3]
[3,2,1]
[]
[]
[1]
[1]
[2,3,1]
[3,2,1]

Outputs:

[3,9,20,null,null,15,7]
[1,2,3]
[1,2,null,3]
[1,null,2,null,3]
[]
[1]
[1,2,null,null,3]
*/