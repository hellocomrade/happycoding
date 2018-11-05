//https://leetcode.com/problems/reverse-linked-list-ii/
/*
92. Reverse Linked List II

Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4

Output: 1->4->3->2->5->NULL

Observations:

Reverse Linked List is leetcde 206, Reverse Linked List II, however is leetcode 92...Is that funny?
Anyway, one could apply the offical solution for leetcde 206 on this one. After the sublist is reversed,
extra step must be taken to hook it up with the remaining list.

reverseBetween and reverseBetween0 though, both use the trick of dummy header, which takes the list on its
next pointer. This dummy is necessary since a different algorithm is used here: instead of reversing next pointer
on each node, every node between [m, n] will be re-positioned at the beginning of this reversed sublist and its next
pointer is hooked up with the previous sublist's head. This "beginning" of reversed sublist is stored in the next pointer
of node[m - 1]. Therefore, node[m - 1] must be retrieved first. Furthermore, this algorithm still requires linking reversed
tail with node[n + 1].

This dummy header is a typical setup for the edge case that the operation, say reversing, applies
on the first node of the list. In this case, node[m - 1] is not available, a dummy head could take this role.
*/
namespace ReverseLinkedList2 {
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
		ListNode* reverseBetween(ListNode* head, int m, int n) {
			ListNode dummyHead(0), *pnode = &dummyHead, *phead = pnode, *revtail = nullptr;
			dummyHead.next = head;
			while (m-- > 0) --n, phead = pnode, pnode = revtail = pnode->next;
			pnode = pnode->next;
			while (n-- > 0) {
				revtail->next = pnode->next;
				pnode->next = phead->next;
				phead->next = pnode;
				pnode = revtail->next;
			}
			return dummyHead.next;
		}
		ListNode* reverseBetween0(ListNode* head, int m, int n) {
			ListNode *pnode = head, dummyHead(0), *revhead = &dummyHead, *revtail = nullptr, *t = nullptr;
			dummyHead.next = head;
			while (--m > 0) --n, revhead = pnode, pnode = pnode->next;
			revtail = pnode;
			while (n-- > 0) {
				t = pnode->next;
				pnode->next = revhead->next;
				revhead->next = pnode;
				pnode = t;
			}
			if (nullptr != revtail) revtail->next = pnode;
			return dummyHead.next;
		}
	};
}
/*
Test cases:

[1]
1
1
[1,2]
1
1
[1,2]
2
2
[1,2]
1
2
[1,2,3]
1
1
[1,2,3]
2
2
[1,2,3]
3
3
[1,2,3]
1
3
[1,2,3]
1
2
[1,2,3]
2
3
[1,2,3,4]
1
1
[1,2,3,4]
1
2
[1,2,3,4]
1
3
[1,2,3,4]
1
4
[1,2,3,4]
2
2
[1,2,3,4]
2
3
[1,2,3,4]
2
4
[1,2,3,4]
3
3
[1,2,3,4]
3
4
[1,2,3,4]
4
4

Outputs:

[1]
[1,2]
[1,2]
[2,1]
[1,2,3]
[1,2,3]
[1,2,3]
[3,2,1]
[2,1,3]
[1,3,2]
[1,2,3,4]
[2,1,3,4]
[3,2,1,4]
[4,3,2,1]
[1,2,3,4]
[1,3,2,4]
[1,4,3,2]
[1,2,3,4]
[1,2,4,3]
[1,2,3,4]
*/