#include "list.h"
#include <cassert>
#include <iostream>

using namespace std;
/*
Implement an algorithm to delete a node in the middle of a singly linked list, given
only access to that node.

Observation:
Since head of the list is unknown, we can only access the remaining list from the node that is going to
be removed. On the other hand, in order to keep the integrity of the list, we can't simply remove
the node since the connection between the previous node to the current node will be broken.
We could though, remove the current node's next, and overwrite current node's data and next pointer with
current node's next's values. And then, we can safely remove the current node's next node.
*/
template<typename T>
void removeGivenNode(ListNode<T> *node)
{
	assert(nullptr != node && nullptr != node->next);
	ListNode<T> *ptr = node->next;
	node->data = ptr->data;
	node->next = ptr->next;
	delete ptr;
}
template<typename T>
void PrintList(ListNode<T> *phead)
{
	while (phead != nullptr)
	{
		cout << phead->data << " -> ";
		phead = phead->next;
	}
	cout << endl;
}
void testRemoveGivenNode()
{
	ListNode<int> *plist = nullptr;
	int arr1[] = { 2, 2, 3, 5, 5, 7 };
	plist = BuildListFromArray(arr1, sizeof(arr1) / sizeof(arr1[0]));
	int n = 3;
	ListNode<int> *pnode = plist;
	while (n-- > 0 && pnode != nullptr)
		pnode = pnode->next;
	if (pnode != nullptr)
	{
		cout << "Before remove " << pnode->data << " from ";
		PrintList(plist);
		removeGivenNode(pnode);
		cout << "After: ";
		PrintList(plist);
	}

	cout << "Before remove " << plist->data << " from ";
	PrintList(plist);
	removeGivenNode(plist);
	cout << "After: ";
	PrintList(plist);

	CleanupList(plist);
}