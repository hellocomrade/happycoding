#include "list.h"
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

/*
Given two singly-listed lists (no circle), check if they are merged at a node
*/
template<typename T>
ListNode<T>* mergedList(ListNode<T> *h1, ListNode<T> *h2)
{
	assert(nullptr != h1 && nullptr != h2);
	int len1 = 0, len2 = 0;
	ListNode<T> *lptr1 = h1, *lptr2;
	while (nullptr != lptr1)
	{
		len1++;
		lptr1 = lptr1->next;
	}
	lptr1 = h2;
	while (nullptr != lptr1)
	{
		len2++;
		lptr1 = lptr1->next;
	}
	lptr1 = (len1 >= len2) ? h1 : h2;
	lptr2 = (lptr1 == h1) ? h2 : h1;
	len2 = std::abs(len1 - len2);
	while (len2-- > 0)
		lptr1 = lptr1->next;
	while (nullptr != lptr1)
	{
		if (lptr1 == lptr2)
			return lptr1;
		lptr1 = lptr1->next;
		lptr2 = lptr2->next;
	}
	return nullptr;
}
void testMergedList()
{
	ListNode<int> head1(1);
	ListNode<int> n2(2);
	head1.next = &n2;
	ListNode<int> n3(3);
	n2.next = &n3;
	ListNode<int> n4(4);
	n3.next = &n4;
	ListNode<int> n5(5);

	ListNode<int> head2(6);
	ListNode<int> n27(7);
	head2.next = &n27;
	n27.next = &n4;

	ListNode<int> *pl = mergedList(&head1, &head2);
	cout << "Expect 4: " << pl->data << endl;

	n27.next = nullptr;
	pl = mergedList(&head1, &head2);
	cout << "Expect 1: " << (pl == nullptr) << endl;
}