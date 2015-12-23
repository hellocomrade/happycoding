#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingWUNYHU-BWR/
https://codility.com/media/train/solution-flags.pdf
*/
int solutionFlags(vector<int> &A)
{
	int len = A.size(), maxcount = 0, k;
	assert(len > 0);
	vector<int> peaks;
	for (int i = 1; i < len - 1; ++i)
	{
		if (A[i] > A[i - 1] && A[i] > A[i + 1])
			peaks.push_back(i);
	}
	len = peaks.size();
	if (len == 1)
		return 1;
	if (len > 1)
	{
		maxcount = 2;
		int l = 2, h = peaks[len - 1] - peaks[0], m, b = 0;
		while (l <= h)
		{
			k = m = l + (h - l) / 2;
			--m;
			for (int i = 1; m > 0 && i < len; ++i)
			{
				if (peaks[i] - peaks[b] >= k)
				{
					--m;
					b = i;
				}
			}
			maxcount = std::max(maxcount, k - std::max(m, 0));
			if (m > 0)
				h = k - 1;
			else
				l = k + 1;
			b = 0;
		}
	}
	return maxcount;
}
void testFlags()
{
	cout << "Expect 3: " << solutionFlags(vector<int>({ 1, 5, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2 })) << endl;
	cout << "Expect 0: " << solutionFlags(vector<int>({ 1 })) << endl;
	cout << "Expect 0: " << solutionFlags(vector<int>({ 1, 2 })) << endl;
	cout << "Expect 1: " << solutionFlags(vector<int>({ 1, 2, 1 })) << endl;
	cout << "Expect 2: " << solutionFlags(vector<int>({ 1, 2, 1, 3, 1 })) << endl;
	cout << "Expect 5: " << solutionFlags(vector<int>({ 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 })) << endl;
	cout << "Expect 4: " << solutionFlags(vector<int>({ 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 })) << endl;
	cout << "Expect 3: " << solutionFlags(vector<int>({ 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 })) << endl;
	cout << "Expect 2: " << solutionFlags(vector<int>({ 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 })) << endl;
	cout << "Expect 1: " << solutionFlags(vector<int>({ 1, 2, 3, 4, 5, 6, 1 })) << endl;
	cout << "Expect 4: " << solutionFlags(vector<int>({ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1 })) << endl;
}