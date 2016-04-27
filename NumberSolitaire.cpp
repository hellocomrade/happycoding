#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

//https://codility.com/demo/results/trainingCQPPCD-68K/
//https://codility.com/demo/results/trainingRVF2WH-DQD/
/*
NumberSolitaire
Observations:
A long text description though, it's kind of basic for DP still. Everyone who has read about DP sohuld get this done
in about 10 minutes.

If you are smart enough, you may realize that the space complexity is actually O(1) considering the fact that we only
need to memorize the last 6 elements.However, you will have to be good at '%' trick...
*/
int solutionNumberSolitaire(const vector<int> &A) {
	int len = A.size();
	vector<long> memo(len, numeric_limits<long>::min());
	memo[0] = A[0];
	for (int i = 1; i < len; ++i)
	{
		for (int j = 1; j < 7; ++j)
		{
			if (i - j >= 0)
				memo[i] = std::max(memo[i], A[i] + memo[i - j]);
		}
	}
	return memo[len - 1];
}
int solutionNumberSolitaire1(const vector<int> &A) {
	int magic = 6;
	int len = A.size();
	vector<long> memo(magic, numeric_limits<long>::min());
	memo[0] = A[0];
	for (int i = 1; i < len; ++i)
	    memo[i % magic] = *std::max_element(memo.begin(), memo.end()) + A[i];
	return memo[(len - 1) % magic];
}
void testNumberSolitaire()
{
	assert(8 == solutionNumberSolitaire1(vector<int>{ 1, -2, 0, 9, -1, -2 }));
	assert(-9999 == solutionNumberSolitaire1(vector<int>{ 1, -10000 }));
	assert(0 == solutionNumberSolitaire1(vector<int>{ -1, -2, -3, -4, -5, 1 }));
	assert(-2 == solutionNumberSolitaire1(vector<int>{ -1, -2, -3, -4, -5, -6, -7, 1 }));
}