#include <limits>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/binary-tree-maximum-path-sum/
/*
124. Binary Tree Maximum Path Sum

Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

Example 1:

Input: [1,2,3]

1
/ \
2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

-10
/ \
9  20
/  \
15   7

Output: 42

Observation:

First, whit is the definition of "path" here? Given the following BS:
3
/ \
2   15
/ \  / \
4  -1 3  4

Vaild paths are: [4, 2], [4, 2, -1], [4, 2, 3, 15, 4], [3, 15, 4]...
Invalid paths are: [3, 15, 3, 4], [4, 2, -1, 3], ...

So, a path here is a one way street.

One may think the binary tree here can be treated as a graph and therfore this problem can be done using
the modification based upon dijkstra shortest paths. Instead of sarching shortest path, the longest path will be examined.

However, if one has finished leetcode 337 (House Robber III), the same trick can be played here using BS DFS (Post-Order).
Let's see how this recursive call should be made:

- At any given node N, the max path at N is decided byN's value, N's left child's max path and N's right child's max path.
std::max(node->val, std::max(std::max(node->val + left, node->val + right), node->val + left + right))

- At any given node N, the contribution to the build of its parent's max path is decided by N's value (definitly included) and optionally,
either N's left's max path or N's right's max path. How so? Because of the definition of the path, if N ever has any contribution to its parent,
only one child of N can be included. Of course, it's also possible neither of N's children are included.
std::max(node->val * 1LL, std::max(node->val + left, node->val + right));

Here goes maxPathSum0.

The above procedure can be simplified: since only max value is the concern for any given node N, a negative return as max path for children of N can be
discarded safely considering the fact that a negative value won't contribute to the N's max path no matter N's value is positive or not. Therefore, the above
two conditions can be:

- node->val + left + right;

- node->val + std::max(left, right);
*/
namespace BinaryTreeMaximumPathSum {
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
	public:
		int maxPathSum(TreeNode* root) {
			long long infinite = (long long)numeric_limits<int>::min() - 1, ans = infinite;
			auto dfs = [infinite, &ans](TreeNode* node, auto& fun) {
				/*
				Without the following line, lambada function argument fun can't be auto deduced due to the missing of return type
				Therefore, the recursive call on fun will fail.
				*/
				if (nullptr == node) return 0LL;//if (nullptr == node) return infinite;
				long long left = std::max(0LL, fun(node->left, fun));
				long long right = std::max(0LL, fun(node->right, fun));
				ans = std::max(ans, node->val + left + right);
				return node->val + std::max(left, right);
			};
			dfs(root, dfs);
			return static_cast<int>(ans);
		}
		int maxPathSum0(TreeNode* root) {
			long long infinite = numeric_limits<int>::min() - 1LL, ans = infinite;
			auto dfs = [infinite, &ans](TreeNode* node, auto& fun) {
				if (nullptr == node) return infinite;
				long long left = fun(node->left, fun);
				long long right = fun(node->right, fun);
				ans = std::max(ans, std::max(node->val * 1LL, std::max(std::max(node->val + left, node->val + right), node->val + left + right)));
				return std::max(node->val * 1LL, std::max(node->val + left, node->val + right));
			};
			dfs(root, dfs);
			return static_cast<int>(ans);
		}
	};
}
/*
Test cases:

[5,4,8,11,null,13,4,7,2,null,null,null,1]
[3,2,15,4,-1,3,-4]
[1]
[1,2,3]
[-10,9,20,null,null,15,7]
[1,-2,-3,null,4,1,null,-2,3]
[-1,-2,null,-3]
[-1,2,null,-3]
[-1,2,null,3]
[-1,-2,null,3]
[-10,2,6,null,7,8,null,6,-1,-9,5]
[-10,2,6,null,7,8,null,6,-1,-9,5,100]

Outputs:

48
27
1
6
42
7
-1
2
5
3
24
124
*/