#include <queue>

using namespace std;

//https://leetcode.com/problems/sum-root-to-leaf-numbers/
/*
129. Sum Root to Leaf Numbers

Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

Note: A leaf is a node with no children.

Example:

Input: [1,2,3]
1
/ \
2   3

Output: 25

Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
Example 2:

Input: [4,9,0,5,1]
4
/ \
9   0
/ \
5   1

Output: 1026

Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.

Observations:

My first attempt is naive BFS, see sumNumbers2. At each level, the value coming from parent node will be multiplied by 10
then add onto current node's value. If the leaf node is reached, the value on the node shall be added onto final answer.
In this solution, the values in BT will be changed.

Then I noticed that this can be done in DFS, sumNumbers1 is the second try. It actually inherits the similar thought as sumNumber2:
the number is sorted out one by one and then add onto the final answer.

sumNumbers, is the elegant solution. It perfectly demonstrates the beauty of BT recursion:

Given any node N, function numberSum to calculate the sum the number sum at N is:

numberSum(N) = numberSum(N->left) + numberSum(N->right)

Of course, N->val shall be passed into numberSum(N->left) and numberSum(N->right)
*/
namespace SumRoot2LeafNumbers {
	/*
	Definition for a binary tree node.
	*/
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	public:
		int sumNumbers(TreeNode* root) {
			auto dfs = [](const TreeNode* root, int val, const auto& fun) -> int {
				if (nullptr == root) return 0;
				int i = val * 10 + root->val;
				if (nullptr == root->left && nullptr == root->right) return i;
				return fun(root->left, i, fun) + fun(root->right, i, fun);
			};
			return dfs(root, 0, dfs);
		}
		int sumNumbers1(TreeNode* root) {
			int ans = 0;
			auto dfs = [&ans](const TreeNode* root, int val, const auto& fun) -> void {
				if (nullptr == root->left && nullptr == root->right) {
					ans += val * 10 + root->val;
					return;
				}
				if (nullptr != root->left) fun(root->left, val * 10 + root->val, fun);
				if (nullptr != root->right) fun(root->right, val * 10 + root->val, fun);
			};
			if (nullptr != root) dfs(root, 0, dfs);
			return ans;
		}
		int sumNumbers2(TreeNode* root) {
			queue<TreeNode*> q;
			if (nullptr != root) q.push(root);
			int ans = 0, sz = 0;
			TreeNode *pnode = nullptr;
			while (false == q.empty()) {
				sz = q.size();
				for (int i = 0, j = 0; i < sz; ++i) {
					pnode = q.front(), q.pop();
					if (nullptr == pnode->left && nullptr == pnode->right) ans += pnode->val;
					else {
						if (nullptr != pnode->left) pnode->left->val += pnode->val * 10, q.push(pnode->left);
						if (nullptr != pnode->right) pnode->right->val += pnode->val * 10, q.push(pnode->right);
					}
				}
			}
			return ans;
		}
	};
}
/*
Test cases:

[0,1,2,3]
[1,2,3]
[4,9,0,5,1]
[]
[1]
[1,2,null,3,4,null,5,6,7,null,8,9,6,null,null,9,9]

Outputs:

15
25
1026
0
1
273360
*/