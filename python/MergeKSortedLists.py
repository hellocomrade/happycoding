# https://leetcode.com/problems/merge-k-sorted-lists
class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

class SolutionMergeKSortedLists(object):
    def merge2Lists(self, l1, l2):
        dummy = ListNode(0)
        itor = dummy
        while None != l1 and None != l2:
            if l1.val <= l2.val:
                itor.next = l1
                l1 = l1.next
            else:
                itor.next = l2
                l2 = l2.next
            itor = itor.next
        itor.next = l1 if None != l1 else l2
        return dummy.next
                
    """
    @param lists: a list of ListNode
    @return: The head of one sorted list.
    """
    def mergeKLists(self, lists):
        size = len(lists)
        while size > 1:
            for i in range(0, size - 1, 2):
                lists[i // 2] = self.merge2Lists(lists[i], lists[i + 1])
            if 1 == (1 & size):
                lists[size // 2] = lists[size - 1]
                size = size // 2 + 1
            else:
                size = size // 2
        return None if 0 == size else lists[0]
