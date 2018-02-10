#include <vector>
#include <queue>
#include <deque>
#include <stack>

using namespace std;

namespace BinaryTreeZigzagLevelOrderTraversal {
//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
/*
103. Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

Observations:

This is a question that can be solved using multiple approaches. 

- Since it asks zigzg, you can do 2 stacks, zigzagLevelOrder2;

- Deque works as well, push/pop position is determined by the level, zigzagLevelOrder1;

- Still take advantage of standard iterative level order traversal by using a queue. Since we know exactly how many nodes per level, it can
  be implemented by inserting the node per its zigzag order, zigzagLevelOrder;
  
You can even solve this recursively if you don't mind inserting element at the beginning at the vector...
*/
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(nullptr == root)return ans;
        int cnt = 0, level = 0;
        queue<TreeNode*> q;
        q.push(root);
        while(0 < (cnt = q.size())) {
            ans.push_back(vector<int>(cnt, 0));
            for(int i = 0; i < cnt; ++i) {
                root = q.front(), q.pop();
                if(nullptr != root->left)q.push(root->left);
                if(nullptr != root->right)q.push(root->right);
                if(0 != (level & 1))ans[level][cnt - i - 1] = root->val;
                else ans[level][i] = root->val;
            }
            ++level;
        }
        return ans;
    }
    vector<vector<int>> zigzagLevelOrder1(TreeNode* root) {
        vector<vector<int>> ans;
        if(nullptr == root)return ans;
        int cnt = 0, level = 0;
        deque<TreeNode*> q;
        q.push_back(root);
        while(0 < (cnt = q.size())) {
            ans.push_back(vector<int>(cnt, 0));
            for(int i = 0; i < cnt; ++i) {
                if(0 == (level & 1)) {
                    root = q.front(), q.pop_front();
                    if(nullptr != root->left)q.push_back(root->left);
                    if(nullptr != root->right)q.push_back(root->right);
                
                }
                else {
                    root = q.back(), q.pop_back();
                    if(nullptr != root->right)q.push_front(root->right);
                    if(nullptr != root->left)q.push_front(root->left);
                }
                ans[level][i] = root->val;
            }
            ++level;
        }
        return ans;
    }
    vector<vector<int>> zigzagLevelOrder2(TreeNode* root) {
        vector<vector<int>> ans;
        if(nullptr == root)return ans;
        int cnt = 0, level = 0;
        stack<TreeNode*> stk0, stk1;
        stk0.push(root);
        while(false == stk0.empty() || false == stk1.empty()) {
            ans.push_back(vector<int>());
            if(false == stk0.empty()) {
                while(false == stk0.empty()) {
                    root = stk0.top(), stk0.pop();
                    ans[level].push_back(root->val);
                    if(nullptr != root->left)stk1.push(root->left);
                    if(nullptr != root->right)stk1.push(root->right);
                }
            }
            else {
                while(false == stk1.empty()) {
                    root = stk1.top(), stk1.pop();
                    ans[level].push_back(root->val);
                    if(nullptr != root->right)stk0.push(root->right);
                    if(nullptr != root->left)stk0.push(root->left);
                }
            }
            ++level;
        }
        return ans;
    }
};
}
