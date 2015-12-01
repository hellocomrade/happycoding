#include <cassert>
#include <vector>
#include <stack>
#include <tuple>
#include <algorithm>
#include <iostream>
#include "btree.h"

using namespace std;

template<typename T>
const TreeNode<T>* lowestCommonAncestorBinaryTreeIterative(const TreeNode<T> *node, const T &a, const T &b)
{
    assert(node != nullptr);
    std::tuple<const TreeNode<int>*, bool, bool> triplet;
    stack<std::tuple<const TreeNode<int>*, bool, bool> > stk;
    const TreeNode<int>* lastNode = nullptr;
    const TreeNode<int>* curNode = nullptr;
    const TreeNode<int>* ancestorNode = nullptr;
    bool hasA=false, hasB=false;
    stk.push(std::make_tuple(node, a==node->GetValue(), b==node->GetValue()));
    while(true)
    {
	if(true == stk.empty())
	    break;
	while(nullptr != curNode)
	{
	    triplet=std::make_tuple(curNode, a == curNode->GetValue(), b == curNode->GetValue());
	    stk.push(triplet);
            curNode=curNode->left();
	}
	triplet = stk.top();
	curNode = std::get<0>(triplet);
	assert(nullptr != curNode);
	if(curNode->Right() == lastNode)
	{
	    stk.pop();
	    hasA = std::get<1>(triplet);
            hasB = std::get<2>(triplet);
	    lastNode = curNode;
	    curNode = nullptr;
	}
	else
	{
	    lastNode = curNode;
	    curNode = curNode->Right();
	}
    }
    return ancestorNode;  
}
