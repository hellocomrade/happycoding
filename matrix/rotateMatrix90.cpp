#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

/*
 Given an image represented by an NxN matrix, where each pixel in the image is
 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
 place?
   1, 2, 3, 4		  13, 9, 5, 1
   5, 6, 7, 8   ==> 14,10, 6, 2 
   9,10,11,12		  15,11, 7, 3
  13,14,15,16		  16,12, 8, 4
 
      1, 2, 3, 4, 5		 21,16,11, 6, 1
      6, 7, 8, 9,10		 22,17,12, 7, 2
      11,12,13,14,15	==>	 23,18,13, 8, 3
      16,17,18,19,20		 24,19,14, 9, 4
      21,22,23,24,25		 25,20,15,10, 5

Obseration:
We are dealing with square here, if we access and swap the elements from outer square to inner square, given N as the length of the rim,
Only N-1 elemetns on each side (4 sides) need to be accessed since there are overlap. Put the A[i][i] on the temp variable, then swap value
from lower left, lower right to lower left, upper right to lower right, upper left to upper right. And then keep this loop from 0 to N-2.
When we are done, start from the inner square. Repeat...

Well, if you ask me this question next time, I probably give you a different index-loop schema. It's really messy... 
 */
void rotateMatrixBy90(vector<vector<int> > &A)
{
    int rowcount = A.size();
    assert(rowcount > 0);
    int colcount = A[0].size();
    assert(colcount == rowcount);
    int tmp = 0;
    //remaining marks the number of elements we have to swap from otter to inner
    //so, it's like 3, 2 for 4X4, 4, 3 for 5X5, [N-1,N/2]
    for (int i = 0, remaining = rowcount - 1; i < remaining; ++i, --remaining)
    {
	//i is the baseline from upper left, j iterate from i to remaining
	//For example 4X4 matrix, i=0 --> j=[0,2]; i=1 --> j=[1,1]
	//Actually, is remaining really necessary to build the indexes?
	for (int j = i; j < remaining; ++j)
	{
	    tmp = A[i][j];
	    A[i][j] = A[i + remaining - j][i];
	    A[i + remaining - j][i] = A[remaining][i + remaining - j];
	    A[remaining][i + remaining - j] = A[j][remaining];
	    A[j][remaining] = tmp;
	}
    }
}
inline void printMatrix(const vector<vector<int> > &A)
{
    for (vector<int> v : A)
    {
	for (int i : v)
  	    cout << std::setw(2) << i << ',';
	cout << endl;
    }
}
void testRotateMatrixBy90()
{
    vector<vector<int> > A1({ { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } });
    cout << "Given Matrix:" << endl;
    printMatrix(A1);
    cout << "Rotate 90 degree clockwise:" << endl;
    rotateMatrixBy90(A1);
    printMatrix(A1);

    vector<vector<int> > A2({ { 1, 2, 3, 4, 5 }, { 6, 7, 8, 9, 10 }, { 11, 12, 13, 14, 15 }, { 16, 17, 18, 19, 20 }, { 21, 22, 23, 24, 25 } });
    cout << "Given Matrix:" << endl;
    printMatrix(A2);
    cout << "Rotate 90 degree clockwise:" << endl;
    rotateMatrixBy90(A2);
    printMatrix(A2);

    vector<vector<int> > A3({ { 1, 2 }, { 3, 4 } });
    cout << "Given Matrix:" << endl;
    printMatrix(A3);
    cout << "Rotate 90 degree clockwise:" << endl;
    rotateMatrixBy90(A3);
    printMatrix(A3);

    vector<vector<int> > A4({ { 1 } });
    cout << "Given Matrix:" << endl;
    printMatrix(A4);
    cout << "Rotate 90 degree clockwise:" << endl;
    rotateMatrixBy90(A4);
    printMatrix(A4);
}
