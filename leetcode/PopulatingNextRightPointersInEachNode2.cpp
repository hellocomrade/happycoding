//https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
/*
117. Populating Next Right Pointers in Each Node II

Given a binary tree

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should
be set to NULL.

Initially, all next pointers are set to NULL.

Example:

Input: {"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":null,"next":null,"right":{"$id":"6","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}

Output: {"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":{"$id":"5","left":null,"next":null,"right":null,"val":7},"right":null,"val":5},"right":null,"val":4},"next":{"$id":"6","left":null,"next":null,"right":{"$ref":"5"},"val":3},"right":{"$ref":"4"},"val":2},"next":null,"right":{"$ref":"6"},"val":1}

Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its
			 next right node, just like in Figure B.

Note:

- You may only use constant extra space.
- Recursive approach is fine, implicit stack space does not count as extra space for this problem.

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
1
/  \
2    3
/ \    \
4   5    7
After calling your function, the tree should look like:
1 -> NULL
/  \
2 -> 3 -> NULL
/ \    \
4-> 5 -> 7 -> NULL

Observation:
I am not sure if the hint makes sense to me, it claims you may consider DFS. But, it appears BFS makes
more sense to me.

Again, no recursion is allowed. Given a 2 level tree, we need to find the first  not-null child node on
the lower level (second level), then find its right neighbor by moving the pointer on he higher level (first level).

We need to keep tracking the leftmost available node on the second level, so we could bump it up as
the first level for the next iteration.

***Update on 2019-06-16***

This question was asked during a phone screen for a Google Interview:

https://leetcode.com/discuss/interview-experience/303008/Google-%40-SWE-L4L5-Mountain-View-CA-Reject

leetcode also recently updated the signature of the method. Three versions have been given here.

connect1 is the first one. Since I just re-did the leetcode 116 (Populating Next Right Pointers in Each Node), connect1
is simply a modified the version of the solution of leetcode 116. Comparing with connect0, which I think having a
better readability, the biggest difference is whether or not using conditional operator. Conditional operator is always
my favorite. It's good for replacing an if-else clause with only one statement per branch. However, for this particular
one, using a conditional operator will block the idea of a better design, which could lead to a even better, shorter solution:
connect. connect is the final version. I was inspired by a solution given in discussion section.

Comparing connect with connect0, the improvement is made by removing checking if pointer currentLevel is NULL. This is
achieved by using the trick usually applied on dealing with Linked List: creating a dummy header! As long as currentLevel
is reset to the dummy header after traversal at each level, no need to check NULL on it at all.
*/
namespace PopulatingNextRightPointersInEachNode2
{

	struct TreeLinkNode {
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
	};
	// Definition for a Node.
	class Node {
	public:
		int val;
		Node* left;
		Node* right;
		Node* next;

		Node() {}

		Node(int _val, Node* _left, Node* _right, Node* _next) {
			val = _val;
			left = _left;
			right = _right;
			next = _next;
		}
	};
	class SolutionPopulatingNextRightPointersInEachNode2 {
	private:
		TreeLinkNode* scan2Right(TreeLinkNode* leftmost)
		{
			TreeLinkNode *cand = nullptr;
			TreeLinkNode* newleftmost = nullptr;
			//try to find the first available child
			while (nullptr == cand && nullptr != leftmost)
			{
				cand = leftmost->left;
				if (nullptr == cand)
					cand = leftmost->right;//is it on the right child?
				else
					break;//find available child on leftmost->left, break loop before we move leftmost to leftmost->next
				leftmost = leftmost->next;//we can safely move to leftmost->next, since even cand is not null, it is the right child of leftmost
			}
			newleftmost = cand;
			while (nullptr != leftmost)
			{
				if (nullptr != leftmost->left && leftmost->left != cand)
				{
					cand->next = leftmost->left;
					cand = cand->next;
				}
				else if (nullptr != leftmost->right && leftmost->right != cand)
				{
					cand->next = leftmost->right;
					cand = cand->next;
					leftmost = leftmost->next;
				}
				else
					leftmost = leftmost->next;
			}
			return newleftmost;
		}
	public:
		Node* connect(Node* root) {
			Node* ans = root, dummyHead = Node(), *currentLevel = &dummyHead;
			while (nullptr != root) {
				if (nullptr != root->left) currentLevel->next = root->left, currentLevel = currentLevel->next;
				if (nullptr != root->right) currentLevel->next = root->right, currentLevel = currentLevel->next;
				if (nullptr != root->next) root = root->next;
				else root = dummyHead.next, dummyHead.next = nullptr, currentLevel = &dummyHead;
			}
			return ans;
		}
		Node* connect0(Node* root) {
			Node* ans = root, *nextLevel = nullptr, *currentLevel = nullptr;
			while (nullptr != root) {
				if (nullptr == nextLevel) nextLevel = (nullptr != root->left) ? root->left : root->right;
				if (nullptr != root->left) {
					if (nullptr == currentLevel) currentLevel = root->left;
					else currentLevel->next = root->left, currentLevel = currentLevel->next;
				}
				if (nullptr != root->right) {
					if (nullptr == currentLevel) currentLevel = root->right;
					else currentLevel->next = root->right, currentLevel = currentLevel->next;
				}
				if (nullptr != root->next)
					root = root->next;
				else
					root = nextLevel, nextLevel = currentLevel = nullptr;
			}
			return ans;
		}
		Node* connect1(Node* root) {
			Node* ans = root, *next = nullptr, *prev = nullptr;
			while (nullptr != root) {
				if (nullptr == next) next = (nullptr != root->left) ? root->left : root->right;
				if (nullptr != root->left && nullptr != root->right) root->left->next = root->right, prev = root->right;
				else if (nullptr != root->left || nullptr != root->right) {
					if (nullptr != prev) {
						prev->next = (nullptr != root->left) ? root->left : root->right;
						prev = prev->next;
					}
					else
						prev = (nullptr != root->left) ? root->left : root->right;
				}
				if (nullptr != root->next) {
					if (nullptr != prev) {
						prev->next = (nullptr != root->next->left) ? root->next->left : root->next->right;
						if (nullptr != prev->next) prev = nullptr;
					}
					root = root->next;
				}
				else
					root = next, next = nullptr, prev = nullptr;
			}
			return ans;
		}
		void connect(TreeLinkNode *root) {
			TreeLinkNode *leftmost = root;
			while (leftmost)
				leftmost = this->scan2Right(leftmost);
		}
	};
}
using PNRPENode2 = PopulatingNextRightPointersInEachNode2::TreeLinkNode;
using PNRPESolution2 = PopulatingNextRightPointersInEachNode2::SolutionPopulatingNextRightPointersInEachNode2;
void TestPopulatingNextRightPointersInEachNode2()
{
	PNRPENode2 root(1);
	PNRPENode2 four(4);
	PNRPENode2 five(5);
	PNRPENode2 six(6);
	PNRPENode2 seven(7);
	PNRPENode2 three(3);
	three.left = &six;
	three.right = &seven;
	PNRPENode2 two(2);
	two.left = &four;
	two.right = &five;
	root.left = &two;
	root.right = &three;
	PNRPESolution2 so;
	so.connect(&root);

	PNRPENode2 root1(1);
	PNRPENode2 two1(2);
	PNRPENode2 three1(3);
	root1.left = &two1;
	root1.right = &three1;
	so.connect(&root1);

	PNRPENode2 root2(1);
	PNRPENode2 two2(2);
	PNRPENode2 three2(3);
	PNRPENode2 four2(4);
	PNRPENode2 five2(5);
	PNRPENode2 seven2(7);
	root2.left = &two2;
	root2.right = &three2;
	two2.left = &four2;
	two2.right = &five2;
	three2.right = &seven2;
	so.connect(&root2);

	PNRPENode2 root3(1);
	PNRPENode2 two3(2);
	PNRPENode2 three3(3);
	root3.left = &two3;
	two3.left = &three3;
	so.connect(&root3);

	PNRPENode2 root4(1);
	PNRPENode2 two4(2);
	PNRPENode2 three4(3);
	PNRPENode2 four4(4);
	PNRPENode2 five4(5);
	PNRPENode2 six4(6);
	PNRPENode2 seven4(7);
	PNRPENode2 eight4(8);
	root4.left = &two4;
	two4.right = &three4;
	three4.left = &four4;
	three4.right = &five4;
	four4.left = &six4;
	five4.left = &seven4;
	five4.right = &eight4;
	so.connect(&root4);

	PNRPENode2 root5(1);
	PNRPENode2 two5(2);
	PNRPENode2 three5(3);
	PNRPENode2 four5(4);
	PNRPENode2 five5(5);
	root5.left = &two5;
	root5.right = &three5;
	two5.left = &four5;
	three5.right = &five5;
	so.connect(&root5);
}
/*
Test cases:

{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":null,"next":null,"right":{"$id":"6","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}
{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":null,"val":2},"next":null,"right":{"$id":"4","left":null,"next":null,"right":{"$id":"5","left":null,"next":null,"right":null,"val":5},"val":3},"val":1}

Outputs:

{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":{"$id":"5","left":null,"next":null,"right":null,"val":7},"right":null,"val":5},"right":null,"val":4},"next":{"$id":"6","left":null,"next":null,"right":{"$ref":"5"},"val":3},"right":{"$ref":"4"},"val":2},"next":null,"right":{"$ref":"6"},"val":1}
{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":null,"right":null,"val":5},"right":null,"val":4},"next":{"$id":"5","left":null,"next":null,"right":{"$ref":"4"},"val":3},"right":null,"val":2},"next":null,"right":{"$ref":"5"},"val":1}
*/