//https://www.lintcode.com/problem/plus-one-linked-list
/*
369. Plus One Linked List

Description
Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

Example

Given head = 1 -> 2 -> 3 -> null, return 1 -> 2 -> 4 -> null.

Observations:

This problem is under subscription on leetcode. Fortunately, lintcode offers it for free.
It's a variation of leetcode 66 (Plus One). However, linked list doesn't allow random access. Therefore, using a stack
to store previous visited node is the option, which requires extra O(N) space.

In fact, one can solve this problem with O(N) time and O(1) space by assigning the next pointer on each node to its previous node
temporarily during the first loop. Then, plus one at the leaf node, loop backward and resume the next pointer.

- A dummy head is created for the case like 9->9>null, a new head is needed: 1->0->0->null

- My first submittal failed the following case due to careless handing on carry. After the plus on operation on a node,
carry is retained if and only if (1 == carry && 0 == pnode->val)

1->0->0->0->0->null
*/
namespace PlusOneLinkedList {
	/**
	* Definition of singly-linked-list:
	*/
	class ListNode {
	public:
		int val;
		ListNode *next;
		ListNode(int val) {
			this->val = val;
			this->next = nullptr;
		}
	};

	class Solution {
	public:
		/**
		* @param head: the first Node
		* @return: the answer after plus one
		*/
		ListNode * plusOne(ListNode * head) {
			int carry = 1;
			ListNode *dummyHead = new ListNode(0), *pnode = dummyHead, *prev = nullptr, *pnext = nullptr;
			dummyHead->next = head;
			while (nullptr != pnode) {
				pnext = pnode->next;
				pnode->next = prev;
				prev = pnode;
				pnode = pnext;
			}
			pnode = prev, prev = nullptr;
			while (nullptr != pnode) {
				pnode->val = (carry + pnode->val) % 10;
				carry = (1 == carry && 0 == pnode->val) ? 1 : 0;
				pnext = pnode->next;
				pnode->next = prev;
				prev = pnode;
				pnode = pnext;
			}
			return 1 == dummyHead->val ? dummyHead : dummyHead->next;
		}
	};
}
