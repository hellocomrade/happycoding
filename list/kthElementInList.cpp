#include <cassert>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

/*
Implement an algorithm to find the kth to last element of a singly linked list.

Assuming we don't know the size of the list.

Note: k is counting from the tail and start from 0

Observation:
If we keep two iterators fi and si, the distance between them keeps as k, we could:
1. Increase si by 1 in a loop as long as k is postive and si doesn't reach the end yet;

2. After the loop, if k is greater than 0 but si has already reached the end of the list, we
are sure that there are less than k elements in the list. missing_value is returned;

3. If k is equal to zero, we can find the kth element following two conditions:

	a. If si has reached the end of the list, we know the current fi (the front of the list)
	is the kth element

	b. If si has not reached the end, now we simply increase both fi and si at the same time in
	a new loop until si reaches the end of the list.

	note: in our setup though, item a will never happen, since STL's end() is one position behind
		  the last element of the list. Also, we assume k is 0-based index counting from the tail.
		  So, in the following solution, if si == ei, the k must be an invalid index for the list.
		  If k happens to be len-1, then by the end of the first loop, si is equal to the last element
		  of the list, not end()

time complexity: O(N)
space complexity: O(1)
*/
template<typename T>
T kthElementInList(list<T> &L, int k, int missingvalue)
{
	assert(k >= 0);
	list<T>::const_iterator fi = L.begin();
	list<T>::const_iterator si = fi;
	list<T>::const_iterator ei = L.end();
	++k;
	while (--k > 0 && si != ei)
		++si;
	if (0 == k)
	{
		if (si != ei)
		{
			while (si != ei)
			{
				++si;
				++fi;
			}
			return *(--fi);
		}
	}
	return missingvalue;
}
void testKthElementInList()
{
	vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	list<int> l1;
	l1.insert(l1.begin(), v1.begin(), v1.end());
	cout << "Expect 6: " << kthElementInList(l1, 4, -1) << endl;
	cout << "Expect -1: " << kthElementInList(l1, 11, -1) << endl;
	cout << "Expect 1: " << kthElementInList(l1, 9, -1) << endl;
	cout << "Expect 9: " << kthElementInList(l1, 1, -1) << endl;
	cout << "Expect 10: " << kthElementInList(l1, 0, -1) << endl;

	vector<int> v2 = { 1 };
	list<int> l2;
	l2.insert(l2.begin(), v2.begin(), v2.end());
	cout << "Expect -1: " << kthElementInList(l2, 4, -1) << endl;
	cout << "Expect 1: " << kthElementInList(l2, 0, -1) << endl;
	cout << "Expect -1: " << kthElementInList(l2, 1, -1) << endl;

	vector<int> v3 = { 1, 2 };
	list<int> l3;
	l3.insert(l3.begin(), v3.begin(), v3.end());
	cout << "Expect 1: " << kthElementInList(l3, 1, -1) << endl;
	cout << "Expect 2: " << kthElementInList(l3, 0, -1) << endl;
	cout << "Expect -1: " << kthElementInList(l3, 2, -1) << endl;

	vector<int> v4 = { 1, 2, 3 };
	list<int> l4;
	l4.insert(l4.begin(), v4.begin(), v4.end());
	cout << "Expect 2: " << kthElementInList(l4, 1, -1) << endl;
	cout << "Expect 3: " << kthElementInList(l4, 0, -1) << endl;
	cout << "Expect 1: " << kthElementInList(l4, 2, -1) << endl;
	cout << "Expect -1: " << kthElementInList(l4, 3, -1) << endl;
	cout << "Expect -1: " << kthElementInList(l4, 1000, -1) << endl;
}