"""
Definition of TreeNode:
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left, self.right = None, None
"""
class Solution:
    def __rightTreeSmallest(self, node):
        right = node.right
        if right.left:
            while right.left.left:
                right = right.left
            ret = right.left.val
            right.left = None
            return ret
        else:
            node.right = right.right
            return right.val
    """
    @param root: The root of the binary search tree.
    @param value: Remove the node with given value.
    @return: The root of the binary search tree after removal.
    """    
    def removeNode(self, root, value):
        # write your code here
        if root:
            node, parent = root, root
            while node:
                if node.val == value:
                    break
                parent = node
                node = node.left if node.val > value else node.right
            if node:
                if node.left and node.right:
                    node.val = self.__rightTreeSmallest(node)
                elif node.left or node.right:
                    if node == root:
                        root = node.left if node.left else node.right
                    elif parent.left == node:
                        parent.left = node.left if node.left else node.right
                    else:
                        parent.right = node.left if node.left else node.right
                else:
                    if node == root:
                        root = None
                    elif parent.left == node:
                        parent.left = None
                    else:
                        parent.right = None
        return root
