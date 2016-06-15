//https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
/*
109. Convert Sorted List to Binary Search Tree

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

Example
2
1->2->3  =>   / \
1   3

Observation:
Recursion like the usual way we build a BT. It requires balanced BST, but no extra concern needed for rotation
since the elements are sorted. We could take advantage of the full binary tree idea or heap in an array that
the head of a subtree is always on element with the index of size / 2
We could recursively solve this problem by keeping split the list to 2 halfs. Create the head node at
size /2 and then split the list to 2 pieces until each piece only contains one element.

Time complexity is O(NlogN) which is as same as building a regular BST.

BTW, this implementation happens to generate the tree as same as the output from test cases. But, you shall
know that there are other forms of balanced BST that do not look as same as the output...
*/
namespace ConvertSortedList2BST {
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};

	class SolutionConvertSortedList2BST {
	public:
		TreeNode* sortedListToBST(ListNode* head) {
			if (nullptr == head)return nullptr;
			else if (nullptr == head->next)return new TreeNode(head->val);
			ListNode *fast = head, *slow = head, *prev = head;
			while (nullptr != fast && nullptr != fast->next)
			{
				prev = slow;
				slow = slow->next;
				fast = fast->next->next;
			}
			prev->next = nullptr;
			TreeNode *thead = new TreeNode(slow->val);
			thead->left = sortedListToBST(head);
			thead->right = sortedListToBST(slow->next);
			return thead;
		}
	};
}