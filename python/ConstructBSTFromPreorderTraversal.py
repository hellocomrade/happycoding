# https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
class SolutionConstructBSTFromPreOrder:

    # Definition for a binary tree node.
    class TreeNode:
        def __init__(self, x):
            self.val = x
            self.left = None
            self.right = None

    def bstFromPreorder(self, preorder: List[int]) -> TreeNode:
        i, sz = 0, len(preorder)
        def fun(min_val = float('-inf'), max_val = float('inf')) -> TreeNode:
            nonlocal i
            if sz == i or preorder[i] <= min_val or preorder[i] >= max_val: return None
            root = TreeNode(preorder[i])
            i += 1
            root.left = fun(min_val, root.val)
            root.right = fun(root.val, max_val)
            return root
        return fun()