#include <cassert>
#include <vector>
#include <deque>
#include <iostream>

using namespace std;

/*
https://codility.com/media/train/14-GreedyAlgorithms.pdf

Trainning question for greedy algorithm

Problem: There are n > 0 canoeists weighing respectively 1 <= W0 <= W1 <= . . . <= Wn−1 <= 10^9

The goal is to seat them in the minimum number of double canoes whose displacement (the
maximum load) equals k. You may assume that Wi <= k.

There are two O(N) solutions:

Solution A O(N): The task can be solved by using a greedy algorithm. The heaviest canoeist
is called fatso. Other canoeists who can be seated with fatso in the canoe are called skinny.
All the other remaining canoeists are also called fatsos.

The idea is that, for the heaviest fatso, we should find the heaviest skinny who can be
seated with him. So, we seat together the heaviest fatso and the heaviest skinny. Let us note
that the thinner the heaviest fatso is, the fatter skinny can be. Thus, the division between
fatso and skinny will change over time — as the heaviest fatso gets closer to the pool of
skinnies.
*/
int solutionCanoeists1(vector<int> &A, const int K)
{
	int len = A.size();
	assert(len > 0 && K > 0);
	int canoe = 0, last = A[len - 1];
	assert(last <= K);
	deque<int> skinny = deque<int>();
	deque<int> fatso = deque<int>();
	//noted that the vector is stored already. So both deques are sorted since we populate
	//them sequentially in a non decreasing order.
	for (int i = 0; i < len; ++i)
	{
		assert(A[i] <= K);
		//If A[i] + A[len - 1] is no greater than K, A[i] is defined as skinny
		//This also indicate if A[i] and A[len - 1] can be seated in a canoe, any other fatso can also
		//be seated together with A[i].
		if (A[i] + last <= K)
			skinny.push_back(A[i]);
		else
			fatso.push_back(A[i]);
	}
	fatso.push_back(last);
	while (!fatso.empty() || !skinny.empty())
	{
		//If there is no skinny available, only fatso can be poped,
		//that's fine. It means this canoe is seated by a fatso only, no skinny is able to share it.
		if (!skinny.empty())
			skinny.pop_back();
		fatso.pop_back();
		++canoe;
		//If fatso is empty, we pop the skinny from right, which is the heaviest skinny and push
		//it to fatso.
		if (fatso.empty() && !skinny.empty())
		{
			fatso.push_back(skinny.back());
			skinny.pop_back();
		}
		//if there are more than 1 fatso in deque, since the previous assumption is based upon the
		//previous heaviest fatso that has been poped already, we have to rebalance the two deques
		//by examining the current fatso, which is the same procedure in the previous for loop.
		while (fatso.size() > 1 && fatso.front() + fatso.back() <= K)
		{
			skinny.push_back(fatso.front());
			fatso.pop_front();
		}
	}
	return canoe;
}
/*
Solution B O(N): The fattest canoeist is seated with the thinnest, as long as their weight is
less than or equal to k. If not, the fattest canoeist is seated alone in the canoe.
*/
int solutionCanoeists2(vector<int> &A, const int K)
{
	int len = A.size();
	assert(len > 0 && K > 0);
	int canoe = 0, i = 0, j = len - 1;
	//when i == j, there is only one canoeist left, so
	//the logic in the loop doesn't make sense for tihs case. However, it doesn't affect the outcome since
	//canoe will be increased by 1 anyway. In this case, it means the last canoeist will be seated alone.
	while (i <= j)
	{
		assert(A[i] <= K && A[j] <= K);
		//if A[i], A[j] can seat together, ++i, --j; Otherwise,
		//only --j
		if (A[i] + A[j] <= K)
			++i;
		--j;
		++canoe;
	}
	return canoe;
}