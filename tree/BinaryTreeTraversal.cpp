#include <cassert>
#include <vector>
#include <stack>
#include <queue>
#include "tree.h"

using namespace std;

template<typename T>
vector<T> PreOrderBinaryTreeTraversalIterative(const TreeNode<T>* node)
{
    assert(nullptr != node);
    vector<T> vec;
    stack<const TreeNode<T>*> stk;
    const TreeNode<T>* currentNode = node;
    stk.push(node);
    while(false == stk.empty())
    {
	currentNode = stk.top();
	stk.pop();
	vec.push_back(currentNode->GetValue());
	if(nullptr != currentNode->Right())
	    stk.push(currentNode->Right());
	if(nullptr != currentNode->Left())
	    stk.push(currentNode->Left());
    }
    return vec;
}
template<typename T>
vector<T> InOrderBinaryTreeTraversalIterative(TreeNode<T>* node)
{
    assert(nullptr != node);
    vector<T> vec;
    stack<TreeNode<T>*> stk;
    const TreeNode<T>* currentNode = node;
    while(true)
    {
	while(nullptr != currentNode)
	{
	    stk.push(currentNode);
	    currentNode = currentNode->Left();
	}
	if(true == stk.empty())
	    break;
	currentNode = stk.top();
	stk.pop();
	vec.push_back(currentNode->GetValue());
	currentNode = currentNode->Right();	
    }
    return vec;
}
template<typename T>
vector<T> PostOrderBinaryTreeTraversalIterative(TreeNode<T>* node)
{
    assert(nullptr != node);
    vector<T> vec;
    stack<TreeNode<T>*> stk;
    const TreeNode<T>* currentNode = node;
    const TreeNode<T>* lastNode = nullptr;
    while(true)
    {
	while(nullptr != currentNode)
        {
            stk.push(currentNode);
            currentNode = currentNode->Left();
        }
        if(true == stk.empty())
            break;
	currentNode = stk.top();
	if( currentNode->Right() == lastNode)
	{
	    stk.pop();
	    vec.push_back(currentNode->GetValue());
	    lastNode = currentNode;
	    currentNode = nullptr;
	}
	else
	{
	    lastNode = nullptr;
	    currentNode = currentNode->Right();
	}
    }
    return vec;
}
void testTreeTraversal()
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

    vector<char> vec = PreOrderBinaryTreeTraversalIterative<char>(&f);
    cout << "Expect 'F,B,A,D,C,E,G,I,H,': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = InOrderBinaryTreeTraversalIterative<char>(&f);
    cout << "Expect 'A,B,C,D,E,F,G,H,I,': ";
    for (char c : vec)
 	cout << c << ',';
    cout << endl;

    vec = PostOrderBinaryTreeTraversalIterative<char>(&f);
    cout << "Expect 'A,C,E,D,B,H,I,G,F,': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;
}
