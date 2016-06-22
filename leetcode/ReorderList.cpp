#include <stack>
//https://leetcode.com/problems/reorder-list/
/*
143. Reorder List

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

Observations:
You could use a stack to store the second half of the list. But this will take O(N) space.

If it asks for O(1) space, we should reverse the second half of the list and then merge the first half
and the reversed second half together.
*/
namespace SolutionReorderList{
	struct ListNode{
		struct ListNode *next;
		int val;
	};
	class SolutionReorderList{
	public:
		//Using a stack
		void reorderList1(ListNode* head) {
			if (head) {
				ListNode *fast = head, *slow = head, *prev = head;
				//from the following loop, the second half is no shorter than the first half
				while (fast != nullptr && fast->next != nullptr) {
					prev = slow;
					slow = slow->next;
					fast = fast->next->next;
				}
				if (slow == prev)return;
				prev->next = nullptr;
				std::stack<ListNode*> stk;
				while (slow) {
					stk.push(slow);
					slow = slow->next;
					stk.top()->next = nullptr;
				}
				slow = head;
				while (stk.empty() == false) {
					fast = slow->next;
					slow->next = stk.top();
					stk.pop();
					if (fast) {
						slow->next->next = fast;
						slow = fast;
					}
					else
						slow = slow->next;
				}
			}
		}
		//reverse the second half, second half is no shorter than the first half
		void reorderList2(ListNode* head) {
			if (head) {
				ListNode *fast = head, *slow = head, *prev = head;
				while (fast != nullptr && fast->next != nullptr) {
					prev = slow;
					slow = slow->next;
					fast = fast->next->next;
				}
				if (slow == prev)return;
				prev->next = fast = nullptr;
				prev = slow;
				while (slow->next) {
					fast = slow->next;
					slow->next = fast->next;
					fast->next = prev;
					prev = fast;
				}
				slow = head, fast = prev;
				//first half: slow will run out first
				while (slow) {
					prev = slow->next;
					slow->next = fast;
					fast = fast->next;
					//condition is for handling the last element on the first half
					//when we reach it, we hook it up with the remaining of the second half then loop exits
					slow->next->next = prev == nullptr ? fast : prev;
					slow = prev;
				}
			}
		}
		//reverse the second half, second half is no longer than the first half
		void reorderList3(ListNode* head) {
			if (head) {
				ListNode *fast = head, *slow = head, *prev = head;
				while (fast != nullptr) {
					prev = slow;
					slow = slow->next;
					fast = fast->next != nullptr ? fast->next->next : nullptr;
				}
				if (slow == nullptr)return;
				prev->next = fast = nullptr;
				prev = slow;
				while (slow->next) {
					fast = slow->next;
					slow->next = fast->next;
					fast->next = prev;
					prev = fast;
				}
				slow = head, fast = prev;
				//second half: fast will run out first
				while (fast) {
					prev = slow->next;
					slow->next = fast;
					fast = fast->next;
					slow->next->next = prev;
					slow = prev;
				}
			}
		}
		void reorderList(struct ListNode* head) {
			if (head)
			{
				struct ListNode* slow = head;
				struct ListNode* fast = head;
				struct ListNode* tmp = head;
				while (fast)
				{
					tmp = slow;
					slow = slow->next;
					if (fast->next)
						fast = fast->next->next;
					else
						break;
				}
				if (!slow)return;
				//printf("%d\n", slow->val);
				tmp->next = nullptr;
				tmp = nullptr;
				fast = slow;
				while (slow->next)
				{
					tmp = fast;
					fast = slow->next;
					slow->next = slow->next->next;
					fast->next = tmp;
				}
				//printf("%d\n", fast->val);
				slow = head;
				while (fast && slow)
				{
					tmp = slow->next;
					slow->next = fast;
					fast = fast->next;
					slow->next->next = tmp;
					slow = tmp;
				}
			}
		}
	};
}
void TestReorderList()
{
	SolutionReorderList::ListNode l7{ nullptr, 7 };
	SolutionReorderList::ListNode l6{ &l7, 6 };
	SolutionReorderList::ListNode l5{ &l6, 5 };
	SolutionReorderList::ListNode l4{ &l5, 4 };
	SolutionReorderList::ListNode l3{ &l4, 3 };
	SolutionReorderList::ListNode l2{ &l3, 2 };
	SolutionReorderList::ListNode l1{ &l2, 1 };
	SolutionReorderList::SolutionReorderList so;
	so.reorderList(&l1);
}