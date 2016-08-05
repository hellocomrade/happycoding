import java.util.Stack;
import java.util.ArrayList;
public class  SolutionBinaryTreePreorderTraversal{
public static class TreeNode {
     public int val;
     public TreeNode left, right;
     public TreeNode(int val) {
         this.val = val;
         this.left = this.right = null;
     }
}
 public ArrayList<Integer> preorderTraversal(TreeNode root) {
        // write your code here
        ArrayList<Integer> ans = new ArrayList<>();
        if(root != null) {
            TreeNode current = null;
            Stack<TreeNode> stk = new Stack<>();
            stk.push(root);
            while(stk.empty() == false) {
                current = stk.pop();
                ans.add(current.val);
                if(current.right != null)
                    stk.push(current.right);
                if(current.left != null)
                    stk.push(current.left);
            }
        }
        return ans;
    }
}
