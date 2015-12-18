#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * This demonstrate a slightly but subtle difference on boundary check as well as high, low are moved.
 * We have a strict comparsion for while: low < high, instead of normal low <= high.
 * and
 * instead of saving the final result in a separte variable, we take the value in low.
 *
 * Since mid=low+(high-low)/2, this will always push mid to the lower bound of [low, high] due to integer
 * division round-up. Taking low as the result will work for all cases except for the k that is greater than
 * the last elem in A since low is equal to high, which gives a false for while condition (low<high).
 * So an extra sanitary check is necessary just for this scenario...
 *
 * What's the benefit of doing this since it requires extra care, well other than saving space for one extra
 * variable, we will actually have one less loop. This could be trivial, but it might be significant if the cost
 * of loop is expensive, say the predicate inside binary search is costly.
 *
 * */
template<typename T>
int binarySearchNoGreaterThan(vector<T> &A, T k)
{
    int len = A.size();
    assert(len > 0);
    int m, low = 0, high = len - 1;
    while (low < high)
    {
	m = low + (high - low) / 2;
	if (k <= A[m])
	    high = m;
	else
	    low = m + 1;
    }
    if (low == len - 1 && A[low] < k)
  	low = len;
    return low;
}
//Add a plain version
template<typename T>
int binarySearchNoGreaterThan1(vector<T> &A, T k)
{
	int len = A.size();
	int result = len;
	assert(len > 0);
	int m, low = 0, high = len - 1;
	while (low <= high)
	{
		m = low + (high - low) / 2;
		if (k <= A[m])
		{
			result = m;
			high = m - 1;
		}
		else
			low = m + 1;
	}
	return result;
}
void testBinarySearchNoGreaterThan()
{
    vector<int> vec1({ 3, 6, 1, 5, -2, 8, 10 });
    std::sort(vec1.begin(), vec1.end());
    cout << "Expect 3: " << binarySearchNoGreaterThan(vec1, 4) << endl;
    cout << "Expect 0: " << binarySearchNoGreaterThan(vec1, -2) << endl;
    cout << "Expect 7: " << binarySearchNoGreaterThan(vec1, 100) << endl;
    cout << "Expect 3: " << binarySearchNoGreaterThan(vec1, 5) << endl;
    cout << "Expect 5: " << binarySearchNoGreaterThan(vec1, 8) << endl;
	
    vector<int> vec2({ 0 });
    cout << "Expect 0: " << binarySearchNoGreaterThan(vec2, -1) << endl;
    cout << "Expect 1: " << binarySearchNoGreaterThan(vec2, 1) << endl;
    cout << "Expect 0: " << binarySearchNoGreaterThan(vec2, 0) << endl;

    vector<int> vec3({ 3, 6, 6, 4, -2, 8, 6 });
    std::sort(vec3.begin(), vec3.end());
    cout << "Expect 3: " << binarySearchNoGreaterThan(vec3, 5) << endl;
    cout << "Expect 6: " << binarySearchNoGreaterThan(vec3, 7) << endl;

    vector<int> vec4({ 0, 10 });
    cout << "Expect 0: " << binarySearchNoGreaterThan(vec4, -1) << endl;
    cout << "Expect 1: " << binarySearchNoGreaterThan(vec4, 5) << endl;
    cout << "Expect 2: " << binarySearchNoGreaterThan(vec4, 100) << endl;
}
