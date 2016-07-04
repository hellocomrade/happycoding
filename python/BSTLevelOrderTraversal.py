"""
Definition of TreeNode:
class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left, self.right = None, None
"""


class SolutionBSTLevelOrderTraversal:
    """
    @param root: The root of binary tree.
    @return: Level order in a list of lists of integers
    """
    def levelOrder(self, root):
        # write your code here
        ans = []
        if root is not None:
            q = []
            q.append(root)
            while q:
                size = len(q)
                vec = [0] * size
                for i in xrange(size):
                    node = q.pop(0)
                    vec[i] = node.val
                    if node.left:
                        q.append(node.left)
                    if node.right:
                        q.append(node.right)
                ans.append(vec)
        return ans
