#include <vector>

using namespace std;

//https://leetcode.com/problems/unique-paths-ii/
/*
 63. Unique Paths II
 
 Follow up for "Unique Paths":
 
 Now consider if some obstacles are added to the grids. How many unique paths would there be?
 
 An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 
 For example,
 There is one obstacle in the middle of a 3x3 grid as illustrated below.
 
 [
 [0,0,0],
 [0,1,0],
 [0,0,0]
 ]
 The total number of unique paths is 2.
 
 Note: m and n will be at most 100.
 
 Observations:
 OK, as a followup on Unique Paths (Leetcode 62), we now have a maze grid with 1 to represent an obstacle
 at the cell!
 
 Apply the same DP from 62 on 63 should be straightforward. Regarding the space need, since a vector 2D
 array is given through input, we could take advantage of it and therefore, no extra space is necessary!
 
 Note: if obstacleGrid[0][0] or obstacleGrid[m - 1][n - 1] is 0, there is no path at all.
 
 Comparing with 62, the extra step is: we have to check the value at obstacleGrid[i][j] first, if it's 1,
 then no count is needed, assign the cell to 0 and carry on.
 
 You may notice both left and up have the type of size_t (long long for 64-bits OS). However, due to the fact
 that the input array is with integer, there is an implicit conversion when we assign (left + up) to the
 obstacleGrid (obstacleGrid[i][j] = (int)(left + up);). Well, you could argue this should force us using an
 extra O(n) space with element type of size_t...
*/
class SolutionUniquePaths2 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        size_t row = obstacleGrid.size();
        if(0 == row)return 0;
        size_t col = obstacleGrid[0].size(), left = 0, up = 0;
        if(0 == col)return 0;
        obstacleGrid[0][0] = (1 == obstacleGrid[0][0]) ? 0 : 1;
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                if(0 == i && 0 == j)continue;
                if(1 == obstacleGrid[i][j])
                    obstacleGrid[i][j] = 0;
                else {
                    left = i > 0 ? obstacleGrid[i - 1][j] : 0;
                    up = j > 0 ? obstacleGrid[i][j - 1] : 0;
                    obstacleGrid[i][j] = (int)(left + up);
                }
            }
        }
        return obstacleGrid[row - 1][col - 1];
    }
};
