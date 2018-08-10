#include <vector>

using namespace std;

//108. Convert Sorted Array to Binary Search Tree
/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

Observation:

Head of any given subtree is always at index size / 2 on the array, which size is the number of node in this subtree.
This is only true if the array has been sorted already.
*/
namespace ConvertSortedArray2BST {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class SolutionConvertSortedArray2BST {
	private:
		TreeNode* aux(const vector<int>& nums, int l, int r) {
			if (l > r) return nullptr;
			if (l == r) return new TreeNode(nums[l]);
			int m = l + (r - l) / 2;
			TreeNode* node = new TreeNode(nums[m]);
			node->left = this->aux(nums, l, m - 1);
			node->right = this->aux(nums, m + 1, r);
			return node;
		}
		TreeNode* aux1(const vector<int>& nums, long long low, long long high)
		{
			if (low > high)return nullptr;
			else if (low == high)return new TreeNode(nums[high]);
			//simply want to keep the output looks like the output from leetcode
			//You could do (high + low + 1) / 2 instead
			long long mid = (high - low + 1) & 1 == 1 ? low + (high - low) / 2 : low + (high - low) / 2 + 1;
			TreeNode *head = new TreeNode(nums[mid]);
			head->left = this->aux1(nums, low, mid - 1);
			head->right = this->aux1(nums, mid + 1, high);
			return head;
		}
	public:
		TreeNode* sortedArrayToBST(vector<int>& nums) {
			return this->aux(nums, 0, nums.size() - 1);
		}
	};
}
/*
Test cases:

[-10,-3,0,5,9]
[1,1,1]
[1,2,3,4,5,6]
[]
[1]
[1,2]
[1,2,3]

Outputs:

[0,-10,5,null,-3,null,9]
[1,1,1]
[3,1,5,null,2,4,6]
[]
[1]
[1,null,2]
[2,1,3]
*/