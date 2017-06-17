#include <vector>

//https://leetcode.com/problems/merge-k-sorted-lists/
/*
23. Merge k Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Observations:
Souds like merge sort, why don't we apply merge sort trick directly! Only difference is that I reuse the input vector
as the array to store the intermidate merge result. Since we merge the continuous 2 lists into 1 on each merge run, the array
will shrink to half. Have to consider the odd: we have odd number of lists in the vector. Then the last one will be transfered to
the smaller array without processing. It will be merged with the result of (len - 1) lists, given len as a odd number.

Merge 2 lists has been done in leedcode 21, which can be found at: https://github.com/hellocomrade/happycoding/blob/master/leetcode/mergeTwoLists.cpp
*/
namespace mergeKSortedLists{

struct ListNode { 
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class SolutionMergeKSortedLists {
private:
    ListNode* merge2(ListNode *l1, ListNode *l2) {
        ListNode dummy(0);
        ListNode *pos = &dummy;
        while(nullptr != l1 && nullptr != l2) {
            if(l1->val <= l2->val) {
                pos->next = l1;
                l1 = l1->next;
            }
            else {
                pos->next = l2;
                l2 = l2->next;
            }
            pos = pos->next;
        }
        pos->next = nullptr != l1 ? l1 : l2;
        return dummy.next;
    }
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        size_t len = lists.size();
        if(0 == len)return nullptr;
        size_t k = 0;
        while(len > 1) {
            k = 0;
            for(size_t i = 0; i < len && i + 1 < len; i += 2)
                lists[k++] = this->merge2(lists[i], lists[i + 1]);
            if(1 == (1 & len))//odd length
                lists[k++] = lists[len - 1];
            len = k;
        }
        return lists[0];
    }
};
}
