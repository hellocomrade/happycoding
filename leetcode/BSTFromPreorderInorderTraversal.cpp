#include <vector>
#include <unordered_map>

using namespace std;

//https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
/*
105. Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

Observations:
First of all, you have to realize that a binary tree structure can only be decided by at least two traversals output.
Therefore, with a preorder output and inorder output, we should be able to construct a binary tree without
any ambiguity.

As we all know, preorder traversal always visits the root first at any given level. Preorder, on the other hand, always
split the tree from left subtree and right subtree at the position where root is.

Therefore, by loop through the preorder output, we can repeatly split the output of inorder traversal and get the left and right
subtree at the position that split occurs. It's intuitive to do this recursively as divide and conquer. We
stop the resursion if there is no element anymore in inorder array based upon start and end index.

The complications are:
1. How we could terminate the resursion?
2. How we could move the pointer on preorder output, so we could always point it to the root of left subtree
and right subtree?

Since we use preorder as index to search the inorder output, it might be wise to hash table inorder output.
Then we could find the index (split position) in inorder output in O(1) time. By doing so, we could make
sure overall construction time is O(NlogN)
*/
namespace BSTFromPreorderInorderTraversal {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class SolutionBSTFromPreorderInorderTraversal {
	private:
		TreeNode* aux(const vector<int>& preorder, unordered_map<int, int>& memo, int start, int end, int rootIdxPre) {
			//if (start > end || rootIdxPre >= preorder.size())return nullptr;
			//It appears the first condition implicitly includes the second one.
			if (start > end)return nullptr;
			int i = memo[preorder[rootIdxPre]];
			TreeNode* root = new TreeNode(preorder[rootIdxPre]);
			//Index for left subtree's root in preorder array is always rootIdxPre + 1
			root->left = aux(preorder, memo, start, i - 1, rootIdxPre + 1);
			//Index for right subtree's root in preorder array is rootIdxPre + numer of element in left subtree + 1
			root->right = aux(preorder, memo, i + 1, end, rootIdxPre + i - start + 1);
			return root;
		}
		/**
		*@param preorder : A list of integers that preorder traversal of a tree
		*@param inorder : A list of integers that inorder traversal of a tree
		*@return : Root of a tree
		*/
	public:
		TreeNode *buildTree(const vector<int> &preorder, const vector<int> &inorder) {
			int len1 = preorder.size();
			int len2 = inorder.size();
			if (len1 != len2)return nullptr;
			unordered_map<int, int> memo;
			for (int i = 0; i < len2; ++i)
				memo.emplace(inorder[i], i);
			return this->aux(preorder, memo, 0, len2 - 1, 0);
		}
	};
}
void TestBSTFromPreorderInorderTraversal() {
	using BFPI = BSTFromPreorderInorderTraversal::SolutionBSTFromPreorderInorderTraversal;
	BFPI so;
	so.buildTree(vector<int>{1, 2, 4, 5, 3, 6, 7}, vector<int>{4, 5, 2, 1, 6, 3, 7});
}