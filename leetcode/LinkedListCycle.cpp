namespace LinkedListCycle {
/**
 * Definition for singly-linked list.
*/
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
};
//https://leetcode.com/problems/linked-list-cycle/
/*
141. Linked List Cycle

Given a linked list, determine if it has a cycle in it.

To represent a cycle in the given linked list, we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.

 

Example 1:

Input: head = [3,2,0,-4], pos = 1

Output: true

Explanation: There is a cycle in the linked list, where tail connects to the second node.


Example 2:

Input: head = [1,2], pos = 0

Output: true

Explanation: There is a cycle in the linked list, where tail connects to the first node.


Example 3:

Input: head = [1], pos = -1

Output: false

Explanation: There is no cycle in the linked list.
*/
class Solution {
public:
    // Detect cycle in while loop, return False at end
    bool hasCycle(ListNode *head) {
        ListNode *hare = head, *tortoise = head;
        // No need to check nullptr != tortoise, coz hare is always faster.
        while(nullptr != hare && nullptr != hare->next) {
            tortoise = tortoise->next, hare = hare->next->next;
            if(hare == tortoise) return true;
        } 
        return false;
    }
    // Detect acyclic list in while loop, return True at end
    bool hasCycle0(ListNode *head) {
        if(nullptr == head) return false;
        ListNode *hare = head->next, *tortoise = head;
        while(hare != tortoise) {
            if(nullptr == hare || nullptr == hare->next) return false;
            tortoise = tortoise->next, hare = hare->next->next;
        } 
        return true;
    }
};
}
/*
Test cases:

[3,2,0,-4]
1
[1,2]
-1
[3,2,0]
0
[1]
0
[1]
-1
[]
-1

Outputs:

true
false
true
true
false
false

*/
