#http://www.lintcode.com/en/problem/topological-sorting/
# Definition for a Directed graph node
# class DirectedGraphNode:
#     def __init__(self, x):
#         self.label = x
#         self.neighbors = []

class Solution:
    """
    @param graph: A list of Directed graph node
    @return: A list of graph nodes in topological order.
    """
    def topSort(self, graph):
        inOrder, ans = {}, []
        for node in graph:
            if not inOrder.has_key(node):
                #new key in dict and no incoming edge
                inOrder[node] = 0
            for neighbor in node.neighbors:
                #if new key in dict, it's init value is 1 instead of 0 since it's as a neighbor having at least 1 incoming edge
                inOrder[neighbor] = inOrder[neighbor] + 1 if inOrder.has_key(neighbor) else 1
        #exhaust nodes in the dict, since we update inorder value on each iteration, there is no way to get the sort done in a single for...in
        while len(inOrder):
            #using dict.keys() allows removing key value pair in loop
            for node in inOrder.keys():
                if inOrder[node] == 0:
                    for neighbor in node.neighbors:
                        inOrder[neighbor] -= 1
                    ans.append(node)
                    del inOrder[node]
        return ans
