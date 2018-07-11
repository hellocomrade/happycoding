//https://leetcode.com/problems/palindrome-linked-list
/*
234. Palindrome Linked List

Given a singly linked list, determine if it is a palindrome.

Example 1:

Input: 1->2

Output: false

Example 2:

Input: 1->2->2->1

Output: true

Follow up:

Could you do it in O(n) time and O(1) space?

Observations:

First of all, since we have to know where the mid point of the linked list is, Tortoise Hare algorithm is necessary.

Furhtermore, if O(1) space, we can't use Stack. Then, the only option would be: reverse the first half of the linked list. So,
when tortoise stops at the middle, we can immediately compare two halfs of linked list, one pointer goes from middle to the end,
the other pointer goes from middle to the old beginning of the linkedlist since the first half of linked list has been reversed in terms of
next pointer connection.

Of course, we have to consider the odd/even number of nodes here as well.

If the linked list is a palindrome, every comparsion on val shall returns true and after the loop exits, two pointers shall both be
nullptr.
*/
namespace PalindromeLinkedList {
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
		bool isPalindrome(ListNode* head) {
			ListNode dummyHead(0), *fast = head, *slow = head, *t = nullptr;
			while (nullptr != fast && nullptr != fast->next) {
				fast = fast->next->next;
				t = dummyHead.next;
				dummyHead.next = slow;
				slow = slow->next;
				dummyHead.next->next = t;
			}
			fast = nullptr == fast ? slow : slow->next;
			slow = dummyHead.next;
			while (nullptr != fast && nullptr != slow) {
				if (fast->val != slow->val) return false;
				fast = fast->next;
				slow = slow->next;
			}
			return nullptr == fast && nullptr == slow;
		}
	};
}