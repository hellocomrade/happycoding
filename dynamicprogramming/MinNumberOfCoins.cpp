#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

int MinNumberOfCoins(unsigned int K, vector<unsigned int> &A)
{
	int len = A.size();
	int empty = -1;
	assert(len > 0 && K > 0 && A[0] <= K);
	//std::sort(A.begin(), A.end());
	vector<int> memo = vector<int>(K + 1, empty);
	memo[0] = 0;
	//for (int i = A[0]; i <= K; ++i)
	for (int i = 1; i <= K; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			if (i >= A[j] && empty != memo[i - A[j]])
				memo[i] = (empty == memo[i]) ? memo[i - A[j]] + 1 : std::min(memo[i], memo[i - A[j]] + 1);
		}
	}
	return memo[K];
}
void testMinNumberOfCoins()
{
	cout << "Expect 4: " << MinNumberOfCoins(7, vector<unsigned int>{2, 1}) << endl;
	cout << "Expect 2: " << MinNumberOfCoins(11, vector<unsigned int>{9, 6, 5, 1}) << endl;
	cout << "Expect 2: " << MinNumberOfCoins(60, vector<unsigned int>{30, 40, 10}) << endl;
	cout << "Expect -1: " << MinNumberOfCoins(55, vector<unsigned int>{30, 40, 10}) << endl;
}