//https://leetcode.com/problems/copy-list-with-random-pointer/
/*
138. Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

Observations:
The intutive way is by using a hashtable with 2 runs:
1. while copying node, we store the address of the original list node's random. At the meantime, we also
check if the current node from the original list is on hash table already. If yes, it means it has been
referenced somewhere already, we then put the copy's address as the value for the key;
2. Scan the new list, at each node, update the address of the random through hash table;
This approach takes O(N) time, but requires O(N) space as well.

Can we do it in O(1) space and O(N) time? We actually have some extra storage space on newly created
list: "random" pointers!

copyRandomList1 illustrates an attempt to do so using the follow methodology using 2 runs:
1. While copying node, we point newly created node's random to original node's random and point original
node's random to newly created node.
2. On second scan, we access newly created node's true random by using newnode->random->random, which first
visits the original node's random, which has random populated with the new node with the same label, which
is the trun random for current newly created node.
This approach, however, has a flaw: it destroys original list's random pointers, which is not allowed in Leetcode
but OK for lintcode.

Here is the diagram with example: -1 -> 8 -> 7 -> -3 -> 4 [4, -3, null, null, -1]

-1 -> 8 -> 7 -> -3 -> 4 == old list
|    |    |     |    |
\/   \/   \/    \/   \/
-1 -> 8 -> 7 -> -3 -> 4 == new list
|    |    |     |    |
\/   \/   \/    \/   \/
4    -3   null  null -1 == random back on the original list

newitor->random = newitor->random->random;


copyRandomList demonstrates a better solution that can keep the original list "unchanged". It requires
a fancier zig-zag structure:

-1 -> 8   ->  7   ->  -3  ->  4      == old list
|   /\ \    /\ \    /\ \    /\ \
\/ /    \/ /    \/ /    \/ /    \/
-1  ->  8   ->   7   ->  -3  ->  4  == new list

In this approach, we don't touch random on the original list at all. It needs 3 runs:

1. While creating new node, we insert it into the original list, you will have: old->new->old->new...
2. From head, we keep moving onto every other node, which is always the orignal one, then we can
easily update new node's random, which is the "next" of current node, with current original node's random's
next, which "happens" to be the newly created node with the same label, true random one for new node
itor->next->random = itor->random->next
3. We break two lists in the third run

The third run can not be merged with the second run because we could destroy the relationships, for the given
example, if we do so, the last node 4 will not be able to locate its random 1, because at this moment, if we
resume the relation in the original list, original node 1 has next pointing to 8 already, the connection with
newly create node 1 has lost.
*/
namespace CopyListWithRandomPointer {
	struct RandomListNode {
		int label;
		RandomListNode *next, *random;
		RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
	};
	class Solution {
	public:
		//O(N) time, 2 runs, O(1) space, the original list will be changed
		RandomListNode *copyRandomList1(RandomListNode *head) {
			RandomListNode *newhead = nullptr, *itor = head, *newitor = nullptr, *t = nullptr;
			if (head != nullptr) {
				while (itor != nullptr) {
					t = new RandomListNode(itor->label);
					if (newhead == nullptr)newhead = newitor = t;
					else {
						newitor->next = t;
						newitor = newitor->next;
					}
					newitor->random = itor->random;
					itor->random = newitor;
					itor = itor->next;
				}
				newitor = newhead, itor = head;
				while (newitor != nullptr) {
					if (newitor->random != nullptr)
						newitor->random = newitor->random->random;
					newitor = newitor->next;
				}
			}
			return newhead;
		}
		//O(N) time, 2 runs, O(1) space, the original list can be restored
		RandomListNode *copyRandomList(RandomListNode *head) {
			RandomListNode *newhead = nullptr, *itor = head, *newitor = nullptr, *t = nullptr;
			if (head != nullptr) {
				while (itor != nullptr) {
					newitor = new RandomListNode(itor->label);
					t = itor->next;
					itor->next = newitor;
					newitor->next = t;
					itor = t;
				}
				itor = head;
				while (itor != nullptr && itor->next != nullptr) {
					if (itor->random != nullptr)
						itor->next->random = itor->random->next;
					itor = itor->next->next;
				}
				itor = head;
				while (itor != nullptr && itor->next != nullptr) {
					if (newhead == nullptr) {
						newhead = itor->next;
						newitor = newhead;
					}
					else {
						newitor->next = itor->next;
						newitor = newitor->next;
					}
					itor->next = itor->next->next;
					itor = itor->next;
				}
			}
			return newhead;
		}
	};
}