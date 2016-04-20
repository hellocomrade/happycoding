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
int solutionPeaks1(const vector<int> &A)
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

int solutionPeaks2(const vector<int> &A)
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
int solutionPeaks3(const vector<int> &A) {
	int len = A.size();
	if (len<3)return 0;
	int d = 2, itor;
	vector<int> lastPeak(len, len);
	for (int i = 1; i<len - 1; ++i)
	{
		lastPeak[i] = lastPeak[i - 1];
		if (A[i]>A[i - 1] && A[i]>A[i + 1])
			lastPeak[i] = i;
	}
	lastPeak[len - 1] = lastPeak[len - 2];
	while (d <= len)
	{
		if (0 == len%d)
		{
			itor = d;//each group has d elements
			//the lastpeak at the last index in the current group should be no greater than the last index
			//in the current group but also greater than the last index in the last group
			while (itor <= len&&lastPeak[itor - 1]<itor&&lastPeak[itor - 1]>itor - d - 1)
				itor += d;
			//If proposed d goes through, we should expect itor==len+d
			//return immediately once we have a match coz we are looking for the max number of group and the
			//first match of len/d is guaranteed to be the one (d starts from 2)
			if (itor>len)
				return len / d;
		}
		++d;
	}
	return 0;
}
int solutionPeaks(const vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int i = 1, d = 2, lastPeakIdx = 0, cnt;
	vector<int> lastPeaks(len, 0);
	//instead of check indexes for peaks, we store the last peak at each index for the sequence.
	//This is like memorization. Given an index in [0, len-1], we can tell the index of the last peak
	//in the sequence. We use 0 as the missing value since peak can't exist at 0 or len - 1. 
	while (i < len)
	{
		//The following line helps to save couple lines of code. We assign lastPeaks[i] with the value
		//at i-1 regardless what the actually value should be at i. Then we check if i has a peak.
		//If so, we update the value at i. By doing so, we don't have a temp value for the lastPeakIndex
		//and also, no need for an else branch.
		lastPeaks[i] = lastPeaks[i - 1];
		if ((i + 1) < len && A[i] > A[i - 1] && A[i] > A[i + 1])
			lastPeaks[i] = i;
		++i;
	}
	while (d <= len)
	{
		if (0 == len % d)
		{
			lastPeakIdx = 0;
			cnt = 0;
			for (i = d; i <= len; i += d)
			{
				//if there is no peak (lastpeakidx == 0) or peak index doesn't change
				//after we move to the next interval by +d, break and move on.
				if (lastPeaks[i - 1] == lastPeakIdx)
					break;
				else
				{
					lastPeakIdx = lastPeaks[i - 1];
					++cnt;
				}
			}
			if (cnt == len / d)
				return cnt;
		}
		++d;
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
