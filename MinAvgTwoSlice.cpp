//https://codility.com/demo/results/training4M2QEN-3PD/
#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * Naive solution
 */
int solutionMinAvgTwoSlice(vector<int> &A)
{
    int len = A.size() - 1;
    assert(len>0);
    double avgminsofar = (A[0] + A[1])/2.0;
    double minendhere = (A[0] + A[1]);
    double tmp, tmp1;
    int sidx = 0, minidx = 0, cnt = 2;
    for (int i = 1; i<len; ++i)
    {
	tmp = (A[i] + A[i + 1]) / 2.0;
	tmp1 = (minendhere + A[i + 1]) / (cnt + 1);
	if (tmp < tmp1 && tmp < minendhere / cnt)
	{
	    minendhere = (A[i] + A[i + 1]);
	    sidx = i;
	    cnt = 2;
	}
	else if (tmp1 < tmp && tmp1 < minendhere / cnt)
	{
	    minendhere += A[i + 1];
	    ++cnt;
	}
	else
	{
	    minendhere = std::numeric_limits<double>::max();
	    cnt = 1;
	    --i;
	}
	if (avgminsofar>minendhere / cnt)
	{
		minidx = sidx;
		avgminsofar = minendhere / cnt;
	}
    }
    return minidx;
}
void testMinAvgTwoSlice()
{
    cout << "Expect 1: " << solutionMinAvgTwoSlice(vector<int>({ 4, 2, 2, 5, 1, 5, 8 })) << endl;
    cout << "Expect 1: " << solutionMinAvgTwoSlice(vector<int>({ 4, -2, 2, 5, 1, 5, 8 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ 4, 2 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -4, -2, -1, -3 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -1, -1, -1, -1 })) << endl;
    cout << "Expect 2: " << solutionMinAvgTwoSlice(vector<int>({ -1, -2, -3, -4 })) << endl;
    cout << "Expect 2: " << solutionMinAvgTwoSlice(vector<int>({ -3, -5, -8, -4, -10 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -8, -4, -10 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ 4, -10, 5, 10, -5, 8 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -1, -1, 0, 0, -1, -1, -1 })) << endl;
}	 
