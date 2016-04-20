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
1. If there is no leading elements, simply a circle, the slower and faster pointers always meet at the
   starting point of the loop (the head of this list in this case).
2. Once the slower pointer is on the starting pointer of the loop, it never takes more than a circle for
   the faster pointer to catch up.
3. When slower and faster pointers meet at pos that is k to the starting point of the loop. If we move
   one pointer back to the head of the list and let both pointers running at 1 pace per step, they will
   eventually meet at the starting point of the loop.

Prove: 
Assuming there are m leading elements before the starting point of the loop, the loop itself has N elements.
When the slow pointer reaches the starting point of the loop after k moves, the faster pointer has moved
2k steps, therefore, it's k step inside the loop. 

Let's assume the starting point of the loop with index 1, N=6

1 -> 2 -> 3 -> 4 ->5 ->6 ->1

Say when slower pointer reaches 1 (at the head of the list above), faster one is at 3. If we start to track
on both pointers:

Slower one: 1 -> 2 -> 3 -> 4 -> [5] -> 6 -> 1
Faster one: 3 -> 5 -> 1 -> 3 -> [5] -> 1 -> 3

Whenever you see they have the same index at a particular step, they meet! For our case, they will meet at index
5.

Let's examine it from a slightly different aspect:

Slower one (1 per step): 1 -> 2 -> 3 -> 4 -> [5] -> 6 -> 1
Faster one (2 per step): 3 -> 5 -> 7 -> 9 -> [11] -> 13 -> 15
								   7%6  9%6   11%6   13%6  15%6
								    1   3     5
For faster pointer, if the continuous counting number is greater than the number of loop (6, in this case). We will
do modulo against 6. We will still get 1, 3 ,5, which are as same as the index since the index starting from 1 at the
beginning of the loop.

By having the above observation, we could get the following expression:

(k + 2*x) % N = x

x is the number of moves the slower pointer made after it reaches the starting point of the loop. During the same period,
the faster pointer will move 2*x steps. Given k as the initial index (base count), the current count when they meet will be:

(k + 2*x)

Since we have known that the slower one never makes more than a circle for faster one to catch up (O. 2), we will have:

(k + 2*x) % N = x

Given C as a constant, we could have:

(k + 2*x) = C*N + x --> x = C*N - k

Since both x  and k is no greater than N, C is no greater than 2. C is equal to 2 if and only if k is equal to N.

So we could safely simplify the above to: x = N - k

Now, we have proved that when two pointers meet first time on the loop, they are N - (N - k) = k away from the starting point
of the loop.
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
