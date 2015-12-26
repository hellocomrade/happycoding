#include "list.h"
#include <cassert>
#include <iostream>

using namespace std;

/*
Given a circular linked list, implement an algorithm which returns the node at the
beginning of the loop.

assuming circule may or may not exist
*/
/*
The following algorithm will find the meeting point on the loop first using the faster/slower pointer trick, 
then counting the number of elements actually inside the loop by freezing one pointer and let the other one
move onto the next element per step. Eventually two pointers will meet again and we can count the number k.
Next, we move both pointers back to the beginning of the list, now the question becomes:
returning the kth element from the list that satisfies the fact that the kth and (k+k)th elements are the same.
*/
template<typename T>
ListNode<T>* positionOfLoop1(ListNode<T> *phead)
{
	assert(nullptr != phead);
	ListNode<T> *slowPtr = phead;
	ListNode<T> *fastPtr = phead;
	int loopcnt = 0, i;
	do
	{
		slowPtr = slowPtr->next;
		if (nullptr != fastPtr->next)
			fastPtr = fastPtr->next->next;
		else
			fastPtr = nullptr;
	} while (nullptr != fastPtr && fastPtr != slowPtr);
	if (nullptr == fastPtr)
		return nullptr;
	else
	{
		do
		{
			loopcnt++;
			fastPtr = fastPtr->next;
		} while (fastPtr != slowPtr);
		i = loopcnt;
		slowPtr = fastPtr = phead;
		do
		{
			if (0 == i--)
			{
				slowPtr = fastPtr;
				i = loopcnt;
			}
			fastPtr = fastPtr->next;
		} while (slowPtr != fastPtr);
		return slowPtr;
	}
	return nullptr;
}
/*
Observation:
1. When slower and faster pointers meet at pos that is k to the starting point of the loop. If we move
   one pointer back to the head of the list and let both pointers running at 1 pace per step, they will
   eventually meet at the starting point of the loop.
2. If there is no leading elements, simply a circle, the slower and faster pointers always meet at the 
   starting point of the loop (the head of this list in this case).
3. Once the slower pointer is on the starting pointer of the loop, it never takes more than a circle for
   the faster pointer to catch up.
Prove: 
Assuming there are m leading elements before the starting point of the loop, the loop itself has N elements.
When the slow pointer reaches the starting point of the loop after k moves, the faster pointer has moved
2k steps, therefore, it's k step inside the loop. It's possible the faster pionter has been looping for a while,
so the actually relative position from the starting of the loop is k%N. We simplify it as K coze we only care
the relative distance from this moment.

Well, they are in a loop, we have to define this way: the faster pointer is N-K steps behild the slower pointer.
When they meet in the loop, let's say the slower one has moved x steps, then the faster one has moved 2x steps.
Actually if we consider this from a different angle, faster pointer moved N-K steps first to get to the starting
point of the loop, then x steps to catch up the slower one. So N-K is actually equal to x.

Therefore, the they will meet N-K steps after the starting point and they are K step away from looping back to the 
starting point.
*/
template<typename T>
ListNode<T>* positionOfLoop(ListNode<T> *phead)
{
	assert(nullptr != phead);
	ListNode<T> *slowPtr = phead;
	ListNode<T> *fastPtr = phead;
	while (nullptr != fastPtr && nullptr != fastPtr->next)
	{
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
		if (fastPtr == slowPtr)
			break;
	}
	if (nullptr == fastPtr || nullptr == fastPtr->next)
		return nullptr;
	else
	{
		slowPtr = phead;
		while (slowPtr != fastPtr)
		{
			fastPtr = fastPtr->next;
			slowPtr = slowPtr->next;
		}
		return slowPtr;
	}
	return nullptr;
}
void testPositionOfLoop()
{
	ListNode<int> head(1);
	ListNode<int> n1(2);
	head.next = &n1;
	ListNode<int> n2(2);
	n1.next = &n2;
	ListNode<int> n3(3);
	n2.next = &n3;
	ListNode<int> n4(4);
	n3.next = &n4;
	ListNode<int> n5(5);
	n4.next = &n5;
	n5.next = &n3;
	cout << "Expect 3: " << positionOfLoop(&head)->data << endl;
}