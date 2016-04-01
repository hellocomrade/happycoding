#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingBUUE4N-CZZ/
https://codility.com/demo/results/trainingYABUCM-DQB/

Observations:
1. If we sort the array, then the problem will be simplified to: for any A[i], A[j], i < j < len, find A[k], j < k < len,
that satisfies A[k] < A[i] + A[j]. This is true because of A[i] <= A[j] <= A[k], then A[j] + A[k] must be greater than A[i],
same for A[k] + A[i];

2. Codility allows O(N) extra space, but don't know how to use it;
3. Since we sort the array, we could apply binary search to find the largest index M in the array that satisfies:
for any k, j < k <= M, have A[i] + A[j] > A[M]. Then we know if A[i] and A[j] are two edges of the triangle, we could
find (M - j) edges in the array for these triangles;
4. The second edition is faster than the first version, since for any given A[i], when we scan from j ,j in [i + 1, len - 1],
low is always based upon the result of the last binary search, which will further narrow the search range.
5. In terms of time complexity, it appears to be O(NlogN) + O(N^2 * logN) --> O(N^2 * logN). Well, if you look at it this way:
since low is in non-decreasing mode for any given i during j moves from i + 1 to len - 1, we can still
say the inner loop, including all junk inside, only takes O(N) time for each outer loop on i.

*/
int solutionCountTriangles(vector<int> &A)
{
	int len = A.size();
	std::sort(A.begin(), A.end());
	int s, ss, l, h, m;
	long long cnt = 0LL;
	for (int i = 0; i < len - 2; ++i)
	{
		ss = i + 2;
		for (int j = i + 1; j < len - 1; ++j)
		{
			l = ss;
			h = len - 1;
			s = -1;
			while (l <= h)
			{
				m = l + (h - l) / 2;
				if (A[m] >= A[i] + A[j])
					h = m - 1;
				else
				{
					s = m;
					l = m + 1;
				}
			}
			if (-1 != s)
			{
				ss = s;
				cnt += s - j;
			}
		}
	}
	return cnt;
}
void testCountTriangles()
{
	cout << "Expect 0: " << solutionCountTriangles(vector<int>{}) << endl;
	cout << "Expect 0: " << solutionCountTriangles(vector<int>{ 10}) << endl;
	cout << "Expect 0: " << solutionCountTriangles(vector<int>{ 10, 2 }) << endl;
	cout << "Expect 0: " << solutionCountTriangles(vector<int>{ 10, 2, 5 }) << endl;
	cout << "Expect 4: " << solutionCountTriangles(vector<int>{ 10, 2, 5, 1, 8, 12 }) << endl;
}