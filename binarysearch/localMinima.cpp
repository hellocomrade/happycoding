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


Usually binary search only applies on a monotonic sequence. However, a more profound definition for applying BS is that
we only need a predicate, which could prove for any predicate(x) implies predicate(y) for all y>x, so we can safely drop
hale of the sequence even thought it's no monotonic.

For this local minima problem, think about why the statement says A[0]>A[1], but A[len-2]<A[len-1]? Of course, this will
guarantee we can find a minima. It also gives us a hint: for any given index m, if A[m]>A[m-1], then there must be a local
minima in the range of [low, m-1], if A[m]>A[m+1], then there must be a local minma in the range of [m+1, high]. What if neither
of the conditions are met? Then we are at a local minima.

Note: we only compare A[m] is greater than its neighbor for a reason: if we do A[m]<A[m+1], then we will have to examine
[low, m] for the next loop, which is OK, but you may run into a infinite loop, if you don't have a careful corner case check.
By using greater than comparison only, we can safely use low <= high as the safteguard because either low or high will move 
by 1 in each loop for sure.
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
    cout << "Expect 1: " << solutionNumberOfExtremes(vector<int>({ 10, 1, 5 })) << endl;
}
