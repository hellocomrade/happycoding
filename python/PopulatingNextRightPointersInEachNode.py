"""
# Definition for a Node.
class Node:
    def __init__(self, val, left, right, next):
        self.val = val
        self.left = left
        self.right = right
        self.next = next
"""
class SolutionPopulatingNextRightPointersInEachNode:

    def connect(self, root: 'Node') -> 'Node':
        ans, pnode, prev = root, None, None
        while root and root.left:
            root.left.next = root.right
            prev, pnode = root, root.next
            while pnode:
                prev.right.next = pnode.left
                pnode.left.next = pnode.right
                prev, pnode = pnode, pnode.next
            root = root.left
        return ans
        
     def connect1(self, root: 'Node') -> 'Node':
        if not root: return None
        if not root.left: return root
        root.left.next = root.right
        if root.next: root.right.next = root.next.left
        self.connect(root.left)
        self.connect(root.right)
        return root
