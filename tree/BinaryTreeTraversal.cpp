#include <cassert>
#include <vector>
#include <stack>
#include <queue>
#include "tree.h"

using namespace std;

/*
 * Iterative Preorder Traversal is the simplest among three.
 * Push head onto stack to form a non-empty stack to start the loop
 * Take the top elem from stack then pop it, visit it
 * Then pushing right child and left child onto the stack as long as they are not null
 * Loop ends if there is no more elem on the stack
 */
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
/*
 * Iterative InOrder Traversal:
 * Drive to the most left no matter what. Therefore, you can push the head onto
 * the stack bfore loop starts. So, we can't use stack.empty() as the exit condition for the loop
 * We can only use it to break the loop instead.
 * When loop ends, currentNode is always null. Then pop the top elem on the stack, vist it and then
 * point currentNode to its right child.
 * Next loop if the right child is not null, we have the most left diving again. Otherwise, we just
 * visited a node without right child. currentNode is equal to nullptr. Then we simply pop from the
 * stack again to retrieve its parent node, visit it and move on.
 */
template<typename T>
vector<T> InOrderBinaryTreeTraversalIterative(const TreeNode<T>* node)
{
    assert(nullptr != node);
    vector<T> vec;
    stack<const TreeNode<T>*> stk;
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
/*
 * Iterative PostOrder Traversal: The trickest one among three.
 * Why so? you can only pop the top elem on the stack if both its left and right child
 * have been visited or the top elem is a leaf node.
 * An extra variable lastNode is introduced to track the last visited node and we only
 * assign the last node to it after we pop the stack, set the currentNode to nullptr, which
 * will not trigger left-most-diving and directly pop the parent from the stack.
 */
template<typename T>
vector<T> PostOrderBinaryTreeTraversalIterative(const TreeNode<T>* node)
{
    assert(nullptr != node);
    vector<T> vec;
    stack<const TreeNode<T>*> stk;
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
	    //the lastNode we visited is not the right child of currentNode.
	    //So, we can't visit currentNode since this is post-order.
	    //Switch to its right node and
	    //clean up lastNode with nullptr. This step is necessary in order for
	    //leaf node to be properly visited.
	    //Considering D (C, E) section in the test case. When we reach C
	    //if we allow lastNode to be currentNode, its value is C as well
	    //then we move currentNode to C's right node, which is nullptr
	    //Next loop, currentNode will be reassigned to C and since C's right child
	    //is null. however the lastNode was assigned to C, C will ever be visted.
	    //We fall into an infinite loop.
	    //So assign lastNode to nullptr since it will never be the right child in this branch
	    lastNode = nullptr;
	    currentNode = currentNode->Right();
	}
    }
    return vec;
}
/*
 * LevelOrder, aka Breadth First, bfs
 * queue instead of stack
 */
template<typename T>
vector<T> LevelOrderBinaryTreeTraversalIterative(const TreeNode<T>* node)
{
    assert(nullptr != node);
    vector<T> vec;
    queue<const TreeNode<T>*> que;
    que.push(node);
    while(false == que.empty())
    {
	vec.push_back(que.front()->GetValue());
	if(nullptr != que.front()->Left())
	    que.push(que.front()->Left());
	if(nullptr != que.front()->Right())
	    que.push(que.front()->Right());
	que.pop();	
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
    vec = LevelOrderBinaryTreeTraversalIterative<char>(&f);
    cout << "Expect 'F,B,G,A,D,I,C,E,H,': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;
    //single node
    vec = PreOrderBinaryTreeTraversalIterative<char>(&a);
    cout << "Expect 'A,': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = InOrderBinaryTreeTraversalIterative<char>(&a);
    cout << "Expect 'A,': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = PostOrderBinaryTreeTraversalIterative<char>(&a);
    cout << "Expect 'A,': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = LevelOrderBinaryTreeTraversalIterative<char>(&a);
    cout << "Expect 'A,': ";
    for (char c : vec)
 	cout << c << ',';
    cout << endl;

    //left nodes only, a list
    TreeNode<char> la('A', nullptr, nullptr);
    TreeNode<char> lc('C', &la, nullptr);
    TreeNode<char> le('E', &lc, nullptr);
    TreeNode<char> lh('H', &le, nullptr);
    TreeNode<char> ld('D', &lh, nullptr);
    TreeNode<char> lb('B', &ld, nullptr);
    TreeNode<char> li('I', &lb, nullptr);
    TreeNode<char> lg('G', &li, nullptr);
    TreeNode<char> lf('F', &lg, nullptr);
    vec = PreOrderBinaryTreeTraversalIterative<char>(&lf);
    cout << "Expect 'F,G,I,B,D,H,E,C,A': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = InOrderBinaryTreeTraversalIterative<char>(&lf);
    cout << "Expect 'A,C,E,H,D,B,I,G,F': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = PostOrderBinaryTreeTraversalIterative<char>(&lf);
    cout << "Expect 'A,C,E,H,D,B,I,G,F': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = LevelOrderBinaryTreeTraversalIterative<char>(&lf);
    cout << "Expect 'F,G,I,B,D,H,E,C,A': ";
    for (char c : vec)
 	cout << c << ',';
    cout << endl;
    
    //all right, a list
    TreeNode<char> ra('A', nullptr, nullptr);
    TreeNode<char> rc('C', nullptr, &ra);
    TreeNode<char> re('E', nullptr, &rc);
    TreeNode<char> rh('H', nullptr, &re);
    TreeNode<char> rd('D', nullptr, &rh);
    TreeNode<char> rb('B', nullptr, &rd);
    TreeNode<char> ri('I', nullptr, &rb);
    TreeNode<char> rg('G', nullptr, &ri);
    TreeNode<char> rf('F', nullptr, &rg);
    vec = PreOrderBinaryTreeTraversalIterative<char>(&rf);
    cout << "Expect 'F,G,I,B,D,H,E,C,A': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = InOrderBinaryTreeTraversalIterative<char>(&rf);
    cout << "Expect 'F,G,I,B,D,H,E,C,A': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = PostOrderBinaryTreeTraversalIterative<char>(&rf);
    cout << "Expect 'A,C,E,H,D,B,I,G,F': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;

    vec = LevelOrderBinaryTreeTraversalIterative<char>(&rf);
    cout << "Expect 'F,G,I,B,D,H,E,C,A': ";
    for (char c : vec)
	cout << c << ',';
    cout << endl;
}
