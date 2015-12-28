#include <cassert>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

/*
Given a sequence with N(N>0) number, find the elements occuring more than k times (k<=N)

A variation of "Boyer and Moore's Linear Time Voting Algorithm", aka leading number or majority.

Instead of O(1), we need O(len/(k+1)) space (there will be never more than len/(k+1) elements that
could occur more than k times. More than k means at least k+1 times. Otherwise, the total number of
elemetns will be more than N). The extra space will be used to track all possible candidates.

We follow the same idea. The difference is: when we see an element that is not on the candidate list,
we will decrease the counts on all candidate by 1. Whenever the count on a candidate is 0, it's out and
will be replaced by the new candidate.

At last, we still have to verify the candidate by actually counting their occurences and see if the count
is more than k.

The overall time complexity O(kN)
*/
vector<int> moreThanKofN(vector<int> &A, int k)
{
	int len = A.size();
	assert(len > 0);
	assert(len >= k);
	std::pair<int, int> empty = std::make_pair(std::numeric_limits<int>::min(), 0);
	//if elements showing up more than k times, there will be at most len/(k+1) such elements
	vector<std::pair<int, int> > stks(len / (k + 1), empty);
	vector<int> result;
	int size = stks.size(), j, m;
	for (int i : A)
	{
		for (j = 0; j < size; ++j)
		{
			if (stks[j].first == i)//see if i is on the stack, if so increase the count by 1
			{
				++stks[j].second;
				break;
			}
		}
		if (j == size)//i is not on the stack
		{
			for (j = 0; j < size; ++j)
			{
				if (0 == stks[j].second)//if there is avaiable spot for i?
				{
					stks[j] = std::make_pair(i, 1);
					break;
				}
			}
			if (j == size)//i is not on stack yet
			{
				for (j = 0; j < size; ++j)
					--stks[j].second;
			}
		}
	}
	for (j = 0; j < size; ++j)
	{
		m = 0;
		for (int i = 0; i < len; ++i)
		{
			if (A[i] == stks[j].first)
				++m;
		}
		if (m > k)
			result.push_back(stks[j].first);
	}
	return result;
}
void testMoreThanKofN()
{
	vector<int> ret1 = moreThanKofN(vector<int>({ 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 4, 4 }), 3);
	cout << "Expect 1,2,3: " << ret1[0] << ',' << ret1[1] << ',' << ret1[2] << endl;

	ret1 = moreThanKofN(vector<int>({ 1, 2, 3, 4, 2, 4, 1, 2, 3, 1, 2, 3, 1, 3, 4 }), 3);
	cout << "Expect 3,2,1: " << ret1[0] << ',' << ret1[1] << ',' << ret1[2] << endl;

	ret1 = moreThanKofN(vector<int>({ 1, 2, 3, 4, 4, 4 }), 3);
	cout << "Expect 0: " << ret1.size() << endl;

	ret1 = moreThanKofN(vector<int>({ 1, 2, 2, 1 }), 1);
	cout << "Expect 1,2: " << ret1[0] << ',' << ret1[1] << endl;

	ret1 = moreThanKofN(vector<int>({ 1, 2, 2, 2, 2, 3, 1 }), 1);
	cout << "Expect 1,2: " << ret1[0] << ',' << ret1[1] << endl;
}