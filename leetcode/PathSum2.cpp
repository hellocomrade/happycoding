#include <vector>

using namespace std;

//https://leetcode.com/problems/path-sum-ii/
/*
113. Path Sum II

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

5
/ \
4   8
/   / \
11  13  4
/ \    / \
7  2  5   1

Return:

[
[5,4,11,2],
[5,8,4,5]
]

Observations:

This is a follow up of leetcode 112 (Path Sum). Instead of asking if such a sum exists, this problem
requires returning all paths. This is a clear indication of Complete Search. Since all paths shall be
returned, backtracing appears to be the best choice if it can be applied.

Both pathSum0 and pathSum follow the theory above.

pathSum0 is a naive version that doesn't completely implement BT. Since pre-order dfs is used, node value is
either pushed to the vector or replaces the element with index that is equal to depth on the vector. Be aware,
since vector is never resized, its actually length always grows and therefore, when copying full path to ans,
it's possible that only a subarray of the vector shall be copied over.

pathSum is a standard BT which pushs every node on the back of the vector and then pop it at the end of the recursive
function. Since the length of vector always matches the depth of the path, copying the full vector to the result is
safe.
*/
namespace PathSum2 {
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
		vector<vector<int>> pathSum(TreeNode* root, int sum) {
			vector<int> memo;
			vector<vector<int> > ans;
			auto fun = [&ans, &memo](const TreeNode* pnode, const int s, const auto& f) {
				if (nullptr == pnode) return;
				memo.push_back(pnode->val);
				if (nullptr == pnode->left && nullptr == pnode->right && s == pnode->val)
					ans.push_back(memo);
				f(pnode->left, s - pnode->val, f);
				f(pnode->right, s - pnode->val, f);
				memo.pop_back();
			};
			fun(root, sum, fun);
			return ans;
		}
		vector<vector<int>> pathSum0(TreeNode* root, int sum) {
			vector<int> memo;
			vector<vector<int> > ans;
			auto fun = [&ans, &memo](const TreeNode* pnode, const int s, const int depth, const auto& f) {
				if (depth == memo.size()) memo.push_back(pnode->val);
				else memo[depth] = pnode->val;
				if (nullptr == pnode->left && nullptr == pnode->right && s == pnode->val) {
					ans.push_back(vector<int>(memo.begin(), memo.begin() + depth + 1));
					return;
				}
				if (nullptr != pnode->left) f(pnode->left, s - pnode->val, depth + 1, f);
				if (nullptr != pnode->right) f(pnode->right, s - pnode->val, depth + 1, f);
			};
			if (nullptr != root) fun(root, sum, 0, fun);
			return ans;
		}
	};
}
/*
Test cases:

[5,4,8,11,null,13,4,7,2,null,null,5,1]
22
[1,2,2,3,3,2,4,4,5,null,6,6,7,null,8]
12
[1,2,2,3,3,2,4,4,5,null,6,6,7,null,8]
14
[1,2,2,3,3,2,4,4,5,null,6,6,7,null,8]
15
[1,2,3,3,2]
6
[1,2,3,3,null,2]
6
[]
10
[1]
1
[1]
0
[1,2]
3
[1,2]
1

Outputs:

[[5,4,11,2],[5,8,4,5]]
[[1,2,3,6],[1,2,2,7]]
[]
[[1,2,4,8]]
[[1,2,3]]
[[1,2,3],[1,3,2]]
[]
[[1]]
[]
[[1,2]]
[]
*/