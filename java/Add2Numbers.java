public class SolutionAdd2Numbers {
    public static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
            next = null;      
        }
    }
    private ListNode aux(ListNode l1, ListNode l2, int carry) {
        ListNode ans = null;
        if(l1 != null && l2 != null) {
            ans = new ListNode((l1.val + l2.val + carry) % 10);
            ans.next = aux(l1.next, l2.next, (l1.val + l2.val + carry) / 10);
        }
        else {
            ListNode t = l1 != null ? l1 : l2 != null ? l2 : null;
            if(t != null) {
                ans = new ListNode((t.val + carry) % 10);
                ans.next = aux(t.next, null, (t.val + carry) / 10);
            }
            else if(carry == 1)
                ans = new ListNode(1);
        }
        return ans;
    }
    /**
     * @param l1: the first list
     * @param l2: the second list
     * @return: the sum list of l1 and l2 
     */
    public ListNode addLists(ListNode l1, ListNode l2) {
        // write your code here
        ListNode ans = null;
        if(l1 != null && l2 != null) {
            ans = new ListNode((l1.val + l2.val) % 10);
            ans.next = aux(l1.next, l2.next, (l1.val + l2.val) / 10);
        }
        else if(l1 != null)ans = l1;
        else if(l2 != null)ans = l2;
        return ans;
    }
}
