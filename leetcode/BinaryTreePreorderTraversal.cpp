#include <stack>
#include <vector>

using namespace std;

//https://leetcode.com/problems/binary-tree-preorder-traversal/
/*
144. Binary Tree Preorder Traversal

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],
   1
    \
     2
    /
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/
namespace BinaryTreePreorderTraversal {
 //Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };
 
class SolutionBinaryTreePreorderTraversal {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> stk;
        while(nullptr != root || false == stk.empty()) {
            while(nullptr != root) {
                ans.push_back(root->val);
                stk.push(root);
                root = root->left;
            }
            root = stk.top(), stk.pop();
            root = root->right;
        }
        return ans;
    }
};
}
