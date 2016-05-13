#include <vector>
//https://leetcode.com/problems/unique-binary-search-trees-ii/
/*
Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

1         3     3      2      1
\       /     /      / \      \
3     2     1      1   3      2
/     /       \                 \
2     1         2                 3

Observation:
Following the same idea of Unique Binary Search Trees, we can actually print out all possible BST with
an extra two dimensional vector with the element type vector<TreeNode*>. memo[i][j] for i, j in [1, n]
means the possible BST if numbers in range [i, j] are given.

We can easily tell all memo[i][i] has one element TreeNode(i), except for i = 0, where memo[0][0] = nullptr.

Be aware, we didn't free the memory for TreeNode on each run...
*/
namespace UniqueBinarySearchTrees2
{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class SolutionUniqueBinarySearchTrees2
	{
	private:
		std::vector<TreeNode*>& trace(int start, int end, std::vector<std::vector<std::vector<TreeNode*> > >& memos)
		{
			if (start > end || start <= 0 || end <= 0)
				start = end = 0;
			if (memos[start][end].size() > 0)
				return memos[start][end];
			TreeNode* root = nullptr;
			for (int i = start; i <= end; ++i)
			{
				std::vector<TreeNode*> leftTree = trace(start, i - 1, memos);
				std::vector<TreeNode*> rightTree = trace(i + 1, end, memos);
				for (auto left : leftTree)
				{
					for (auto right : rightTree)
					{
						root = new TreeNode(i);
						root->left = left;
						root->right = right;
						memos[start][end].push_back(root);
					}
				}
			}
			return memos[start][end];
		}
	public:
		std::vector<TreeNode*> generateTrees(int n)
		{
			if (0 == n)return std::vector<TreeNode*>();
			std::vector<std::vector<std::vector<TreeNode*> > > memos(n + 1, std::vector<std::vector<TreeNode*> >(n + 1, std::vector<TreeNode*>()));
			memos[0][0].push_back(nullptr);
			for (int i = 1; i <= n; ++i)
				memos[i][i].push_back(new TreeNode(i));
			std::vector<TreeNode*>& trees = trace(1, n, memos);
			return trees;
		}
	};
}
void TestUniqueBinarySearchTrees2()
{
	UniqueBinarySearchTrees2::SolutionUniqueBinarySearchTrees2 ubst2;
	auto vec = ubst2.generateTrees(2);
	vec = ubst2.generateTrees(3);
	vec = ubst2.generateTrees(1);
	vec = ubst2.generateTrees(0);
}