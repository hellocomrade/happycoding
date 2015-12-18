#include <cassert>
#include <vector>
#include <iostream>

using namespace std;
/*
Observation:
1. Since the number of subsequences is identical, we are looking for all divisors of the length of
   the sequence.
2. The divisor should be greater than the smallest peak index ([peak index]+1 is the minimum number 
   of elements that can form a group), any divisor smaller than this can be safely discarded.
3. In each possible divisors, we need to make sure that each group/interval covers at least one peak.
4. Since we scan the divisors from the low end (monotonic, increase order), the first divisor that meets
   the requirement must generate the largest group number. max(len/divisor). Following divsiors, even
   they can pass, each group will have more elements, therefore result in less number of groups.

find all peaks in O(N), then loop through all possible divisors from peak[0]+1 till len, inclusive;
the difference in the following two solution is on how to find out if the current interval with 'divisor'
long is capable to cover at least one peak every time.
*/
int solutionPeaks1(vector<int> &A)
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
		//peaks[0] is not sufficient as a possible divisor, since peaks stores index, it's off by 1
		//in terms of the number of elements
		d = peaks[0] + 1;
		while (d <= len)
		{
			if (0 == len % d)
			{
				//j stores the last max index that the last interval with the lenght of divisor
				//could possibly covered
				j = 0;
				num = d;
				while (j < len1)
				{
					k = j;
					while (j < len1 && num >= peaks[j])
						++j;
					//if the current interval can't cover at least one more peak, we are done.
					if (j > k)
						num += d;
					else
						break;
				}
				//if it passes all tests, the final result should be equal to len+current divisor
				if (num - d == len)
					return len / d;
			}
			++d;
		}
	}
	return 0;
}

int solutionPeaks(vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int i = 1, d, j, len1, cnt;
	vector<int> peaks;
	while (i < len - 1)
	{
		if (A[i] > A[i - 1] && A[i] > A[i + 1])
			peaks.push_back(i);
		++i;
	}
	len1 = peaks.size();
	if (len1 > 0)
	{
		d = peaks[0] + 1;
		while (d <= len)
		{
			if (0 == len % d)
			{
				j = -1;
				cnt = 0;
				//instead of increase the interval based upon current divsor, we could check
				//if there is at least one peak falling into an inteval by peaks[i]/divisor
				//assuming you have a bucket array, each seat represents an interval, we want to
				//make sure no bucket is empty.
				//We need a variable here, j, to store the last bucket number that the last peak
				//is in. We only ++cnt if j value is increased. By the end, if all buckets is occupied,
				//we could expect cnt == len/current divisor, otherwise, cnt < len/d
				for (int k : peaks)
				{
					if (k / d != j)
					{
						++cnt;
						j = k / d;
					}
				}
				if (cnt == len / d)
					return cnt;
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