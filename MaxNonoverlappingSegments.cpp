#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingH2D7D7-9EQ/

Observations:
1. First, edge conditions: if vectors are empty, return 0; if there is only one segment or all segments
are overlapping, we should return 1 since you can always pick 1 segment and claim it's the max nonoverlapping
segment in the group;
2. segments are sorted by end point, so we should scan the vector and compare A[i] with B[i - 1], if A[i] is greater
we have found two nonoverlapping segments at least;
3. We could use the extra O(N) space to track the previous B[j] if the current A[i] is not greater than B[i -1]. This
intuitive thought will work for the case like [2,7], [4,9], [3,10], [10,11], note [4,9] and [10,11] are not
overlapped. However, this trick will not work for [0,3], [2,5], [2, 8], [4,10]!
4. For te latter case, we found that this tracking array should keep the smallest B[j] since an overlapping
event is found. If a nonoverlapping event is found at index i, we shall reset tracking[i] to -1 to stop the
propagation.
*/
int solutionMaxNonoverlappingSegments(const vector<int> &A, const vector<int> &B)
{
	int len1 = A.size();
	if (0 == len1)return 0;
	int cnt = 1;
	vector<int> lastCmp = vector<int>(len1, -1);
	for (int i = 1; i < len1; ++i)
	{
		if (A[i] > B[i - 1] || (-1 != lastCmp[i - 1] && A[i] > lastCmp[i - 1]))
			++cnt;
		else
			lastCmp[i] = -1 != lastCmp[i - 1] ? lastCmp[i - 1] : B[i - 1];
	}
	return cnt;
}
void testMaxNonoverlappingSegments()
{
	cout << "Expect 0: " << solutionMaxNonoverlappingSegments(vector<int>{}, vector<int>{}) << endl;
	cout << "Expect 1: " << solutionMaxNonoverlappingSegments(vector<int>{1}, vector<int>{1}) << endl;
	cout << "Expect 2: " << solutionMaxNonoverlappingSegments(vector<int>{0, 2, 2, 4}, vector<int>{3, 5, 8, 10}) << endl;
	cout << "Expect 4: " << solutionMaxNonoverlappingSegments(vector<int>{0, 2, 2, 4, 22, 26, 20}, vector<int>{3, 5, 8, 10, 24, 28, 30}) << endl;
	cout << "Expect 3: " << solutionMaxNonoverlappingSegments(vector<int>{2, 4, 3, 10, 16, 0}, vector<int>{7, 9, 10, 11, 18, 20}) << endl;
	cout << "Expect 2: " << solutionMaxNonoverlappingSegments(vector<int>{2, 4, 3, 10, 16, 0}, vector<int>{7, 9, 10, 17, 18, 20}) << endl;
	cout << "Expect 1: " << solutionMaxNonoverlappingSegments(vector<int>{4, 3, 0}, vector<int>{9, 10, 12}) << endl;
	cout << "Expect 3: " << solutionMaxNonoverlappingSegments(vector<int>{1, 3, 7, 9, 9}, vector<int>{5, 6, 8, 9, 10}) << endl;
	cout << "Expect 2: " << solutionMaxNonoverlappingSegments(vector<int>{0, 3, 15}, vector<int>{10, 12, 16}) << endl;
	cout << "Expect 3: " << solutionMaxNonoverlappingSegments(vector<int>{0, 3, 15, 17}, vector<int>{10, 12, 16, 18}) << endl;
	cout << "Expect 2: " << solutionMaxNonoverlappingSegments(vector<int>{0, 3, 14, 15}, vector<int>{10, 12, 16, 18}) << endl;
	cout << "Expect 3: " << solutionMaxNonoverlappingSegments(vector<int>{0, 3, 14, 15, 20}, vector<int>{10, 12, 16, 18, 28}) << endl;
	cout << "Expect 2: " << solutionMaxNonoverlappingSegments(vector<int>{2, 4, 3, 10}, vector<int>{7, 9, 10, 12}) << endl;
	cout << "Expect 3: " << solutionMaxNonoverlappingSegments(vector<int>{4, 3, 10, 0, 14}, vector<int>{9, 10, 11, 12, 16}) << endl;
	cout << "Expect 4: " << solutionMaxNonoverlappingSegments(vector<int>{2, 4, 3, 10, 16, 15, 26}, vector<int>{7, 9, 10, 12, 22, 28, 30}) << endl;
	cout << "Expect 3: " << solutionMaxNonoverlappingSegments(vector<int>{2, 4, 3, 10, 11, 15, 26}, vector<int>{7, 9, 10, 12, 22, 28, 30}) << endl;
	cout << "Expect 4: " << solutionMaxNonoverlappingSegments(vector<int>{2, 4, 3, 10, 11, 15, 29}, vector<int>{7, 9, 10, 12, 22, 28, 30}) << endl;
}
