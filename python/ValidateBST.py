"""
Definition of TreeNode:
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left, self.right = None, None
"""
class SolutionValidateBST:
    """
    @param root: The root of binary tree.
    @return: True if the binary tree is BST, or false
    """  
    def isValidBST(self, root):
        # write your code here
        if root:
            stk = []
            current, prev = root, None
            while stk or current:
                while current:
                    stk.append(current)
                    current = current.left
                current = stk.pop()
                if prev is not None and prev.val >= current.val:
                    return False
                prev = current
                current = current.right
        return True
