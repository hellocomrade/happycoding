#include <vector>
#include <bitset>

using namespace std;

//https://leetcode.com/problems/linked-list-components/
/*
817. Linked List Components

We are given head, the head node of a linked list containing unique integer values.

We are also given the list G, a subset of the values in the linked list.

Return the number of connected components in G, where two values are connected if they appear consecutively in the linked list.

Example 1:

Input:

head: 0->1->2->3

G = [0, 1, 3]

Output: 2

Explanation:
0 and 1 are connected, so [0, 1] and [3] are the two connected components.

Example 2:

Input:

head: 0->1->2->3->4

G = [0, 3, 1, 4]

Output: 2

Explanation:
0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.

Note:

- If N is the length of the linked list given by head, 1 <= N <= 10000.
- The value of each node in the linked list will be in the range [0, N - 1].
- 1 <= G.length <= 10000.
- G is a subset of all values in the linked list.

Observations:

Seem to be very straightforward to me. O(N) extra space to track all values in G. Then scan the list, increase the
counter by 1 if the value of current list node is not available in G.

Since G.length <= 10000, we can safely use an array of integer or even a bitset to track values in G.
*/
namespace LinkedListComponents {
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
		int numComponents(ListNode* head, vector<int>& G) {
			bitset<10001> arr;
			int ans = 0, cnt = 0;
			for (int i : G) arr.set(i, 1);
			while (nullptr != head) {
				if (true == arr.test(head->val)) ++cnt;
				else {
					ans = cnt > 0 ? ans + 1 : ans;
					cnt = 0;
				}
				head = head->next;
			}
			return cnt > 0 ? ans + 1 : ans;
		}
		int numComponents1(ListNode* head, vector<int>& G) {
			int arr[10000] = { 0 }, ans = 0, cnt = 0;
			for (int i : G) arr[i] = 1;
			while (nullptr != head) {
				if (1 == arr[head->val]) ++cnt;
				else {
					ans = cnt > 0 ? ans + 1 : ans;
					cnt = 0;
				}
				head = head->next;
			}
			return cnt > 0 ? ans + 1 : ans;
		}
	};
}