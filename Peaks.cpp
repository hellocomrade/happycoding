#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solutionPeaks(vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int d, i = 1, j, k, len1, num;
	vector<int> peaks;
	while (i < len - 1)
	{
		if (A[i] > A[i - 1] && A[i] > A[i + 1])
			peaks.push_back(i + 1);
		++i;
	}
	len1 = peaks.size();
	if (len1 > 0)
	{
		d = peaks[0];
		while (d <= len)
		{
			if (0 == len % d)
			{
				j = 0;
				num = d;
				while (j < len1)
				{
					k = j;
					while (j < len1 && num >= peaks[j])
						++j;
					if (j > k)
						num += d;
					else
						break;
				}
				if (num - d == len)
					return len / d;
			}
			++d;
		}
	}
	return 0;
}
void testPeaks()
{
	cout << "Expect 3: " << solutionPeaks(vector<int>({ 1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2 })) << endl;
	cout << "Expect 0: " << solutionPeaks(vector<int>({ 1 })) << endl;
	cout << "Expect 0: " << solutionPeaks(vector<int>({ 1, 2 })) << endl;
	cout << "Expect 0: " << solutionPeaks(vector<int>({ 1, 2, 3 })) << endl;
	cout << "Expect 1: " << solutionPeaks(vector<int>({ 1, 2, 1 })) << endl;
	cout << "Expect 2: " << solutionPeaks(vector<int>({ 1, 2, 1, 3, 2, 1 })) << endl;
	cout << "Expect 1: " << solutionPeaks(vector<int>({ 1, 2, 1, 3, 2, 1, 0 })) << endl;
	cout << "Expect 0: " << solutionPeaks(vector<int>({ 1, 2, 3, 4, 5, 6, 7 })) << endl;
	cout << "Expect 2: " << solutionPeaks(vector<int>({ 0, 2, 0, 2, 0, 1, 2, 1 })) << endl;
	cout << "Expect 3: " << solutionPeaks(vector<int>({ 0, 2, 0, 2, 0, 1, 0, 1, 0 })) << endl;
	cout << "Expect 4: " << solutionPeaks(vector<int>({ 1, 2, 1, 0, 4, 1, 1, 2, 1, 4, 6, 2 })) << endl;
	cout << "Expect 4: " << solutionPeaks(vector<int>({ 1, 2, 0, 1, 0, 4, 0, 5, 0, 4, 0, 2 })) << endl;
	cout << "Expect 1: " << solutionPeaks(vector<int>({ 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 4, 5 })) << endl;
	cout << "Expect 2: " << solutionPeaks(vector<int>({ 0, 1, 0, 1, 0, 1, 0, 1, 0, 3, 4, 5 })) << endl;
	cout << "Expect 2: " << solutionPeaks(vector<int>({ 1, 2, 3, 4, 5, 6, 5, 5, 5, 6, 5, 6 })) << endl;
}