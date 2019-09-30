# https://leetcode.com/problems/minimum-height-trees/
class SolutionMinimumHeightTrees:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        adj_matrix, leaf_q, m = dict(), list(), n
        for edge in edges:
            for e in edge:
                if e not in adj_matrix:
                    adj_matrix[e] = [0, list()]
            adj_matrix[edge[0]][0] = adj_matrix[edge[0]][0] + 1
            adj_matrix[edge[0]][1].append(edge[1])
            adj_matrix[edge[1]][0] = adj_matrix[edge[1]][0] + 1
            adj_matrix[edge[1]][1].append(edge[0])
        leaf_q = [i for i in range(n) if i in adj_matrix and 1 == adj_matrix[i][0]]
        while 2 < n:
            cnt = len(leaf_q)
            while 0 < cnt:
                for neighbor in adj_matrix[leaf_q[0]][1]:
                    adj_matrix[neighbor][0] = adj_matrix[neighbor][0] - 1
                    if 1 == adj_matrix[neighbor][0]:
                        leaf_q.append(neighbor)
                leaf_q.pop(0)
                n, cnt = n - 1, cnt - 1
        return leaf_q if 1 < m else [0]
