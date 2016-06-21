//https://leetcode.com/problems/sort-list/
/*
148. Sort List

Sort a linked list in O(n log n) time using constant space complexity.

Observations:
It ask O(1) space, this excludes quick sort, which requires O(logN) space no matter what.

Since this is a linked list, we could apply bottom-up merge sort.

"The evil always comes from details"...can you really do this in 30 minutes without any bug?
*/
namespace SortList {
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};
	class SolutionSortList {
	private:
		void copyListfrom2(ListNode*& copyfrom, ListNode*& copy2, int cnt) {
			if (cnt > 0) {
				while (copyfrom != nullptr && cnt--) {
					copy2->next = copyfrom;
					copy2 = copyfrom;
					copyfrom = copyfrom->next;
				}
			}
		}
		void seekNext(ListNode* left, int size, ListNode*& right, int& lcnt, int& rcnt) {
			lcnt = rcnt = 0;
			while (left && ++lcnt < size)left = left->next;
			if (left && left->next) {
				right = left->next;
				left = right;
				while (left && ++rcnt < size)left = left->next;
			}
			else
				right = nullptr;
		}
	public:
		//Toooo long
		ListNode* sortList1(ListNode* head) {
			ListNode *itor = head, *left = head, *right = head, *newhead = head, *leftend = nullptr, *rightend = nullptr, *tmp = nullptr, *last = nullptr, *end = nullptr;
			int cnt = 0, run = 1, size = 0;
			if (head != nullptr)
			{
				while (itor != nullptr)
				{
					++size;
					itor = itor->next;
				}
				while (run < size)
				{
					run <<= 1;
					itor = newhead;
					newhead = nullptr;
					while (itor != nullptr)
					{
						left = leftend = itor;
						cnt = 0;
						while (itor != nullptr && ++cnt < run)
						{
							if (run / 2 == cnt)
								leftend = itor;
							itor = itor->next;
						}
						right = leftend->next;
						rightend = itor == nullptr ? nullptr : itor->next;
						while (left != leftend->next && right != rightend)
						{
							if (left->val <= right->val)
							{
								tmp = left;
								left = left->next;
							}
							else
							{
								tmp = right;
								right = right->next;
							}
							if (newhead == nullptr)
							{
								newhead = tmp;
								last = newhead;
							}
							else
							{
								last->next = tmp;
								last = last->next;
							}
						}
						if (left != leftend->next)
						{
							tmp = left;
							end = leftend->next;
						}
						else if (right != rightend)
						{
							tmp = right;
							end = rightend;
						}
						else
							tmp = nullptr;
						if (newhead == nullptr)
						{
							newhead = tmp;
							last = newhead;
						}
						while (tmp != nullptr && tmp != end)
						{
							last->next = tmp;
							last = last->next;
							tmp = tmp->next;
						}
						itor = rightend;
					}
					last->next = nullptr;

				}
			}
			return newhead;
		}
		//Better, but...
		ListNode* sortList(ListNode* head) {
			ListNode *ans = head;
			if (head) {
				ListNode *itor = head, *left = head, *right = nullptr, *tail = head;
				int mergeSize = 1, leftCnt = 0, rightCnt = 0, cnt = 0;
				while (head != nullptr) {
					itor = ans = head;
					head = nullptr;
					while (nullptr != itor) {
						left = itor, cnt = 1, leftCnt = 0, rightCnt = 0;
						while (itor != nullptr && cnt++ <= mergeSize)
							itor = itor->next;
						if (nullptr == itor) {
							while (left != ans && left != nullptr) {
								tail->next = left;
								tail = left;
								left = left->next;
							}
							break;
						}
						else right = itor;
						while (leftCnt < mergeSize && nullptr != right && rightCnt < mergeSize) {
							if (left->val <= right->val) {
								itor = left, ++leftCnt;
								left = left->next;
							}
							else {
								itor = right, ++rightCnt;
								right = right->next;
							}
							if (nullptr == head)
								head = tail = itor;
							else {
								tail->next = itor;
								tail = itor;
							}
						}
						while (leftCnt < mergeSize) {
							tail->next = left;
							tail = left;
							left = left->next;
							++leftCnt;
						}
						while (nullptr != right && rightCnt < mergeSize) {
							tail->next = right;
							tail = right;
							right = right->next;
							++rightCnt;
						}
						itor = right;
					}
					tail->next = nullptr;
					mergeSize <<= 1;
				}
			}
			return ans;
		}
		//I am not sure if this version is better it's shorter though.
		//by using two aux funtions to handle duplicates logics
		ListNode *sortList2(ListNode *head) {
			ListNode *first = head, *second = nullptr, *tmp = nullptr, *itor = nullptr;
			if (head) {
				int size = 1, lcnt = 1, rcnt = 1;
				second = head->next;
				head = nullptr;
				while (second) {
					while (first) {
						if (second == nullptr) {
							this->copyListfrom2(first, itor, lcnt);
							break;
						}
						while (lcnt > 0 && rcnt > 0) {
							if (first->val <= second->val) {
								tmp = first;
								first = first->next;
								--lcnt;
							}
							else {
								tmp = second;
								second = second->next;
								--rcnt;
							}
							if (head == nullptr) {
								head = tmp;
								itor = tmp;
							}
							else {
								itor->next = tmp;
								itor = tmp;
							}
						}
						if (lcnt > 0)this->copyListfrom2(first, itor, lcnt);
						else if (second != nullptr && rcnt > 0)this->copyListfrom2(second, itor, rcnt);
						first = tmp = second;
						this->seekNext(tmp, size, second, lcnt, rcnt);
					}
					itor->next = nullptr;
					size <<= 1;
					first = tmp = head;
					head = nullptr;
					this->seekNext(tmp, size, second, lcnt, rcnt);
				}
			}
			return first;
		}
	};
}
void TestSortList() {
	SortList::ListNode node4(1);
	SortList::ListNode node3(2);
	node3.next = &node4;
	SortList::ListNode node2(3);
	node2.next = &node3;
	SortList::ListNode node1(4);
	node1.next = &node2;
	SortList::SolutionSortList so;
	SortList::ListNode *newhead = so.sortList(&node1);

	node4.next = &node2;
	node2.next = &node3;
	node3.next = nullptr;
	newhead = so.sortList(&node4);//1,3,2

	SortList::ListNode n1(1);
	SortList::ListNode n2(2);
	n2.next = &n1;
	SortList::ListNode n3(3);
	n3.next = &n2;
	SortList::ListNode n4(4);
	n4.next = &n3;
	SortList::ListNode n5(5);
	n5.next = &n4;
	newhead = so.sortList(&n5);
}