#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/programmers/task/odd_occurrences_in_array/

classic XOR algorithm

Given M as a non-negative integer
0^M = M, M^M = 0

Consider the following sequence:

1,2,2,1,3

 001
^010
------
 011
^010
------
 001
^001
------
 000
^011
------
 011	= 3

For the integer with even numbr of occurrences, the bits for the integers will be flipped even times.
Therefore, by the end of the operations, they will all be zero out. On the other hand, for the only
integer with odd number of occurrences, its value will remain.
*/
int solutionOddOccurrencesInArray(vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int num = 0;
	for (int i : A)
		num ^= i;
	return num;
}
void testOddOccurrencesInArray()
{
	cout << solutionOddOccurrencesInArray(vector<int>({ 9, 3, 9, 3, 9, 7, 9 })) << endl;
}