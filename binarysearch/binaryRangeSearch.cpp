#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * Finding the position pair (i, i+1) for K in a sorted vector A, at which meets A[i]<K<=A[i+1]
 * if this position can't be found, return (-1,-1)
 * */
template<typename T>
std::pair<int, int> binaryRangeSearch(vector<T> &A, T k)
{
    int len = A.size();
    assert(len > 0);
    int m, low = 0, high = len - 1;
    std::pair<int, int> result = std::make_pair(-1, -1);
    while (low <= high)
    {
	m = low + (high - low) / 2;
	if (k <= A[m])
	{
	    result.second = m;
	    high = m - 1;
	}
	else
	{
	    result.first = m;
	    low = m + 1;
	}
    }
    return result;
}
void testBinaryRangeSearch()
{
    vector<int> vec1({ 3, 6, 1, 5, -2, 8, 10 });
    std::sort(vec1.begin(), vec1.end());
    std::pair<int, int> ret = binaryRangeSearch(vec1, 4);
    cout << "Expect (2, 3): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec1, -2);
    cout << "Expect (-1, 0): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec1, 100);
    cout << "Expect (6, -1): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec1, 5);
    cout << "Expect (2, 3): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec1, 8);
    cout << "Expect (4, 5): (" << ret.first << ", " << ret.second << ")" << endl;

    vector<int> vec2({ 0 });
    ret = binaryRangeSearch(vec2, -1);
    cout << "Expect (-1, 0): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec2, 1);
    cout << "Expect (0, -1): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec2, 0);
    cout << "Expect (-1, 0): (" << ret.first << ", " << ret.second << ")" << endl;

    vector<int> vec3({ 3, 6, 6, 4, -2, 8, 6 });
    std::sort(vec3.begin(), vec3.end());
    ret = binaryRangeSearch(vec3, 5);
    cout << "Expect (2, 3): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec3, 7);
    cout << "Expect (5, 6): (" << ret.first << ", " << ret.second << ")" << endl;
    
    vector<int> vec4({ 0,10 });
    ret = binaryRangeSearch(vec4, -1);
    cout << "Expect (-1, 0): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec4, 5);
    cout << "Expect (0, 1): (" << ret.first << ", " << ret.second << ")" << endl;
    ret = binaryRangeSearch(vec4, 100);
    cout << "Expect (1, -1): (" << ret.first << ", " << ret.second << ")" << endl;
}
