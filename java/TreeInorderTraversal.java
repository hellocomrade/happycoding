import java.util.Stack;
import java.util.ArrayList;
public class SolutionBinaryTreeInorderTraversal{
public static class TreeNode {
     public int val;
     public TreeNode left, right;
     public TreeNode(int val) {
         this.val = val;
         this.left = this.right = null;
     }
}
public ArrayList<Integer> inorderTraversal(TreeNode root) {
        // write your code here
        ArrayList<Integer> ans = new ArrayList<>();
        if(root != null) {
            TreeNode current = root;
            Stack<TreeNode> stk = new Stack<>();
            while(current != null || stk.empty() == false) {
                while(current != null) {
                    stk.push(current);
                    current = current.left;
                }
                current = stk.pop();
                ans.add(current.val);
                current = current.right;
            }
        }
        return ans;
    }
}
