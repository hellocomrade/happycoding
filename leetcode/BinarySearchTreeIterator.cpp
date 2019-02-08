#include <stack>

using namespace std;

//https://leetcode.com/problems/binary-search-tree-iterator/
/*
173. Binary Search Tree Iterator

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Example:

BSTIterator iterator = new BSTIterator(root);

iterator.next();    // return 3

iterator.next();    // return 7

iterator.hasNext(); // return true

iterator.next();    // return 9

iterator.hasNext(); // return true

iterator.next();    // return 15

iterator.hasNext(); // return true

iterator.next();    // return 20

iterator.hasNext(); // return false

Note:

- next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
- You may assume that next() call will always be valid, that is, there will be at least a next smallest number in the BST when next() is called.

Observations:

Average O(1) time on next() and hasNext() and O(h) memory. The latter indicates some data structure like Stack!

In order to get the increasing order return, "Next Smallest", In-Order Traversal shall be used.

Since this is an iterator, revusion DFS won't work. Therefore, iterative in-order DFS is the way to go.

How to justfiy average O(1) on next()? Obvisouly, depending on if the current node has the left child, a while loop
will be executed for at most O(h) time! Well, "average" is the key here. Each node in this implementation will be visited twice,
therefore, if next() is called until hasNext() returns False, N calls will be made on next(), given N is the number of node.
Assuming visiting a node takes 1 unit time, therefore, each next() take 2 * N * 1/ N = 2.
*/
namespace BinarySearchTreeIterator {
	/**
	* Definition for a binary tree node.
	**/
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class BSTIterator {
	private:
		stack<TreeNode*> stk;
	public:
		BSTIterator(TreeNode* root) : stk() {
			if (nullptr != root) {
				stk.push(root);
				while (nullptr != root->left) stk.push(root->left), root = root->left;
			}
		}

		/** @return the next smallest number */
		int next() {
			int ans = -1;
			if (true == hasNext()) {
				TreeNode* pnode = this->stk.top();
				stk.pop();
				ans = pnode->val;
				if (nullptr != pnode->right) {
					pnode = pnode->right;
					stk.push(pnode);
					while (nullptr != pnode->left) stk.push(pnode->left), pnode = pnode->left;
				}
			}
			return ans;
		}

		/** @return whether we have a next smallest number */
		bool hasNext() {
			return false == stk.empty();
		}
	};
	class BSTIterator0 {
	private:
		TreeNode* currentNode;
		stack<TreeNode*> stk;
	public:
		BSTIterator0(TreeNode* root) : stk(), currentNode(root) {

		}

		/** @return the next smallest number */
		int next() {
			int ans = -1;
			if (true == hasNext()) {
				while (nullptr != currentNode) stk.push(currentNode), currentNode = currentNode->left;
				ans = stk.top()->val;
				currentNode = stk.top()->right;
				stk.pop();
			}
			return ans;
		}

		/** @return whether we have a next smallest number */
		bool hasNext() {
			return nullptr != currentNode || false == stk.empty();
		}
	};
	/**
	* Your BSTIterator object will be instantiated and called as such:
	* BSTIterator* obj = new BSTIterator(root);
	* int param_1 = obj->next();
	* bool param_2 = obj->hasNext();
	*/
}
/*
Test cases:

["BSTIterator","next","next","hasNext","next","hasNext","next","hasNext","next","hasNext"]
[[[7,3,15,null,null,9,20]],[null],[null],[null],[null],[null],[null],[null],[null],[null]]
["BSTIterator","hasNext","next","hasNext","next","hasNext"]
[[[1,null,2]],[null],[null],[null],[null],[null]]

Outputs:

[null,3,7,true,9,true,15,true,20,false]
[null,true,1,true,2,false]
*/