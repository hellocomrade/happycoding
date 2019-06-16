//https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
/*
116. Populating Next Right Pointers in Each Node

Given a binary tree

struct TreeLinkNode {
TreeLinkNode *left;
TreeLinkNode *right;
TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
1
/  \
2    3
/ \  / \
4  5  6  7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \  / \
4->5->6->7 -> NULL

Observation:
Nothing too serious, since it asks for contstant space, recursion approach doesn't apply here.

Simply take advantage of the next pointer built at the higher level, you can traverse the node at
the same level from left to right. Then the next iteration always start from the left most node.

***Update on 2019-06-15***
This question was asked during the phone screen interview of either Microsoft or Google. I lost track of the original post though.
leetcode also updated the signature of the method. Therefore, I redo both the interative and recursive versions.
*/
namespace PopulatingNextRightPointersInEachNode
{
	/**
	* Definition for binary tree with next pointer.
	*/
	struct TreeLinkNode {
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
	};

	class SolutionPopulatingNextRightPointersInEachNode {
	private:
		void aux(TreeLinkNode *node, TreeLinkNode *next)
		{
			if (nullptr == node)
				return;
			node->next = next;
			aux(node->left, node->right);
			aux(node->right, node->next == nullptr ? nullptr : node->next->left);
		}
	public:
		TreeLinkNode* connect(TreeLinkNode *root) {
			TreeLinkNode *ans = root, *left = nullptr;
			while (nullptr != root && nullptr != root->left) {
				if (nullptr == left) left = root->left;
				root->left->next = root->right;
				if (nullptr != root->next) root->right->next = root->next->left, root = root->next;
				else root = left, left = nullptr;
			}
			return ans;
		}
		TreeLinkNode* connect0(TreeLinkNode *root) {
			if (nullptr == root) return nullptr;
			if (nullptr != root->left) {
				root->left->next = root->right;
				if (nullptr != root->next) root->right->next = root->next->left;
				connect0(root->left);
				connect0(root->right);
			}
			return root;
		}
		void connect_old(TreeLinkNode *root) {
			TreeLinkNode *leftmost = root;
			root = nullptr;
			while (nullptr != leftmost) {
				if (nullptr == root) {
					root = leftmost;
					leftmost = root->left;
					if (nullptr == leftmost)break;
				}
				root->left->next = root->right;
				root->right->next = (nullptr != root->next) ? root->next->left : nullptr;
				root = root->next;
			}
		}
		void connect2(TreeLinkNode *root) {
			aux(root, nullptr);
		}
		void connect1(TreeLinkNode *root) {
			if (nullptr == root)return;
			TreeLinkNode *tn = nullptr;
			while (root->left)
			{
				root->left->next = root->right;
				root->right->next = nullptr == root->next ? nullptr : root->next->left;
				tn = root;
				while (root->next)
				{
					root = root->next;
					root->left->next = root->right;
					root->right->next = nullptr == root->next ? nullptr : root->next->left;
				}
				root = tn->left;
			}
		}
	};
}
using PNRPENode = PopulatingNextRightPointersInEachNode::TreeLinkNode;
using PNRPESolution = PopulatingNextRightPointersInEachNode::SolutionPopulatingNextRightPointersInEachNode;
void TestPopulatingNextRightPointersInEachNode()
{
	PNRPENode root(1);
	PNRPENode four(4);
	PNRPENode five(5);
	PNRPENode six(6);
	PNRPENode seven(7);
	PNRPENode three(3);
	three.left = &six;
	three.right = &seven;
	PNRPENode two(2);
	two.left = &four;
	two.right = &five;
	root.left = &two;
	root.right = &three;
	PNRPESolution so;
	so.connect(&root);

	PNRPENode root1(1);
	PNRPENode two1(2);
	PNRPENode three1(3);
	root1.left = &two1;
	root1.right = &three1;
	so.connect(&root1);
}
/*
Test cases:

{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":{"$id":"6","left":null,"next":null,"right":null,"val":6},"next":null,"right":{"$id":"7","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}
{"$id":"1","left":null,"next":null,"right":null,"val":0}

Outputs:

{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":{"$id":"5","left":null,"next":{"$id":"6","left":null,"next":null,"right":null,"val":7},"right":null,"val":6},"right":null,"val":5},"right":null,"val":4},"next":{"$id":"7","left":{"$ref":"5"},"next":null,"right":{"$ref":"6"},"val":3},"right":{"$ref":"4"},"val":2},"next":null,"right":{"$ref":"7"},"val":1}
{"$id":"1","left":null,"next":null,"right":null,"val":0}
*/