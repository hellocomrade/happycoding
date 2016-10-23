#include <vector>

using namespace std;

//https://leetcode.com/problems/unique-paths/
/*
 62. Unique Paths
 
 A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 
 The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 
 How many possible unique paths are there?
 
 Note: m and n will be at most 100.
 
 Observation:
 It's not hard to discover unique_paths[m][n] = unique_paths[m][n - 1] + unique_paths[m - 1][n], if we apply
 DP approach here, since robot can only move down or right. unique_paths[m][n - 1] is the count left to 
 unique_paths[m][n], unique_paths[m - 1][n] is the count top to unique_paths[m][n].
 
 We cound build a memo array to track all previous count. This leads to an O(m X n) space. See uniquePaths1.
 
 However, after a second look, you would find that we actually only care the previous line given a m X n 
 array for tracking purpose! At any given index k (assuming we have a memo 1D array with size of n), its
 count memo[k] = memo-left + memo-top. memo-left and memo-top may or may not exist depending on the location
 of k. Either way, they can be found either by looking at memo[k - 1] (for left) or checking the previous
 memo[k] (for top). Otherwise, they shall be zero. Therefore, we only need O(n) space.
 
 The only exception is memo[0] at the very beginning: for this case, it has to be assigned to 1 and our loop
 should escape from this case.
 
 Time complexity: O(m X n).
*/
class SolutionUniquePath {
public:
    int uniquePaths(int m, int n) {
        if(m < 1 || n < 1)return 0;
        vector<long long> memo(n, 0);
        long long left = 0, top = 0;
        memo[0] = 1;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j) {
                if(0 == i && 0 == j)continue;
                left = (j - 1 >= 0) ? memo[j - 1] : 0;
                top = (i - 1 >= 0) ? memo[j] : 0;
                memo[j] = left + top;
            }
        }
        return (int)memo[n - 1];
    }
    int uniquePaths1(int m, int n) {
        if(m < 1 || n < 1)return 0;
        vector<vector<long long>> memo(m, vector<long long>(n, 1));
        for(int i = 1; i < m; ++i)
        {
            for(int j = 1; j < n; ++j)
                memo[i][j] = memo[i-1][j] + memo[i][j - 1];
        }
        return (int)memo[m - 1][n - 1];
    }
};
