#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

//https://codility.com/demo/results/trainingWTZKEB-DY6/
/*
1. CountTriangles
Count the number of triangles that can be built from a given set of edges.
Task description
A zero-indexed array A consisting of N integers is given. A triplet (P, Q, R) is triangular if it is possible to build a triangle with sides of lengths A[P], A[Q] and A[R]. In other words, triplet (P, Q, R) is triangular if 0 ≤ P < Q < R < N and:

A[P] + A[Q] > A[R],
A[Q] + A[R] > A[P],
A[R] + A[P] > A[Q].
For example, consider array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 12
There are four triangular triplets that can be constructed from elements of this array, namely (0, 2, 4), (0, 2, 5), (0, 4, 5), and (2, 4, 5).

Write a function:

int solution(vector<int> &A);
that, given a zero-indexed array A consisting of N integers, returns the number of triangular triplets in this array.

For example, given array A such that:

  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 12
the function should return 4, as explained above.

Assume that:

N is an integer within the range [0..1,000];
each element of array A is an integer within the range [1..1,000,000,000].
Complexity:

expected worst-case time complexity is O(N2);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.

Observations:
https://codility.com/media/train/13-CaterpillarMethod.pdf
Tutorial has the best solution. However, it sets the third edge first and then loop on the second edge, which is counter-intutive for me.
I would rather use the caterpillar method in its plain style, which is defining the second and third edges first then loop both of them
together. We see 3 loops here. But it's still O(N^2) since we loop j and k together by the following observation:

If A[i] + A[j] > A[k], then A[i] + A[j + 1] > A[k] given j + 1 < k. Therefore, if j is increased by 1, we don't have to move k back to j + 1,
we are sure from current j to (k - 1) meets the requirement of building a triangle, we only need to check from k to len - 1 at most.

When the most inner loop exits, we calculate the distance between k and j (off by 1 since current k is either equal to len or meets
A[i] + A[j] <= A[k]). After that, we increase j by 1 but DO NOT reset k.

Be aware we count all duplicate cases as valid.
*/
int solutionCountTriangles(vector<int> &A) {
    int len = static_cast<int>(A.size()), j = 0, k = 0, ans = 0;
    std::sort(A.begin(), A.end());
    for(int i = 0; i < len - 2; ++i) {
        j = i + 1;
        k = j + 1;
        while(j < len - 1) {
            while(k < len && A[i] + A[j] > A[k])++k;
            ans += k - 1 - j++;
        }
    }
    return ans;
}
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
int solutionCountTriangles1(vector<int> &A)
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
	vector<int> v = {};
	cout << "Expect 0: " << solutionCountTriangles(v) << endl;
	v = { 10 };
	cout << "Expect 0: " << solutionCountTriangles(v) << endl;
	v = { 10, 2 };
	cout << "Expect 0: " << solutionCountTriangles(v) << endl;
	v = {10, 2, 5};
	cout << "Expect 0: " << solutionCountTriangles(v) << endl;
	v = { 10, 2, 5, 1, 8, 12 };
	cout << "Expect 4: " << solutionCountTriangles(v) << endl;
}
