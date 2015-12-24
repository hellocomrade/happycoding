#include <cassert>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

/*
Write an algorithm such that if an element in an MxN matrix is 0, its entire row
and column are set to 0.

For example:

1, 2			1, 0
3, 0	-->		0, 0

1, 0, 2, 3     0, 0, 0, 0
2, 4, 1, 5 --> 0, 0, 1, 5
0, 2, 3, 5		0, 0, 0, 0

1, 2, 3, 4		 1, 2, 0, 4
2, 2, 0, 4  --> 0, 0, 0, 0
3, 2, 3, 4		 3, 2, 0, 4
4, 2, 3 ,4		 4, 2, 0, 4

Observation:
If you simply scan the matrix and whenever meets a zero at [i,j] then clear out the row i and column j,
you will generate more zero on the cells you have not visited and cover up the cell that originally has
zero. A simple solution would be cloning the entire matrix as lookup, but it will take extra M*N space.

Can we do this in place? No matter where zero is, the outter rim will be zero out at that i and j. Even
zero is on outter rim, this still apply. So, what if we store the row and column that need to be zero out
at outter rim, say the first row and the first column and then loop row 0 and column 0 to zero out accordingly?

In a MXN matrix, We will take column 0 to mark if the row [0, M-1] should be zero out; row 0 to mark if the
column [0, N-1] should be zero out. There will be an overlap at [0,0] for this approach. So, we will need an
extra variable to avoid the conflict, let's define variable k to store whether row 0 should be zero out, so
[0,0] is saved for tracking if column 0 should be zero out.

Another trick is that you will have to scan and zero out the matrix starting from [M-1, N-1]. By doing so,
the information stored at row 0 and column 0 will be reserved until they need to be zero out if it's necessary.
By the moment, all other cells have been checked, it's safe to overwrite these info. However, if you start from
[0,0], as long as k or/and [0,0] is equal to 0, you will zero out row 0 or/and column 0 so all info will be wiped
out, you will end up an all-zero matrix...

The overall time complexity is O(M*N) and space complexity is O(1)

Here is an example:

k=0
1, 0, 2, 3     0, 0, 2, 3		0, 0, 0, 0
2, 4, 1, 5 --> 2, 4, 1, 5 -->  0, 0, 1, 5
0, 2, 3, 5		0, 2, 3, 5		0, 0, 0, 0
*/
void matrixZeroOut(vector<vector<int> > &A)
{
	int rowLen = A.size();
	assert(rowLen > 0);
	int colLen = A[0].size();
	assert(colLen > 0);
	int k = 1;
	for (int i = 0; i < rowLen; ++i)
	{
		for (int j = 0; j < colLen; ++j)
		{
			if (0 == A[i][j])
			{
				if (0 == i)//row 0 should be zero out
					k = 0;
				else
					A[i][0] = 0;//row i(i>0) should be zero out
				A[0][j] = 0;//column j should be zero out
			}
		}
	}
	for (int i = rowLen - 1; i > 0; --i)
	{
		for (int j = colLen - 1; j >= 0; --j)
		{
			if ((0 == A[i][0] || 0 == A[0][j]))
				A[i][j] = 0;
		}
	}
	if (0 == k)
	{
		for (int j = 0; j < colLen; ++j)
			A[0][j] = 0;
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
void testMatrixZeroOut()
{
	vector<vector<int> > v1({ { 1, 2 }, { 3, 0 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v1);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v1);
	printMatrix(v1);

	vector<vector<int> > v2({ { 1, 0, 2, 3 }, { 2, 4, 1, 5 }, { 0, 2, 3, 5 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v2);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v2);
	printMatrix(v2);

	vector<vector<int> > v3({ { 1, 2, 3, 4 }, { 2, 2, 0, 4 }, { 3, 2, 3, 4 }, { 4, 2, 3, 4 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v3);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v3);
	printMatrix(v3);

	vector<vector<int> > v4({ { 1 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v4);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v4);
	printMatrix(v4);

	vector<vector<int> > v5({ { 0 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v5);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v5);
	printMatrix(v5);

	vector<vector<int> > v6({ { 1, 0 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v6);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v6);
	printMatrix(v6);

	vector<vector<int> > v7({ { 0, 1 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v7);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v7);
	printMatrix(v7);

	vector<vector<int> > v8({ { 1 }, { 0 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v8);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v8);
	printMatrix(v8);

	vector<vector<int> > v9({ { 0 }, { 1 } });
	cout << "Given Matrix:" << endl;
	printMatrix(v9);
	cout << "Zero out Matrix:" << endl;
	matrixZeroOut(v9);
	printMatrix(v9);
}