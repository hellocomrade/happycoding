#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingWUNYHU-BWR/
https://codility.com/media/train/solution-flags.pdf
Observation:
1. There should be no more than N/2 peaks in any sequence and take at most sqrt(N) flags on peaks.
2. If there is only one peak in the sequence, the default result should be 1.
3. If taking k flags can put flags on m peaks, k-1, k-2 , K-3...1 can do m-1, m-2, m-3...1. So we are looking for the
largest k that can get m flags onto peaks. If you take more than k flags, however, due to the constriction on the
fact that "the distance between any two flags should be greater than or equal to k", there will be less than m flags
on peaks.
4. The upper boundary of k could be set to len, which is the number of peaks. The lower boundary is 2,
if we ignore taking 1 flag, which is always doable. The low bound is 2 because the distance between peaks is always no
less than 2.
5. It appears we can always greedily put a flag on the first peak.

Applied the binary search here:

We have a monotonic sequence here on the number of flags [2, N/2]. The condition to drop half of the sequence,
however, is the fact that, if we take m flags over all peaks and have n flags left, we could take less flags and have less than n flags
left after going through all peaks.

Therefore, finding all peaks takes O(N) time and O(N) space.

The binary search we conduct, well, if done in recursion, we would have:

T(N)=1*T(N/2)+N^1

According to the Master Theorem, log2(1) = 0 < 1, we will have T(N)=BigTheta(N^1)=BigTheta(N)
*/
int solutionFlags1(vector<int> &A)
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
/*
https://codility.com/demo/results/trainingTCBBPG-R5P/
Redo this task with the same binary search algorithm described above.
Make correction: the upper boundary of the binary search is len, which is the number of peaks in the sequence.
There are at most sqrt(N) peaks in a sequence with N elements.

The lower boundary is still 2, since the minimum distance between two neighbor peaks is 2. So given 2 flags,
we are sure they can both be put on peaks as long as there are more than 1 peak in the sequence.
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
		int l = 2, h = len, m, b = 0;
		while (l <= h)
		{
			k = l + (h - l) / 2;
			b = 0, m = 1;
			for (int i = 1; m < k && i < len; ++i)
			{
				if (peaks[i] - peaks[b] >= k)
				{
					++m;
					b = i;
				}
			}
			maxcount = std::max(maxcount, m);
			if (k - m > 0)
				h = k - 1;
			else
				l = k + 1;
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
