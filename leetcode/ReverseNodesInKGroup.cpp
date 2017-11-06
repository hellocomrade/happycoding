#include <vector>

using namespace std;

//https://leetcode.com/problems/reverse-nodes-in-k-group/
/*
25. Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

Observations:
At first try, I didn't see the statement "Only constant memory is allowed". I had a reverseKGroup1 with an array with size k...

Then, when I read the statement, I realize that a constant space reverse on list node was done before by me! How come I let it slip...

Anyway, with this reverse function using constant space, we simply reverse every k nodes on the original list. I did spend some time to
make the code shorter coz some one in the discussion area claims a short C++ implmentation, which is not true even that impl only uses one funcation call
which should be shorter comparing with mine.

A pitfall of this question is: k is supposed to be positive and up to the length of the list. But, the following test case is given:

[1]
2

which is not legal actually.
*/
namespace ReverseNodesInKGroup {
	/**
	* Definition for singly-linked list.
	*/
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};

	class Solution {
	private:
		ListNode* aux(const vector<ListNode*> &vec, ListNode* root) {
			int sz = vec.size();
			vec[0]->next = vec[sz - 1]->next;
			for (int i = sz - 1; i > 0; --i) {
				vec[i]->next = vec[i - 1];
				root->next = vec[i];
				root = root->next;
			}
			return vec[0];
		}
		ListNode* reverse(ListNode *start, ListNode *end) {
			if (nullptr == start)return nullptr;
			ListNode *newstart = start, *p = nullptr, *tail = start;
			while (end != (p = tail->next)) {
				tail->next = p->next;
				p->next = newstart;
				newstart = p;
			}
			return newstart;
		}
	public:
		/*
		Using dummy node head so we can make the code shorter coz tail->next is always available.
		*/
		ListNode* reverseKGroup(ListNode* head, int k) {
			ListNode *cur = head, *h1 = head, *t = nullptr, ans = ListNode(0), *tail = &ans;
			int c = 0;
			while (nullptr != cur) {
				if (k == ++c) {
					t = cur->next;
					tail->next = this->reverse(h1, t);
					tail = h1, h1 = cur = t, c = 0;
				}
				else cur = cur->next;
			}
			return nullptr == ans.next ? head : ans.next;
		}
		ListNode* reverseKGroup1(ListNode* head, int k) {
			if (1 == k)return head;
			ListNode ans = ListNode(0), *ncur = &ans;
			int cnt = 0, l = 0, r = k - 1;
			vector<ListNode*> vec(k, nullptr);
			while (nullptr != head) {
				if (cnt == k) {
					ncur = this->aux(vec, ncur);
					cnt = 0;
				}
				vec[cnt++] = head;
				head = head->next;
			}
			if (cnt == k)this->aux(vec, ncur);
			return ans.next;
		}
	};
}
void TestReverseNodesInKGroup() {
	ReverseNodesInKGroup::ListNode l5(5);
	ReverseNodesInKGroup::ListNode l4(4);l4.next = &l5;
	ReverseNodesInKGroup::ListNode l3(3);l3.next = &l4;
	ReverseNodesInKGroup::ListNode l2(2);l2.next = &l3;
	ReverseNodesInKGroup::ListNode l1(1);l1.next = &l2;
	ReverseNodesInKGroup::Solution so;
	so.reverseKGroup(&l1, 5);
}