/*
147. Insertion Sort List

Sort a linked list using insertion sort.

A graphical example of insertion sort. The partial sorted list (black) initially contains only the first element in the list.
With each iteration one element (red) is removed from the input data and inserted in-place into the sorted list

Algorithm of Insertion Sort:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there.
It repeats until no input elements remain.

Example 1:

Input: 4->2->1->3

Output: 1->2->3->4

Example 2:

Input: -1->5->3->4->0

Output: -1->0->3->4->5

Observations:

insertionSortList1 is the exact duplicate of insertion sort on linked list in terms of algorithm.
Since linked list doesn't support random access, one may have to point each nodes'next pointer to its
previous node in order to have the classic backward iteration as a qualified "Insertion Sort". After
sorting, the entir linked list is reversed. Therefore, it has to be recovered by reestablishing the
correct next pointers to nodes' next node.

The above algorithm doesn't perform very well comparing with others' solutions. After exhaust all tricks
in my pocket, I gave up and took a peek on other's solution: the faster algorithm is barely considered
as Insertion Sort by my opinion: it's not an in-place sorting algorithm anymore! It re-arrange the entire
linked list by maintaining a brand new list in sorted order. Then the next node will be compared with nodes on this new
list. Depending on its value, it could be "inserted" at beginning, in the middle or at the end of the new list.
See insertionSortList.

It's shorter, more elegant, all great but no Insertion Sort...
*/
namespace InsertionSortList {
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
		ListNode* insertionSortList(ListNode* head) {
			ListNode dummyHead(0);
			ListNode *pnext = nullptr, *ptr = nullptr, *prev = nullptr;
			while (nullptr != head) {
				pnext = head->next, prev = &dummyHead, ptr = dummyHead.next;
				while (nullptr != ptr && head->val >= ptr->val) prev = ptr, ptr = ptr->next;
				prev->next = head, head->next = ptr, head = pnext;
			}
			return dummyHead.next;
		}
		ListNode* insertionSortList1(ListNode* head) {
			if (nullptr == head) return head;
			ListNode* pnext = head->next, *prev = nullptr, *t = nullptr;
			do {
				head->next = t, t = head;
				while (nullptr != head->next && head->val < head->next->val) {
					std::swap(head->val, head->next->val);
					head = head->next;
				}
				head = pnext, pnext = (nullptr == pnext) ? nullptr : pnext->next;
			} while (nullptr != head);
			while (nullptr != t) {
				prev = t->next;
				t->next = head;
				head = t;
				t = prev;
			}
			return head;
		}
	};
}
/*
Test cases:

[4,2,1,3]
[-1,5,3,4,0]
[2,1,1,2]
[1,1,1]
[1,2,1]
[2,1,1]
[1,1,2]
[]
[1]
[1,2]
[2,1]

Outputs:

[1,2,3,4]
[-1,0,3,4,5]
[1,1,2,2]
[1,1,1]
[1,1,2]
[1,1,2]
[1,1,2]
[]
[1]
[1,2]
[1,2]
*/