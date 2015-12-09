#include <cassert>
#include <vector>
#include <iostream>

using namespace std;
/*
Given an array of unique integers whose first two numbers are decreasing and 
last two numbers are increasing, find a number in the array which is local minima. 
A number in the array is called local minima if it is smaller than both its left and right numbers.

For example in the array 9,7,2,8,5,6,3,4
2 is a local minima as it is smaller than its left and right number 7 and 8. Similarly 5 is another local minima as it is 
between 8 and 6, both larger than 5.
 */
int localMinima(vector<int>& A)
{
    int len = A.size();
    assert(len > 0);
    int low = 1, high = len - 2, m;
    while (low <= high)
    {
	m = low + (high - low) / 2;
	if (A[m] < A[m - 1] && A[m] < A[m + 1])
	    return A[m];
 	if (A[m] > A[m - 1])
	    high = m - 1;
	else if (A[m] > A[m + 1])
	    low = m + 1;
    }
    if (A[0] < A[1])
	return A[0];
    else if (A[len - 1] < A[len - 2])
	return A[len - 1];
    else
	return -1;
}
void testLocalMinima()
{
	cout << "Expect 1: " << localMinima(vector<int>({ 15, 13, 12, 18, 19, 20, 7, 6, 5, 4, 3, 2, 1 })) << endl;
	cout << "Expect 2: " << localMinima(vector<int>({ 9, 7, 2, 8, 5, 6, 3, 4 })) << endl;
}
