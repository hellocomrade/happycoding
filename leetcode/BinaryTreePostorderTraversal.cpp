#include <vector>
#include <stack>

using namespace std;

//https://leetcode.com/problems/binary-tree-postorder-traversal/
/*
145. Binary Tree Postorder Traversal

Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],

   1
    \
     2
    /
   3
 

return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?

Observation:

Comparing with preorder and inorder, the difference here in terms of iterative approach is: look back on the previously visited node to tell
if current node's right child has been visited already, if so, it's time to visit current node. If not, go to current node's right subtree.
*/
namespace BinaryTreePostorderTraversal {
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> stk;
        while(nullptr != root || false == stk.empty()) {
            while(nullptr != root) {
                stk.push(root);
                root = root->left;
            }
            root = stk.top()->right;
            if(nullptr == root || (ans.size() > 0 && ans[ans.size() - 1] == stk.top()->right->val)) {
                ans.push_back(stk.top()->val), stk.pop();
                root = nullptr;
            }
        }
        return ans;
    }
};
}
