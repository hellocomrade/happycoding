//https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
/*
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
*/
namespace PopulatingNextRightPointersInEachNode2
{

	struct TreeLinkNode {
		int val;
		TreeLinkNode *left, *right, *next;
		TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
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