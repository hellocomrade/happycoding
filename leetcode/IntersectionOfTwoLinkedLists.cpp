#include <cassert>

//https://leetcode.com/problems/intersection-of-two-linked-lists/
/*
160. Intersection of Two Linked Lists

Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:     a1 → a2
		      ↘
				c1 → c2 → c3
			  ↗
B: b1 → b2 → b3

begin to intersect at node c1.


Notes:

- If the two linked lists have no intersection at all, return null.
- The linked lists must retain their original structure after the function returns.
- You may assume there are no cycles anywhere in the entire linked structure.
- Your code should preferably run in O(n) time and use only O(1) memory.

Observations:

https://leetcode.com/problems/intersection-of-two-linked-lists/solution/

I didn't figure out the trick...

The trick is: if one pointer reaches the end of the list, we move it to the head of the other list. Then two pointers will guarantee to
meet at intersection point eventually if itersection exists or they would end up both reaching NULL.

Note: it's possible both pointers may switch to the other list more than one time. Say [1, 2, 3], [1,2,3,4]

That has been said, I am not sure if this is a linear algorithm, as solution claimed O(m + n)... what is the upper boudary for the loop?
How many times does the pointer have to switch? Is the case I mentioned the worst one? Is there any case that requires a pointer switches more than twice?
*/
namespace IntersectionOfTwoLinkedLists {
	/**
	* Definition for singly-linked list.
	*/
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};

	class Solution {
	public:
		ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
			ListNode *pa = headA, *pb = headB;
			while (pa != pb) {
				pa = (nullptr != pa) ? pa->next : headB;
				pb = (nullptr != pb) ? pb->next : headA;
			}
			return pa;
		}
		ListNode *getIntersectionNode1(ListNode *headA, ListNode *headB) {
			ListNode *pa = headA, *pb = headB, *ans = nullptr;
			while (nullptr != pa && nullptr != pb) {
				if (pa == pb) {
					ans = pa;
					break;
				}
				pa = pa->next;
				if (nullptr == pa) pa = headB, headB = nullptr;
				pb = pb->next;
				if (nullptr == pb) pb = headA, headA = nullptr;
			}
			return ans;
		}
	};
}
void TestIntersectionOfTwoLinkedLists() {
	namespace ITL = IntersectionOfTwoLinkedLists;
	ITL::ListNode a1(1);
	ITL::ListNode a2(2);
	ITL::ListNode b1(3);
	ITL::ListNode b2(4);
	ITL::ListNode b3(5);
	ITL::ListNode c1(6);
	ITL::ListNode c2(7);
	ITL::ListNode c3(8);

	a1.next = &a2;
	a2.next = &c1;
	c1.next = &c2;
	c2.next = &c3;
	b1.next = &b2;
	b2.next = &c1;

	ITL::Solution so;
	assert(&c1 == so.getIntersectionNode(&a1, &b1));
}