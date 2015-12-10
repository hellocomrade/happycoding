#include <cassert>
#include <vector>
#include <stack>
#include <iostream>
#include "tree.h"
#include <cstdio>
#include <climits>
#include "btree.h"

using namespace std;

/*
 * Let's assume that a and b exist in the binary tree
 *
 * Iterative search is based upon a post order depth first traversal
 *
 * Use two pointers, hasA and hasB, to track the branch that has a or b discovered from bottom to the root of the tree
 *
 * The visted node who has both hasA and hasB pointed to is the LCA
 */
template<typename T>
const TreeNode<T>* lowestCommonAncestorBinaryTreeIterative(const TreeNode<T> *node, const T &a, const T &b)
{
    assert(node != nullptr);
    stack<const TreeNode<T>*> stk;
    const TreeNode<T>* lastNode = nullptr;
    const TreeNode<T>* curNode = node;
    const TreeNode<T> *hasA = nullptr, *hasB = nullptr;
    while (true)
    {
	while (nullptr != curNode)
	{
	    stk.push(curNode);
	    curNode = curNode->Left();
	}
	if (true == stk.empty())
	    break;
	curNode = stk.top();
	assert(nullptr != curNode);
	if (curNode->Right() == lastNode)
	{
	    if (a == curNode->GetValue())
		hasA = curNode;
	    else if (hasA != nullptr && (curNode->Left() == hasA || curNode->Right() == hasA))
                hasA = curNode;
	    if (b == curNode->GetValue())
		hasB = curNode;
	    else if (hasB != nullptr && (curNode->Left() == hasB || curNode->Right() == hasB))
		hasB = curNode;
	    //if both hasA and hasB have been pointed to curNode, then it's the LCA
	    if (curNode == hasA && curNode == hasB)
		break;
	    lastNode = curNode;
	    curNode = nullptr;
	    stk.pop();
	}
	else
	{
	    lastNode = nullptr;
	    curNode = curNode->Right();
	}
    }
    return curNode;
}
void testLowestCommonAncestorBinaryTreeIterative()
{
    TreeNode<char> a('A', nullptr, nullptr);
    TreeNode<char> c('C', nullptr, nullptr);
    TreeNode<char> e('E', nullptr, nullptr);
    TreeNode<char> h('H', nullptr, nullptr);
    TreeNode<char> d('D', &c, &e);
    TreeNode<char> b('B', &a, &d);
    TreeNode<char> i('I', &h, nullptr);
    TreeNode<char> g('G', nullptr, &i);
    TreeNode<char> f('F', &b, &g);

    const TreeNode<char>* ancestor = lowestCommonAncestorBinaryTreeIterative<char>(&f, 'A', 'E');
    cout << "Expect B: " << ancestor->GetValue() << endl;
    const TreeNode<char>* ancestor1 = lowestCommonAncestorBinaryTreeIterative<char>(&f, 'A', 'H');
    cout << "Expect F: " << ancestor1->GetValue() << endl;
    const TreeNode<char>* ancestor2 = lowestCommonAncestorBinaryTreeIterative<char>(&f, 'E', 'H');
    cout << "Expect F: " << ancestor2->GetValue()<< endl;
    const TreeNode<char>* ancestor3 = lowestCommonAncestorBinaryTreeIterative<char>(&f, 'A', 'C');
    cout << "Expect B: " << ancestor3->GetValue() << endl;
    const TreeNode<char>* ancestor4 = lowestCommonAncestorBinaryTreeIterative<char>(&f, 'C', 'D');
    cout << "Expect D: " << ancestor4->GetValue() << endl;
    const TreeNode<char>* ancestor5 = lowestCommonAncestorBinaryTreeIterative<char>(&f, 'G', 'G');
    cout << "Expect G: " << ancestor5->GetValue() << endl;
    const TreeNode<char>* ancestor6 = lowestCommonAncestorBinaryTreeIterative<char>(&f, 'D', 'I');
    cout << "Expect F: " << ancestor6->GetValue() << endl;
    const TreeNode<char>* ancestor7 = lowestCommonAncestorBinaryTreeIterative<char>(&a, 'A', 'A');
    cout << "Expect A: " << ancestor7->GetValue() << endl;
}
const int missing = INT_MIN;
/*
 * Recursive version of LCA
 * Recursively check left and right subtrees, find lca only if:
 * 1. both a and b are found in left and right children
 * 2. find a or b in either left or right child, the current node has b or a
 * If neither of above is satisfied, report missing to upper stream
 */
static int lca(BinaryTreeNode *root,int a,int b)
{
    int l, r;
    if(root)
    {
	l=lca(root->left,a,b);
	r=lca(root->right,a,b);
	if (a == l&&b == r){
	    printf("Found lca for (%d,%d) with value:%d\n", a, b, root->data);
	    return missing;
	}
	else if (root->data == a)
	{
	    if (l == b || r == b)
	    {
		printf("Found lca for (%d,%d) with value:%d\n", a, b, root->data);
		return missing;
	    }
	    else
	        return a;
	}
	else if (root->data == b)
	{
	    if (l == a || r == a)
	    {
	        printf("Found lca for (%d,%d) with value:%d\n", a, b, root->data);
		return missing;
	    }
	    else
	        return b;
	}
	if (l > missing)return l;
	else if (r > missing)return r;
	else return missing;
    }
    return missing;
}

void testlca()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
    BinaryTreeNode *root = buildBTreeFromArrayBFT(arr, sizeof(arr) / sizeof(int));
    lca(root, 4, 6);
    lca(root, 4, 5);
    lca(root, 2, 4);//2 is the immediate parent of 4, so the lca=2
    lca(root, 4, 3);
    lca(root, 5, 7);
    lca(root, 3, 2);
    lca(root, 5, 6);
    lca(root, 3, 7);
}
