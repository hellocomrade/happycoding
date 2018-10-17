//https://leetcode.com/problems/partition-list/
/*
86. Partition List

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Example:

Input: head = 1->4->3->2->5->2, x = 3

Output: 1->2->2->4->3->5

Observations:

Manipulate a list using two dummy headers and one pointer, scan list only once then attach
nodes to either dummy header based upon the comparison with x, break these nodes links with original
list by assigning nullptr to their next.

Edge cases are: all nodes' values are less than x or all of them are no less than x, which cause one of
the two dummy headers has nothing.
*/
namespace PartitionList {
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
		ListNode* partition(ListNode* head, int x) {
			ListNode dummy1(0), dummy2(0), *pd1 = &dummy1, *pd2 = &dummy2, *pnode = head;
			while (nullptr != pnode) {
				if (pnode->val < x) pd1->next = pnode, pd1 = pd1->next;
				else pd2->next = pnode, pd2 = pd2->next;
				pnode = pnode->next;
				pd1->next = pd2->next = nullptr;
			}
			if (nullptr != dummy1.next) pd1->next = dummy2.next;
			else dummy1.next = dummy2.next;
			return nullptr == head ? nullptr : dummy1.next;
		}
	};
}
/*
Test cases:

[1,4,3,2,5,2]
3
[]
10
[1]
2
[1]
0
[5,4,3,3,2,1]
3
[5,4,3,3,2,1]
4
[5,4,3,3,2,1]
5
[5,4,3,2,1]
0
[5,4,3,2,1]
10

Outputs:

[1,2,2,4,3,5]
[]
[1]
[1]
[2,1,5,4,3,3]
[3,3,2,1,5,4]
[4,3,3,2,1,5]
[5,4,3,2,1]
[5,4,3,2,1]
*/