#include <cassert>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

/*
Write a program to sort a stack in ascending order (with biggest items on top).
You may use at most one additional stack to hold items, but you may not copy the
elements into any other data structure (such as an array). The stack supports the
following operations: push, pop, peek, and isEmpty.

Please get sort done in place.
O(N^2)
*/
template<typename T>
void sortStack(stack<T> &S)
{
	assert(false == S.empty());
	stack<T> utilStk;
	T t;
	while (false == S.empty())
	{
		t = S.top();
		S.pop();
		while (false == utilStk.empty() && utilStk.top() < t)
		{
			S.push(utilStk.top());
			utilStk.pop();
		}
		utilStk.push(t);
	}
	while (false == utilStk.empty())
	{
		S.push(utilStk.top());
		utilStk.pop();
	}
}
void printSortedStack(stack<int> &S)
{
	while (false == S.empty())
	{
		cout << S.top() << ',';
		S.pop();
	}
	cout << endl;
}
void testSortStack()
{
	stack<int> stk1;
	stk1.push(4);
	stk1.push(3);
	stk1.push(2);
	stk1.push(1);
	sortStack(stk1);
	printSortedStack(stk1);

	stack<int> stk2;
	stk2.push(1);
	stk2.push(2);
	stk2.push(3);
	stk2.push(4);
	sortStack(stk2);
	printSortedStack(stk2);

	stack<int> stk3;
	stk3.push(6);
	stk3.push(2);
	stk3.push(3);
	stk3.push(2);
	stk3.push(7);
	stk3.push(9);
	sortStack(stk3);
	printSortedStack(stk3);

	stack<int> stk4;
	stk4.push(0);
	sortStack(stk4);
	printSortedStack(stk4);
}