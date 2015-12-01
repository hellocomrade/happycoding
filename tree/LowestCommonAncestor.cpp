#include <cassert>
#include <vector>
#include <stack>
#include <iostream>
#include "tree.h"

using namespace std;

/*
 * Let's assume that a and b exist in the binary tree
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
	    if (b == curNode->GetValue())
		hasB = curNode;
	    if (hasA != nullptr && (curNode->Left() == hasA || curNode->Right() == hasA))
		hasA = curNode;
	    if (hasB != nullptr && (curNode->Left() == hasB || curNode->Right() == hasB))
		hasB = curNode;
	    if (hasA != nullptr && hasB != nullptr && curNode == hasA && curNode == hasB)
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
void testLCA()
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

