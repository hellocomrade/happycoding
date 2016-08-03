#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

namespace TreeSort {
    struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	};
	class SolutionTreeSort {
	    private:
	    TreeNode* insertNode2BST(TreeNode *root, int value) {
	        if(nullptr == root)return new TreeNode(value);
	        TreeNode *node = root, *prev = nullptr;
	        while(nullptr != node) {
	            prev = node;
	            if(node->val < value)node = node->right;
	            else node = node->left;
	        }
	        if(prev->val < value)prev->right = new TreeNode(value);
	        else prev->left = new TreeNode(value);
	        return root;
	    }
	    public:
	    void BSTInOrderTraversal(TreeNode* root) {
	        if(nullptr == root)return;
	        BSTInOrderTraversal(root->left);
	        cout << root->val << ",";
	        BSTInOrderTraversal(root->right);
	        return;
	    }
	    TreeNode* Sort(vector<int>& A) {
	        int len = A.size(), idx = 0;
	        TreeNode *root = nullptr;
	        srand(time(nullptr));
	        for(int i = 0; i < len; ++i) {
	            idx = i + rand() % (len - i);
	            std::swap(A[i], A[idx]);
	            root = this->insertNode2BST(root, A[i]);
	        }
	        return root;
	    }
	};
}
void TestTreeSort(void) {
using Solution = TreeSort::SolutionTreeSort;
using TreeNode = TreeSort::TreeNode;
    Solution so;
    vector<int> vec{9,5,6,3,2,7,8};
    TreeNode* root = so.Sort(vec);
    so.BSTInOrderTraversal(root);
    return;
}
