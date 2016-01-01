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
