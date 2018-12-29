# Definition for a binary tree node.
# 

class SolutionPathSum2:

    class TreeNode:
        def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

    def pathSum(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: List[List[int]]
        """
        ans, memo = [], []
        def bt(root, remain):
            if not root: return
            memo.append(root.val)
            # Not like C++, list of lists only copies the reference of the list
            # Thus, ans.append(memo) only makes a shallow copy of memo. But deep copy is needed here
            # Either memo[:] to create the new slice or list(memo)
            if not root.left and not root.right and remain == root.val: ans.append(memo[:])
            if root.left: bt(root.left, remain - root.val)
            if root.right: bt(root.right, remain - root.val)
            memo.pop()
            
        bt(root, sum)
        return ans

    # Pythonic: list comprehension will return [] if for loop is on an empty list
    def pathSum1(self, root, sum):
        if not root: return []
        elif not root.left and not root.right and sum == root.val: return [[root.val]]
        else: return [[root.val] + _ for _ in self.pathSum(root.left, sum - root.val) + self.pathSum(root.right, sum - root.val)]
