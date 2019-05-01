#include <functional>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/delete-node-in-a-bst/
/*
450. Delete Node in a BST

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

- Search for a node to remove.
- If the node is found, delete the node.

Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]

key = 3

	5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

	5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

	5
   / \
  2   6
   \   \
	4   7

Observations:

Believe it or not, I totally ignore the fact this is a BST not a BT even the notes says the time complexity
should be O(height of tree) :)

There goes my first deleteNode1. It's actually pretty easy to change it for BST and it will run faster. However,
it's still not an elegant recursion due to the fact that I failed to recognize the correct way to link parent node
with children and therefore had to pass parent node along with the current node into recursion function...

A better looked general BT solution is deleteNode00. However, it has a cost associated with the much cleaner code:
it introduces multiple removals and therefore time complexity is guaranteed O(N).

Combining the lession we took from deleteNode1 and deleteNode00, here we have deleteNode0: a BS node removal function
using recursion. Rationale is:

- If key is not found on current node, search both left child and right child;
- If key found on current node, root and root is a leaf node, return nullptr;
- If key found on current node, root and root only has left child, replace root with root->left, L and return L.
  Assigning L to its root's parent is done through the nature of recursion;
- If key found on current node, root and root has both left and right child, replace root with root->right's
  leftmost child, N (N does NOT have left child). In this case, we will have to consider more details:
  1. N's new left child is root->left;
  2. If N has right child NR, NR will be N's parent left child;
  3. Step 2 is only necessary if N is NOT root->right;
  4. Return N;

The true BST node removal solution is here:

https://leetcode.com/problems/delete-node-in-a-bst/solution/

deleteNode, it will also introduce more than one removal but the overall time complexity is O(log(H)) due to BST.
The idea is:

1. Search key through BST;
2. If key is found on current node, root and root is a leaf node, return nullptr;
3. If key is found on current node, root and root->right is not nullptr,
   set root->val to root's successor's val in in-order traversal and resume searching on root->val as key and it will hit
   root's successor for sure;
4. If key is found on current node, root and root->left is not nullptr but root->right is nullptr,
   set root->val to root's predecessor's val in in-order traversal and resume searching on root->val as key and it will hit
   root's predecessor for sure;

That has been said, it's actually interesting to see that leetcode judge's code works for general BS. Therefore,
its implementation is definitely not as same as deleteNode...

Note: the test cases below may not work for deleteNode since it relies on the character of BST.
*/
namespace DeleteBSTNode {
	//Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	private:
		TreeNode* successor(TreeNode* root) {
			if (nullptr == root || nullptr == root->right) return nullptr;
			root = root->right;
			while (nullptr != root->left) root = root->left;
			return root;
		}
		TreeNode* predecessor(TreeNode* root) {
			if (nullptr == root || nullptr == root->left) return nullptr;
			root = root->left;
			while (nullptr != root->right) root = root->right;
			return root;
		}
	public:
		TreeNode* deleteNode(TreeNode* root, int key) {
			if (nullptr == root) return root;
			if (key > root->val) root->right = deleteNode(root->right, key);
			else if (key < root->val) root->left = deleteNode(root->left, key);
			else {
				if (nullptr != root->right) {
					root->val = this->successor(root)->val;
					root->right = deleteNode(root->right, root->val);
				}
				else if (nullptr != root->left) {
					root->val = this->predecessor(root)->val;
					root->left = deleteNode(root->left, root->val);
				}
				else {
					delete root;
					root = nullptr;
				}
			}
			return root;
		}
		TreeNode* deleteNode0(TreeNode* root, int key) {
			if (nullptr == root) return root;
			TreeNode *pn = nullptr, *ppn = nullptr;
			if (key == root->val) {
				if (nullptr != root->right) {
					pn = ppn = root->right;
					while (nullptr != pn->left) ppn = pn, pn = pn->left;
					if (ppn != pn) ppn->left = pn->right;
					pn->left = root->left;
					if (pn != root->right) pn->right = root->right;
				}
				else if (nullptr != root->left)
					pn = root->left;
				delete root;
				return pn;
			}
			else {
				root->left = deleteNode0(root->left, key);
				root->right = deleteNode0(root->right, key);
			}
			return root;
		}
		/*
		A better written general BT node removal, O(N) time
		The trade off for a shorter, better looking function is: there will be more than 1 removal
		since swap will introduce another node with val of key...
		*/
		TreeNode* deleteNode00(TreeNode* root, int key) {
			if (nullptr == root) return root;
			TreeNode* pnode = nullptr;
			if (key == root->val) {
				if (nullptr == root->right) {
					pnode = root->left;
					delete root;
					return pnode;
				}
				else {
					pnode = root->right;
					while (nullptr != pnode->left) pnode = pnode->left;
					std::swap(root->val, pnode->val);
				}
			}
			root->left = deleteNode00(root->left, key);
			root->right = deleteNode00(root->right, key);
			return root;
		}
		//Ignored BST, general BT, O(N) time, recursion stops when the node with val of key is found
		TreeNode* deleteNode1(TreeNode* root, int key) {
			function<void(TreeNode*, TreeNode*)> fun = [&](TreeNode* pnode, TreeNode* parent) -> void {
				if (nullptr == pnode) return;
				TreeNode *pn = nullptr, *ppn = nullptr;
				if (key == pnode->val) {
					if (nullptr != pnode->left && nullptr != pnode->right) {
						pn = ppn = pnode->right;
						while (nullptr != pn->left) ppn = pn, pn = pn->left;
						if (ppn != pn) ppn->left = pn->right;
						pn->left = pnode->left;
						if (pn != pnode->right) pn->right = pnode->right;
					}
					else if ((nullptr == pnode->left) ^ (nullptr == pnode->right))
						pn = (nullptr != pnode->left) ? pnode->left : pnode->right;
					if (nullptr == parent) root = pn;
					else if (pnode == parent->left) parent->left = pn;
					else parent->right = pn;
				}
				else {
					fun(pnode->left, pnode);
					fun(pnode->right, pnode);
				}
			};
			fun(root, nullptr);
			return root;
		}
	};
}
/*
Not all test cases work for deleteNode since it depends on the nature of BST.

Test cases:

[5,3,6,2,4,null,7,8,9,10,11]
3
[5,10,6,2,4,null,7,8,9,null,11]
11
[5,3,6,2,4,null,7]
3
[5,3,6,2,4,null,7]
5
[5,3,6,2,4,null,7]
3
[5,3,6,2,4,null,7]
6
[5,3,6,2,4,null,7]
3
[5,3,6,2,4,null,7]
2
[5,3,6,2,4,null,7]
3
[5,3,6,2,4,null,7]
4
[5,3,6,2,4,null,7]
3
[5,3,6,2,4,null,7]
7
[5]
5
[5]
1
[]
1
[1,2,3,4,null,5,6,7,8,9,10]
2
[1,2,3,4,null,5,6,7,8,9,10]
1
[1,2,3,4,null,5,6,7,8,9,10]
3
[1,2,3,4,null,5,6,7,8,9,10]
5
[1,2,3,4,null,5,6,7,8,9,10]
4
[1,2,3,4,null,5,6,7,8,9,10]
6
[1,2,3,4,null,5,6,7,8,9,10]
7
[1,2,3,4,null,5,6,7,8,9,10]
8
[1,2,3,4,null,5,6,7,8,9,10]
9
[1,2,3,4,null,5,6,7,8,9,10]
10

Outputs:

[5,10,6,2,4,null,7,8,9,null,11]
[5,10,6,2,4,null,7,8,9]
[5,4,6,2,null,null,7]
[6,3,7,2,4]
[5,4,6,2,null,null,7]
[5,3,7,2,4]
[5,4,6,2,null,null,7]
[5,3,6,null,4,null,7]
[5,4,6,2,null,null,7]
[5,3,6,2,null,null,7]
[5,4,6,2,null,null,7]
[5,3,6,2,4]
[]
[5]
[]
[1,4,3,7,8,5,6,null,null,null,null,9,10]
[9,2,3,4,null,5,6,7,8,null,10]
[1,2,6,4,null,5,null,7,8,9,10]
[1,2,3,4,null,10,6,7,8,9]
[1,2,3,8,null,5,6,7,null,9,10]
[1,2,3,4,null,5,null,7,8,9,10]
[1,2,3,4,null,5,6,null,8,9,10]
[1,2,3,4,null,5,6,7,null,9,10]
[1,2,3,4,null,5,6,7,8,null,10]
[1,2,3,4,null,5,6,7,8,9]
*/