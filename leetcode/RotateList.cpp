//https://leetcode.com/problems/rotate-list/
/*
61. Rotate List

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

Observations:
It appears that you have to know the size of the list anyway for a simple reason:

k could be greater than the size of the list, so you have to do modulus (k % size).

You can do this either throught recursion or iteration. Iteration is faster and doesn't require
extra space.
*/
namespace RotateList {
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};
	class Solution {
	private:
		//for recursion version only
		int aux(ListNode *node, int k, ListNode *head, ListNode **newhead, int &size) {
			if (node != nullptr) ++size;
			if (node->next == nullptr)return 1;
			int cnt = aux(node->next, k, head, newhead, size) + 1;
			if (cnt == k % size + 1)
			{
				if (node->next != nullptr)
				{
					*newhead = node->next;
					ListNode *itor = node;
					while (itor->next != nullptr)itor = itor->next;
					itor->next = head;
					node->next = nullptr;
				}
			}
			return cnt;
		}
	public:
		ListNode *rotateRight1(ListNode *head, int k) {
			ListNode *newhead = head;
			if (head != nullptr)
			{
				int len = 0;
				this->aux(head, k, head, &newhead, len);
			}
			return newhead;
		}
		ListNode* rotateRight(ListNode* head, int k) {
			ListNode *newhead = head, *itor = head, *tail;
			if (head)
			{
				int size = 0;
				while (itor != nullptr)
				{
					tail = itor;
					itor = itor->next;
					++size;
				}
				k = k % size;
				int cnt = 0;
				itor = head;
				while (++cnt < size - k)
					itor = itor->next;
				if (nullptr != itor)
				{
					tail->next = head;
					newhead = itor->next;
					itor->next = nullptr;
				}
			}
			return newhead;
		}
	};
}
