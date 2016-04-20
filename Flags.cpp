#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingT5HFZA-A7V/
This is the solution using binary search and guarantee linear time complexity. The previous versions
can achive linear in certain cases but can't prove it works for all.

Instead of using the array keeping peaks' indexes to conduct the distance calculation against possible
number of flags 'k', we track the index of next coming peak's index.

The next flag is only valid if the next peak is at least k distance away from the current peak where we
stand on. Starting from index b=0, if we increase b by k steps every interation and set b=nextPeak[b+k],
we can guarantee the next b is on the peak that is at least k distance away from the previous b (last peak).
If b==-1, we know there is no more peaks all the way down to the end of the nextPeak array.

After a closer look, we can even save the extra O(N) space for the new array by reusing the vector A. With
an extra variable to keep A[i+1], we can do this. Therefore, the space complexcity is O(1), not counting the
storage required for input arguments.

This version does need a litte bit more coding but all worth it.

Let examine the time complexity:

"while (l <= h)", binary search, in worst case, take O(lgN) iteration.

For the inner loop, "while (b < len && m < k)", let's break it to two parts:

1. b < len
len is always equal to N, but noted b increased by k every iteration,
it's like "for(int b=0;b<len;b*=ck), 1<=c, so it will take N/k steps to complete. In order to simplify
the problem, since k is always equal to N/2^b (b>=1) in a binary search, this
part of loop will take 2^b to complete in each iteration. We have:

2, 2^2, 2^3, ... , 2^m

Since the outter loop will run log2(N) times, the above geometric sequence will have sum:

2*(1-2^(log2(N))/1-2 = 2(2^(log2(N)-1) = 2(N-1) <=O(N)

2. m < k, k is N/2^b, will form a sequece:

N/2, N/4, N/8, N/16,... , N/2^b,

Given N=2^a, we then have: 2^(a-1), 2^(a-2),2^(a-3)..., 2.

Since the outter loop will run log2(N) times, the above geometric sequence will have sum:

2*(1-2^(log2(N))/1-2 = 2(2^(log2(N)-1) = 2(N-1) <=O(N)

Therefor the overall time complexity is O(N).

Actually, considering the fact both conditions apply on the loop, it's very likely forcing the loop to
exit even earlier. When one condition is: 2, 2^2, 2^3; the other one is 2^(n-1), 2^(n-2), 2

We could guess when k=sqrt(N), we should observe the worst case, considering the example:

N=8, then k=2^1.5

"b < len" condition will take N/k times ==> 8/2^1.5 = 2^1.5

"m < k" condition will take 2^1.5 times as well

Both of them will take less than log2(8)=3.

So it's possible in the worst case, the inner loop will run O(log2(N)). Then we could say the overall
is O(lgN*log2(N)) ==> O(lgN*lgN)
*/
int solutionFlags(vector<int> &A)
{
	int len = A.size(), maxcount = 0, k;
	assert(len > 0);
	if (1 == len)return 0;
	k = A[len - 1];
	A[len - 1] = -1;
	for (int i = len - 2; i > 0; --i)
	{
		if (A[i] > A[i - 1] && A[i] > k)
		{
			k = A[i];
			A[i] = i;
		}
		else
		{
			k = A[i];
			A[i] = A[i + 1];
		}
	}
	A[0] = A[1];
	int l = 1, h = len - 1, m, b;
	while (l <= h)
	{
		k = l + (h - l) / 2;
		b = 0, m = 0; int count = 0;
		while (b < len && m < k)
		{
			if ((b = A[b]) == -1)
				break;
			++m;
			b += k;
		}
		maxcount = std::max(maxcount, m);
		if (k - m > 0)
			h = k - 1;
		else
			l = k + 1;
	}
	return maxcount;
}
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
int solutionFlags2(vector<int> &A)
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
    vector<int> v = { 1, 5, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2 };	
    cout << "Expect 3: " << solutionFlags(v) << endl;
    v = { 1 };
    cout << "Expect 0: " << solutionFlags(v) << endl;
    v = { 1, 2 };
    cout << "Expect 0: " << solutionFlags(v) << endl;
    v = { 1, 2, 1 };
    cout << "Expect 1: " << solutionFlags(v) << endl;
    v = { 1, 2, 1, 3, 1 };
    cout << "Expect 2: " << solutionFlags(v) << endl;
    v = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 };
    cout << "Expect 5: " << solutionFlags(v) << endl;
    v = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 };
    cout << "Expect 4: " << solutionFlags(v) << endl;
    v = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 };
    cout << "Expect 3: " << solutionFlags(v) << endl;
    v = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1 };
    cout << "Expect 2: " << solutionFlags(v) << endl;
    v = { 1, 2, 3, 4, 5, 6, 1 };
    cout << "Expect 1: " << solutionFlags(v) << endl;
    v = { 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1 };
    cout << "Expect 4: " << solutionFlags(v) << endl;
}
