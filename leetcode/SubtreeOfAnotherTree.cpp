//https://leetcode.com/problems/subtree-of-another-tree/
/*
572. Subtree of Another Tree

Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

3
/ \
4   5
/ \
1   2
Given tree t:
4
/ \
1   2
Return true, because t has the same structure and node values with a subtree of s.

Example 2:
Given tree s:

3
/ \
4   5
/ \
1   2
/
0
Given tree t:
4
/ \
1   2
Return false.

Observations:
This problem is also available at lintcode, but with a subtle difference.
http://lintcode.com/en/problem/subtree/

It is claimed as a Google interview question. S is with millions of nodes and t has only couple hundreds of nodes.
In such a context, the ways to solve the problem could be totally different.

Let's start from the "standard" solution using recursion. Before we start, we have to notice that:

An empty tree is a sub-tree of any non-empty tree. Therefore, if t is NULL and s is not NULL, t is considered as s' subtree!

- We need to have a fucntion to examine if two trees are identical, which means t1->val is equal to t2->val and the trees rooted at their
left children and right children are identical as well. Be aware, two empty trees are considered same as well. So if
nullptr == s && nullptr == t, t and s are same.

- Where and how to trigger this isSame function? The naive solution would be pre-order traversal on tree s and then
examine every node on s with t. At any given node Si on tree s, we do:

this->isSame(Si, t) || this->isSubtree(Si->left, t) || this->isSubtree(Si->right, t);

if and only if Si is not NULL. Or isSame fails when nullptr == Si unless t itself is NULL, which meets the notice we
mentioned earlier: an empty tree is a subtree of any non-empty tree.

Regarding Google interview, I'd argue the above approach is naive and wastes too much time on unnecessary comparsion. The
comparison shall only be initialized on tree s, when there are only Ht levels of nodes left on s, where Ht is equal to
the height of tree t.

In such an assumption, we will have to replace depth first traversal to breadth first, level-order traversal. Keep tracking
the nodes on tree s until we reach the level Ht, from where we start comparing Si on level Ht with tree t.


Leetcode Official Solution at: https://leetcode.com/problems/subtree-of-another-tree/solution/

*/
namespace SubtreeOfAnotherTree {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class Solution {
	private:
		bool isSame(TreeNode *t1, TreeNode *t2) {
			if (nullptr == t1 && nullptr == t2)return true;
			else if (nullptr == t1 || nullptr == t2)return false;
			return t1->val == t2->val && isSame(t1->left, t2->left) && isSame(t1->right, t2->right);
		}
	public:
		bool isSubtree(TreeNode* s, TreeNode* t) {
			if (nullptr == t)return true;
			else if (nullptr == s)return false;
			return this->isSame(s, t) || this->isSubtree(s->left, t) || this->isSubtree(s->right, t);
		}
	};
}