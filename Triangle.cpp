//https://codility.com/demo/results/trainingP2BFAD-DVQ/
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
/*
Observations:
1. Only ask to return if such a triple exists, no need to find every possible triple;
2. If we sort the array in non decending order, it might facilite the identification;
3. If the array is sorted, we can easily drop all elements that are no greater than 0.
   Because the sum of two smaller elements that are no greater than 0, is always less than
   the largest of three. For example: [-10, -5, -1], [0, 5, 6]
   So we actually only need to look at the elements that are greater than 0;
4. In fact, there is no need to examine all three required condition. Because in an array
   with non decending order, A[i+2]+A[i+1] is always greater than A[i], same reason,
   A[i] + A[i+2] is always greater than A[i+1];
5. Possible overflow since we could have sum two really large/small integers. For example:
   [2147483645, 2147483646, 2147483647]. So "long long" is necessary. Remeber to convert
   integer to long long before addition. The conversion on the result of sum will not work.
   If you do so, only the overflowed value will be converted to long long.
   Actually, you can avoid this trouble by simply using substraction since we won't allow any
   negative integer showing up anyway.
*/
int solutionTriangle(vector<int> &A)
{
	int len = A.size();
	if (len < 3)
		return 0;
	len -= 2;
	sort(A.begin(), A.end());
	for (int i = 0; i < len; ++i)
	{
		//if (A[i] > 0 && (long long)A[i] + (long long)A[i + 1] > A[i + 2] && (long long)A[i + 2] + (long long)A[i] > A[i + 1])
		if (A[i] > 0 && A[i] > A[i + 2] - A[i + 1])
			return 1;
	}
	return 0;
}
void testTriangle()
{
	cout << "Expect 1: " << solutionTriangle(vector<int>({ 10 ,2, 5, 1, 8, 20 })) << endl;
	cout << "Expect 0: " << solutionTriangle(vector<int>({ 10, 50, 5, 1 })) << endl;
	cout << "Expect 0: " << solutionTriangle(vector<int>({})) << endl;
	cout << "Expect 0: " << solutionTriangle(vector<int>({ 10 })) << endl;
	cout << "Expect 0: " << solutionTriangle(vector<int>({ 10, 50 })) << endl;
	cout << "Expect 1: " << solutionTriangle(vector<int>({ 2147483647, 2147483645, 2147483646 })) << endl;
	cout << "Expect 0: " << solutionTriangle(vector<int>({ -1, 5, 6 })) << endl;
	cout << "Expect 0: " << solutionTriangle(vector<int>({ 0, 5, 6 })) << endl;
	cout << "Expect 1: " << solutionTriangle(vector<int>({ -1, 5, 6, 7 })) << endl;
}