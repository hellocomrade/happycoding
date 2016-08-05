//https://leetcode.com/problems/validate-binary-search-tree/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
import java.util.Stack;
public class Solution {
    private TreeNode prev = null;
    //Recursion
    public boolean isValidBST(TreeNode root) {
        if(null == root)return true;
        boolean ret = isValidBST(root.left);
        if(false == ret)return false;
        if(prev != null && prev.val >= root.val)return false;
        prev = root;
        return isValidBST(root.right);
    }
    //iteration
    public boolean isValidBST1(TreeNode root) {
        if(null == root)return true;
        Stack<TreeNode> stk = new Stack<>();
        TreeNode prev = null;
        TreeNode current = root;
        while(current != null || stk.empty() == false) {
            while(current != null) {
                stk.push(current);
                current = current.left;
            }
            current = stk.pop();
            if(prev != null && prev.val >= current.val)return false;
            prev = current;
            current = current.right;
        }
        return true;
    }
    private boolean auxLeft(TreeNode node, int grandParentVal) {
        if(null == node)return true;
        else if(node.left != null && node.left.val >= node.val)return false;
        else if(node.right != null && !(node.right.val > node.val && node.right.val < grandParentVal))return false;
        return auxLeft(node.left, node.val) && auxRight(node.right, node.val);
    }
    private boolean auxRight(TreeNode node, int grandParentVal) {
        if(null == node)return true;
        else if(node.left != null && !(node.left.val < node.val && node.left.val > grandParentVal))return false;
        else if(node.right != null && node.right.val <= node.val)return false;
        return auxLeft(node.left, node.val) && auxRight(node.right, node.val);
    }
    //preorder, forgot the nature of BST...
    public boolean isValidBST2(TreeNode root) {
        // write your code here
        if(root == null)return true;
        if(root.left != null && root.left.val >= root.val)return false;
        if(root.right != null && root.right.val <= root.val)return false;
        return auxLeft(root.left, root.val) && auxRight(root.right, root.val);
    }
}
