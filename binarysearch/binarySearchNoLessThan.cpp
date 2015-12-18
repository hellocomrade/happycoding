#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
int binarySearchNoLessThan1(vector<T> &A, T k)
{
	int len = A.size();
	assert(len > 0);
	int m, low = 0, high = len - 1;
	while (low < high)
	{
		m = low + (high - low) / 2;
		if (k < A[m])
			high = m;
		else
			low = m + 1;
	}
	if (low == len - 1 && A[low] < k)
		low = len;
	return low - 1;
}
template<typename T>
int binarySearchNoLessThan(vector<T> &A, T k)
{
	int len = A.size();
	assert(len > 0);
	int m, low = 0, high = len - 1;
	while (low < high)
	{
		m = low + (high - low) / 2 + 1;
		if (k >= A[m])
			low = m;
		else
			high = m - 1;
	}
	if (low == 0 && A[low] > k)
		low = -1;
	return low;
}
void testBinarySearchNoLessThan()
{
	//-2, 1, 3, 5, 6, 8, 10
	vector<int> vec1({ 3, 6, 1, 5, -2, 8, 10 });
	std::sort(vec1.begin(), vec1.end());
	cout << "Expect 2: " << binarySearchNoLessThan(vec1, 4) << endl;
	cout << "Expect 0: " << binarySearchNoLessThan(vec1, -2) << endl;
	cout << "Expect -1: " << binarySearchNoLessThan(vec1, -3) << endl;
	cout << "Expect 6: " << binarySearchNoLessThan(vec1, 100) << endl;
	cout << "Expect 3: " << binarySearchNoLessThan(vec1, 5) << endl;
	cout << "Expect 5: " << binarySearchNoLessThan(vec1, 8) << endl;

	vector<int> vec2({ 0 });
	cout << "Expect -1: " << binarySearchNoLessThan(vec2, -1) << endl;
	cout << "Expect 0: " << binarySearchNoLessThan(vec2, 1) << endl;
	cout << "Expect 0: " << binarySearchNoLessThan(vec2, 0) << endl;

	vector<int> vec3({ 3, 6, 6, 4, -2, 8, 6 });
	//-2, 3, 4, 6, 6, 6, 8
	std::sort(vec3.begin(), vec3.end());
	cout << "Expect 2: " << binarySearchNoLessThan(vec3, 5) << endl;
	cout << "Expect 5: " << binarySearchNoLessThan(vec3, 7) << endl;

	vector<int> vec4({ 0, 10 });
	cout << "Expect -1: " << binarySearchNoLessThan(vec4, -1) << endl;
	cout << "Expect 0: " << binarySearchNoLessThan(vec4, 5) << endl;
	cout << "Expect 1: " << binarySearchNoLessThan(vec4, 100) << endl;
}