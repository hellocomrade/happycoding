#include <vector>
#include <iostream>

using namespace std;

//https://leetcode.com/problems/search-a-2d-matrix-ii/
/*
 * Search a 2D matrix
 * [
 * [1,   4,  7, 11, 15],
 * [2,   5,  8, 12, 19],
 * [3,   6,  9, 16, 22],
 * [10, 13, 14, 17, 24],
 * [18, 21, 23, 26, 30]
 * ]
 *
 * Observation:
 * All rows and columns are in non-descending order, therefore:
 * If target is less than the start of the column, it might reside in the columns at the left side of the current column
 * If target is greater than the end of the column, it might reside int the columns at the right side of the current column
 * If target is less than the start of the row, it might reside in the rows above the current row
 * If target is greater than the end of the row, it might reside in the rows below the current row
 *
 * Not all of aboves four observations are needed for the algorithm. Let's only pick 1 and 4
 *
 * so, we need to start from the top right corner, if target is less than 15, we take observation 1, move
 * index for column to left by 1, if target is greater than 15, we take observation 4, move index for row
 * down by 1. Everytime we move either indexed by 1, we are facing a new matrix, so we can re-apply the above
 * step again until we run out of index or locate the target.
 *
 * Time complexity O(max(N, M))
 * */
bool search2DMatrix(vector<vector<int>>& matrix, int target)
{
    bool ret = false;
    int rowcnt = matrix.size();
    if (rowcnt > 0)
    {
	int colcnt = matrix[0].size();
  	//the line below is not necessary, however, during a real coding test. This will
  	//help you pass some corner condition test even your main algorithm has flaw...
	if (colcnt<1 || target<matrix[0][0] || target>matrix[rowcnt - 1][colcnt - 1])
	    return ret;
	int i = 0, j = colcnt - 1;
	while (i < rowcnt && j >= 0)
	{
	    if (matrix[i][j] == target)
		return true;
	    else if (matrix[i][j] > target)
		--j;
	    else
		++i;
	}
    }
    return ret;
}
void testSearch2DSortedMatrix()
{
    vector<vector<int> > vec1;
    vec1.push_back(vector<int>({ 1, 4, 7, 11, 15 }));
    vec1.push_back(vector<int>({ 2, 5, 8, 12, 19 }));
    vec1.push_back(vector<int>({ 3, 6, 9, 16, 22 }));
    vec1.push_back(vector<int>({ 10, 13, 14, 17, 24 }));
    vec1.push_back(vector<int>({ 18, 21, 23, 26, 30 }));
    cout << "Expect 1: " << search2DMatrix(vec1, 23) << endl;
    cout << "Expect 0: " << search2DMatrix(vec1, 29) << endl;

    vector<vector<int> > vec2;
    vec2.push_back(vector<int>({15, 20, 40, 85}));
    vec2.push_back(vector<int>({ 20, 35, 80, 95 }));
    vec2.push_back(vector<int>({ 30, 55, 95, 105 }));
    vec2.push_back(vector<int>({40, 80, 100, 120}));
    cout << "Expect 1: " << search2DMatrix(vec2, 55) << endl;
    cout << "Expect 1: " << search2DMatrix(vec2, 99) << endl;
}
