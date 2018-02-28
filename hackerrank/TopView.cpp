#include <iostream>

using namespace std;

//https://www.hackerrank.com/challenges/tree-top-view/problem
/*
Tree : Top View

You are given a pointer to the root of a binary tree. Print the top view of the binary tree.
Top view means when you look the tree from the top the nodes you will see will be called the top view of the tree. See the example below.
You only have to complete the function.
For example :

1
\
2
\
5
/  \
3    6
\
4
Top View : 1 -> 2 -> 5 -> 6

Input Format

You are given a function,

void topView(node * root) {

}
Constraints

1 Nodes in the tree  500

Output Format

Print the values on a single line separated by space.

Sample Input

1
\
2
\
5
/  \
3    6
\
4
Sample Output

1 2 5 6

Explanation

1
\
2
\
5
/  \
3    6
\
4
From the top only nodes 1,2,5,6 will be visible.

Observations:

This is supposed to be a fun question: top view is the leftmost nodes and rightmost nodes at each level.

However, I can't tell how they should be printed, in what order?

Again, this is a typical HackerRank challenge: the question itself is never well described. The example in the description
has no left subtree from root, given it no clue how the left end should be displayed...

1
/ \
2   3
/ \   \
4   5   6

A reasonable example should look like above: the output is: 4 2 1 3 6

Now you know it asks an in-order like tree traversal. We will have to split this in two pieces starting from root

- From root->left, we only do left tree in-order and skip right tree;

- From root->right, we only do right tree in-order and skip left tree;
*/
namespace TopView {
	struct node
	{
		int data;
		node* left;
		node* right;
	};
	class TopView {
	private:
		void _aux(node *root, bool isLeft) {
			if (nullptr == root)return;
			if (true == isLeft) _aux(root->left, isLeft), cout << root->data << ' ';
			else cout << root->data << ' ', _aux(root->right, isLeft);
		}
	public:
		void topView(node * root) {
			if (nullptr == root)return;
			_aux(root->left, true);
			cout << root->data << ' ';
			_aux(root->right, false);
		}
	};
}