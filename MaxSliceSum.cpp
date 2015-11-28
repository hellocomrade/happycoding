//https://codility.com/programmers/task/max_slice_sum
#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//classic max sub array
int solutionMaxSliceSum(vector<int> &A) {
    int len = A.size();
    assert(len > 0);
    //integer overflow is possible, long long is the safe choice since it's guaranteed to be 8 bytes
    //long, however, could still be 4 bytes on Windows even it's x64 
    long long maxhere = 0, maxsofar = INT_MIN, tmp;
    for (int i : A)
    {
	tmp = maxhere + i;
	//update maxsofar first and then maxhere to make sure negative max value can be stored properly
	maxsofar = std::max(maxsofar, tmp);
	maxhere = std::max(0ll, tmp);
    }
    return static_cast<int>(maxsofar);
}
void testMaxSliceSum()
{
	cout << "Expect 5: " << solutionMaxSliceSum(vector<int>({ 3, 2, -6, 4, 0 })) << endl;
	cout << "Expect 6: " << solutionMaxSliceSum(vector<int>({ 0, 1, 2, 3, -5, -8 })) << endl;
	cout << "Expect 0: " << solutionMaxSliceSum(vector<int>({ 0 })) << endl;
	cout << "Expect -1: " << solutionMaxSliceSum(vector<int>({ -1 })) << endl;
	cout << "Expect 1: " << solutionMaxSliceSum(vector<int>({ 1 })) << endl;
	cout << "Expect 25: " << solutionMaxSliceSum(vector<int>({ 8, 7, -3, 6, -2, 9 })) << endl;
	cout << "Expect -1: " << solutionMaxSliceSum(vector<int>({ -3, -1, -3, -6, -2, -9 })) << endl;
	cout << "Expect -1: " << solutionMaxSliceSum(vector<int>({ -1, -1, -3, -6, -2, -9 })) << endl;
	cout << "Expect 0: " << solutionMaxSliceSum(vector<int>({ -1, -1, -3, 0, -6, -2, -9 })) << endl;
	cout << "Expect 0: " << solutionMaxSliceSum(vector<int>({ 0, -1, 0, 0, -6, -2, -9 })) << endl;
	cout << "Expect 1: " << solutionMaxSliceSum(vector<int>({ 0, -1, 0, 1, -6, -2, -9 })) << endl;
}


