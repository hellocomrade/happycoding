//https://leetcode.com/problems/swap-nodes-in-pairs/
/*
24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.

Observations:
Statement says not allowing swapping values, that means swapping nodes only.

Spent most of time on "competing" with a guy who completed this in 8 lines of C++ code using pointer to pointer.
I use a dummy header node...try to simplify my code, down to 9 lines...
*/
namespace SwapNodesInPairs {
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
		ListNode* swapPairs1(ListNode* head) {
			//tmp is not necessary
			ListNode dummy = ListNode(0), *cur = &dummy, *tmp = nullptr;
			while (nullptr != head) {
				cur->next = head->next;
				if (nullptr == cur->next)cur->next = head;
				else {
					tmp = cur->next->next;
					cur->next->next = head;
					head->next = tmp;
					cur = head;
				}
				head = head->next;
			}
			return dummy.next;
		}
		ListNode* swapPairs2(ListNode* head) {
			ListNode dummy = ListNode(0), *cur = &dummy;
			while (nullptr != head) {
				cur->next = head->next;
				//check on nullptr == cur->next is only necessary for the list with only one node
				if (nullptr == cur->next)cur->next = head;
				else {
					head->next = cur->next->next;
					cur->next->next = head;
					cur = head;
				}
				head = head->next;
			}
			return dummy.next;
		}
		ListNode* swapPairs3(ListNode* head) {
			ListNode dummy = ListNode(0), *cur = &dummy;
			while (nullptr != head && nullptr != head->next) {
				cur->next = head->next;
				head->next = cur->next->next;
				cur->next->next = head;
				cur = head;
				head = head->next;
			}
			return nullptr == dummy.next ? head : dummy.next;
		}
		/*
		Using pointer to pointer to simplify reconnecting swapped node pairs by referencing it to 
		the previous second node's next varaible that could otherwise be done by tracking the previous second node
		directly. Nice trick!
		*/
		ListNode* swapPairs(ListNode* head) {
			ListNode **phead = &head, *pn1, *pn2;
			while (nullptr != (pn1 = *phead) && nullptr != (pn2 = pn1->next)) {
				pn1->next = pn2->next;
				pn2->next = pn1;
				*phead = pn2;
				phead = &(pn1->next);
			}
			return head;
		}
	};
}
