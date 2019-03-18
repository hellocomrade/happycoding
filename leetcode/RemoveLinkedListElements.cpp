//https://leetcode.com/problems/remove-linked-list-elements
/*
203. Remove Linked List Elements

Remove all elements from a linked list of integers that have value val.

Example:

Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5
*/
namespace RemoveLinkedListElements {
	/**
	* Definition for singly-linked list.
	**/
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};

	class Solution {
	public:
		//Construct new list
		ListNode* removeElements(ListNode* head, int val) {
			ListNode dummyHead(-1), *ptr = &dummyHead, *t = nullptr;
			while (nullptr != head) {
				t = head->next;
				if (val != head->val) ptr->next = head, ptr = ptr->next, ptr->next = nullptr;
				head = t;
			}
			return dummyHead.next;
		}
		//In place
		ListNode* removeElements1(ListNode* head, int val) {
			ListNode dummyHead(-1), *ptr = head, *prev_ptr = &dummyHead;
			dummyHead.next = head;
			while (nullptr != ptr) {
				if (val == ptr->val) prev_ptr->next = ptr->next;
				else prev_ptr = ptr;
				ptr = ptr->next;
			}
			return dummyHead.next;
		}
	};
}
/*
Test cases:

[1,2,6,3,4,5,6]
6
[]
1
[1,1,1]
1
[1,2,3,4,1]
1
[1,2,3]
4

Outputs:

[1,2,3,4,5]
[]
[]
[2,3,4]
[1,2,3]
*/