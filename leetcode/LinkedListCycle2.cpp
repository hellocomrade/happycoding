#include <cassert>

//https://leetcode.com/problems/linked-list-cycle-ii/
/*
142. Linked List Cycle II

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?

Obserations:
I know this trick long time ago but never knew this algorithm's origin and its name. Here you go:

Floyd's Tortoise and Hare, a 2-stage cycle detection algorithm.

https://leetcode.com/problems/linked-list-cycle-ii/solution/

With prove as well.

https://en.wikipedia.org/wiki/Cycle_detection
*/
namespace LinkedListCycle2 {
	/*
	Definition for singly-linked list.
	*/
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};

	class Solution {
	public:
		ListNode *detectCycle(ListNode *head) {
			if (nullptr == head)return nullptr;
			ListNode *slow = head, *fast = head;
			do {
				slow = slow->next;
				fast = fast->next;
				if (nullptr != fast)fast = fast->next;
			} while (nullptr != fast && slow != fast);
			if (nullptr == fast)return nullptr;
			fast = head;
			while (fast != slow) {
				fast = fast->next;
				slow = slow->next;
			}
			return fast;
		}
	};
}
void TestLinkedListCycle2() {
	LinkedListCycle2::Solution so;
	using ListNode = LinkedListCycle2::ListNode;
	ListNode ln1(1);
	ListNode ln2(2);
	ListNode ln3(3);
	ListNode ln4(4);
	ListNode ln5(5);
	ln1.next = &ln2, ln2.next = &ln3, ln3.next = &ln4, ln4.next = &ln5, ln5.next = &ln3;
	assert(&ln3 == so.detectCycle(&ln1));
	ln5.next = nullptr;
	assert(nullptr == so.detectCycle(&ln1));
	ln5.next = &ln1;
	assert(&ln1 == so.detectCycle(&ln1));
	ln2.next = nullptr;
	assert(nullptr == so.detectCycle(&ln1));
	ln1.next = nullptr;
	assert(nullptr == so.detectCycle(&ln1));
}