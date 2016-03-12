#include "stdafx.h"
#include <cassert>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;
/*
https://codility.com/demo/results/trainingGY4XYP-XSU/
https://codility.com/demo/results/training27GSKJ-JTQ/

Observation:
It requires a linear algorithm but allows you to use O(M) space and tells you that no elements in the
sequence is larger than M. This gives you the hint to take either a bitset or a hashmap. We will make
the decision later:

Examine the following sequence:

4, 3, 2, 1, 3, 5, 6, 5

If we put a pointer (base) at the start and use another pointer (iterator) to scan the sequence, we will stop at index 3,
since A[4] == A[1]. The subsequence [4, 3, 2, 1] could generate at most 1+2+3+4=10 unique slices. We could
easily generalize this to n*(n+1)/2, given n is the number of elements in the subsequence.

So, can we move the base pointer from index 0 to index 4? it looks we solved this? Wait a minute, if we
do so, we would miss distinct slices [2,1,3]! So, we actullay should move the base pointer to the position
just next to the duplicated element that we have scaned, which is index 2 in the example. OK, we could
only count the subsequence [4,3] using the formula we figured out. Then we moved the iterator back to index 2,
and continue this scan. However, this will not work! Because we are looking for a linear solution! Doing
so will generate a O(N^2) solution.

OK, it appears we have to try to make sure both the base and the iterator only moving forward, no backward, dude! All right,
no big deal!

Assuming we move the base pointer to index 2, and keep the itertor at index 4, then start to scan and stop at the next
duplicate at index 7. We got a subsequence [2,1,3,5,6]. If we use the formula to count the total again and add
them to the count we got at the first stop, what we miss here? We didn't miss, we double count the slices
for [2,1].

4, 3, 2, 1
2, 1, 3, 5, 6

Well, since we can count the total unique slices for any subsequence in O(1). We could do this:
count distinct slices for [4,3,2,1] first and then substract the duplicates count on [2,1] that will be
introduced in the next counting. This will only take O(1) time. Therefore, we can continue this process
and have a linear solution.

Go back to the O(M) space, how should we use it? bitset or hashtable? bitset may seems preferred at the first
glance, however, we soon realize that, in order to implement the algorithm we described above, we need to
track no only the value of the elements we scanned but also their indexes. This requirement rules out bitset,
and hashtable is the only option! So, base pointer moves to the index of the duplicate plus 1 every time scan
stops.

Another small concern: should we clear the hashtable everytime we scan a duplicate element? Not necessary.
Everytime we move the base pointer to its new location, we create a base line. If hashtable returns a hit,
but the index it returns is smaller than the base pointer's index, we know it was from the last run. We
could safely ignore it and put new key-value in.

OK, we now have a solution!

One thing I overlooked is: we have a possibility for integer overflow here. Since N <= 100000, if we do
N*(N+1)/2, it will be an overflow for integer! So, use long long to cover the rear.
*/
int solutionCountDistinctSlices(int M, vector<int> &A)
{
	int len = A.size();
	assert(len > 0 && M >= 0 && M < 100001);
	unordered_map<int, int> map;
	unordered_map<int, int>::const_iterator end = map.end();
	unordered_map<int, int>::const_iterator valueItor;
	long long count = 0, i = 0, j = 0, k;
	while (j < len)
	{
		valueItor = map.find(A[j]);
		if (valueItor == end || valueItor->second < i)
		{
			map[A[j]] = j;
			++j;
		}
		else
		{
			count += (j - i)*(j - i + 1) / 2;
			k = j - valueItor->second - 1;
			count -= k*(k + 1) / 2;
			i = valueItor->second + 1;
			if (count >= 1000000000ll)return 1000000000;
		}
	}
	count += (j - i)*(j - i + 1) / 2;
	return (int)std::min(count, 1000000000ll);
}
void testCountDistinctSlices()
{
	cout << "Expect 11: " << solutionCountDistinctSlices(4, vector<int>({ 3, 4, 3, 4, 3, 4 })) << endl;
	cout << "Expect 9: " << solutionCountDistinctSlices(6, vector<int>({ 3, 4, 5, 5, 2 })) << endl;
	cout << "Expect 5: " << solutionCountDistinctSlices(0, vector<int>({ 0, 0, 0, 0, 0 })) << endl;
	cout << "Expect 6: " << solutionCountDistinctSlices(3, vector<int>({ 1, 2, 3 })) << endl;
	cout << "Expect 10: " << solutionCountDistinctSlices(4, vector<int>({ 1, 2, 3, 4 })) << endl;
	cout << "Expect 1: " << solutionCountDistinctSlices(100, vector<int>({ 1 })) << endl;
	cout << "Expect 9: " << solutionCountDistinctSlices(10, vector<int>({ 3, 8, 8, 1, 2 })) << endl;
	cout << "Expect 9: " << solutionCountDistinctSlices(4, vector<int>({ 3, 4, 3, 4, 3 })) << endl;
	cout << "Expect 14: " << solutionCountDistinctSlices(4, vector<int>({ 3, 4, 5, 3, 4, 3 })) << endl;
	cout << "Expect 12: " << solutionCountDistinctSlices(5, vector<int>({ 3, 4, 5, 3, 4 })) << endl;
	cout << "Expect 25: " << solutionCountDistinctSlices(10, vector<int>({ 1, 10, 7, 6, 1, 9, 2 })) << endl;
	cout << "Expect 5: " << solutionCountDistinctSlices(10, vector<int>({ 10, 1, 10 })) << endl;
	cout << "Expect 7: " << solutionCountDistinctSlices(10, vector<int>({ 1, 10, 1, 10 })) << endl;
	cout << "Expect 23: " << solutionCountDistinctSlices(10, vector<int>({ 1, 10, 7, 6, 1, 10, 2 })) << endl;
	cout << "Expect 23: " << solutionCountDistinctSlices(100000, vector<int>({ 1, 100000, 7, 6, 1, 100000, 2 })) << endl;
	cout << "Expect 10: " << solutionCountDistinctSlices(6, vector<int>({ 3, 4, 5, 5, 5, 2 })) << endl;
	cout << "Expect 8: " << solutionCountDistinctSlices(6, vector<int>({ 3, 4, 5, 5, 5 })) << endl;
	cout << "Expect 12: " << solutionCountDistinctSlices(6, vector<int>({ 3, 4, 3, 5, 6 })) << endl;
	cout << "Expect 15: " << solutionCountDistinctSlices(6, vector<int>({ 4, 3, 2, 3, 5, 6 })) << endl;

	vector<int> vec;
	for (int i = 0; i < 100000; ++i)vec.push_back(i);
	cout << "Expect 1000000000: " << solutionCountDistinctSlices(100000, vec) << endl;
}
