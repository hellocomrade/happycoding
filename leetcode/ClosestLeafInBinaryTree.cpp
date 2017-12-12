#include <utility>
#include <cstdlib>

using namespace std;

//
/*
742. Closest Leaf in a Binary Tree

Given a binary tree where every node has a unique value, and a target key k, find the value of the closest leaf node to target k in the tree.

Here, closest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree. Also, a node is called a leaf if it has no children.

In the following examples, the input tree is represented in flattened form row by row. The actual root tree given will be a TreeNode object.

Example 1:

Input:
root = [1, 3, 2], k = 1
Diagram of binary tree:
1
/ \
3   2

Output: 2 (or 3)

Explanation: Either 2 or 3 is the closest leaf node to the target of 1.
Example 2:

Input:
root = [1], k = 1
Output: 1

Explanation: The closest leaf node is the root node itself.
Example 3:

Input:
root = [1,2,3,4,null,null,null,5,null,6], k = 2
Diagram of binary tree:
1
/ \
2   3
/
4
/
5
/
6

Output: 3
Explanation: The leaf node with value 3 (and not the leaf node with value 6) is closest to the node with value 2.
Note:
root represents a binary tree with at least 1 node and at most 1000 nodes.
Every node has a unique node.val in range [1, 1000].
There exists some node in the given binary tree for which node.val == k.

Observations:
Idea is:

- Find the shorted distance from the leaf nodes to node k in a tree that node k is the root;
- For the remaining tree, considering node k as a virtual leaf, then find the other leaf on the same tree that is closest to node k;

The closest leaf to node k can only be one of the two.

During the recursion, if node k doesn't present as a child of a tree with node root as the root, it returns the leaf that is closer to node root.
Otherwise, examine the distance from other leafs and always returns node k.
*/
namespace ClosestLeafInBinaryTree {
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
	private:
		std::pair<int, int> aux(TreeNode *root, pair<int, int> &target, pair<int, int> &ans, int n, int &len) {
			if (nullptr == root)return std::make_pair(1001, 1001);
			std::pair<int, int> l, r;
			if (nullptr == root->left && nullptr == root->right)
				l = r = std::make_pair(root->val, n);
			else {
				l = this->aux(root->left, target, ans, n + 1, len);
				r = this->aux(root->right, target, ans, n + 1, len);
			}
			if (root->val == target.first) {//Find node k, case 1
				target.second = n;
				ans = l.second < r.second ? l : r;
				len = std::abs(n - ans.second);
				return target;
			}
			else if (target == l || target == r) {//All others fall into case 2
				std::pair<int, int> t = (l == target) ? r : l;
				if (std::abs(n * 2 - t.second - target.second) < len) {
					len = std::abs(n * 2 - t.second - target.second);
					ans = t;
				}
				return target;
			}
			else // node k doesn't share the same root yet
				return l.second < r.second ? l : r;
		}
	public:
		int findClosestLeaf(TreeNode* root, int k) {
			int len = 1000;
			std::pair<int, int> target = std::make_pair(k, -1), ans = std::make_pair(root->val, 0);
			this->aux(root, target, ans, 0, len);
			return ans.first;
		}
	};
	/*
	Test cases:

	[1,3,2]
	1
	[1]
	1
	[1,2,3,4,null,null,null,5,null,6]
	2
	[1,2,3,null,4,5,null,6,7,null,8,null,null,9,10,11,12,13,null,14,null,null,null,15,null]
	8

	Output:
	2
	1
	3
	11
	*/
}
