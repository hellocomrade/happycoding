#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingWPCT3R-3GD/
Classic Array rotation, right-hand, left-hand thing, rotate around the axis 3 times
Time complexity: O(N)
Space complexity: O(1);

The only trick is: K could be greater than the size of the sequence, in that case, given Len as the length
of the sequence, assign K = K/Len. Make sure in this case, Len can't be zero, so rule out Len = 0 or 1 first
*/
static inline void swapElems(vector<int> &A, int start, int end)
{
	int tmp = 0;
	while (start < end)
	{
		tmp = A[start];
		A[start++] = A[end];
		A[end--] = tmp;
	}
}
vector<int> solutionCyclicRotation(vector<int> &A, int K)
{
	int len = A.size();
	if (0 == len || 0 == K)
		return A;
	K = K % len;
	swapElems(A, len - K, len - 1);
	swapElems(A, 0, len - K - 1);
	swapElems(A, 0, len - 1);
	return A;
}
static inline void printVector(const vector<int> &A)
{
	for (int i : A)
		cout << i << ", ";
	cout << endl;
}
void testCyclicRotation()
{
	vector<int> A{ 3, 8, 9, 7, 6 };
	solutionCyclicRotation(A, 1);
	cout << "Expect 6, 3, 8, 9, 7: ";
	printVector(A);

	vector<int> A1{ 3, 8, 9, 7, 6 };
	solutionCyclicRotation(A1, 3);
	cout << "Expect 9, 7, 6, 3, 8: ";
	printVector(A1);

	vector<int> A3{ 1, 2, 3, 4, 5 };
	solutionCyclicRotation(A3, 6);
	cout << "Expect 5, 1, 2, 3, 4: ";
	printVector(A3);

	vector<int> A4{ 1, 2, 3, 4, 5 };
	solutionCyclicRotation(A4, A4.size());
	cout << "Expect 1, 2, 3, 4, 5: ";
	printVector(A4);

	vector<int> A5{ 1, 2, 3, 4, 5 };
	solutionCyclicRotation(A5, 12);
	cout << "Expect 4, 5, 1, 2, 3: ";
	printVector(A5);

	vector<int> A6{ 1, 2, 3, 4, 5 };
	solutionCyclicRotation(A6, 11);
	cout << "Expect 5, 1, 2, 3, 4: ";
	printVector(A6);

	vector<int> A7{ 1, 2, 3, 4 };
	solutionCyclicRotation(A7, A7.size());
	cout << "Expect 1, 2, 3, 4: ";
	printVector(A7);

	vector<int> A8{ 1, 2, 3, 4 };
	solutionCyclicRotation(A8, 6);
	cout << "Expect 3, 4, 1, 2: ";
	printVector(A8);

	vector<int> A9{ 1, 2, 3, 4 };
	solutionCyclicRotation(A9, 11);
	cout << "Expect 2, 3, 4, 1: ";
	printVector(A9);
}