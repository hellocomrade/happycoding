#include <stack>

using namespace std;

//https://leetcode.com/problems/kth-smallest-element-in-a-bst/
/*
230. Kth Smallest Element in a BST

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Observations:
A In-Order Traversal should do it, stop at k. Did it iterative way. Time complexity O(N), space O(N)

Don't really understand the follow up, doing too much insert/delete on BST? Is it even a balanced tree? Anyway, I guess what
the follow up means is to enlight us using BS? If we could store the size of the tree at any given node as if it's the root,
we could do a binary search around it and overall time complexity is O(logN), no extra space is needed.

Well, I guess what leetcode looks for as follow-up is a heap? I saw the discussion if you use a BS solution by counting the number of children
for each node, then you might store that count info everytime a modification on the tree occurs. But, I don't think BS is a good solution here
at all, just look at how many overlapped counting it has! Yes, you could somehow keep all previous counting through memorization like DP,
but that means extra space as well.
*/
namespace KthSmallestInBST {
    struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    class SolutionKthSmallestInBST {
    private:
	/*
	This recursive version looks ugly, but I can't find a really better one so far.
	*/
	int aux(TreeNode *root, int &k) {
            int i = 0;
            if(nullptr != root->left)i = aux(root->left, k);
            if(0 == k)return i;
            if(0 == --k)return root->val;
            if(nullptr != root->right)i = aux(root->right, k);
            if(0 == k)return i;
            return 0;
        }
    public:
	int kthSmallest(TreeNode* root, int k) {
	    int ans = 0;
	    stack<TreeNode*> stk;
	    TreeNode* node = root;
	    while (nullptr != node || false == stk.empty()) {
		if (nullptr != node) {
		    stk.push(node);
		    node = node->left;
		}
		else {
		    node = stk.top();
		    stk.pop();
		    if (0 == --k) {
			ans = node->val;
			break;
		    }
		    node = node->right;
		}
	    }
	    return ans;
	}
	int kthSmallest1(TreeNode* root, int k) {
            return this->aux(root, k);
    	}
    };
}
