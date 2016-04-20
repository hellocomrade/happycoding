#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

/*
Given a value V, if we want to make change for V cents,
and we have infinite supply of each of C = { C1, C2, .. , Cm} valued coins,
what is the minimum number of coins to make the change?

Observation:
1. Vector C is not guaranteed to be sorted, no such assumption;
2. We try a bottom up approach by building the memorization from the smallest possible value, which is the
smallest denomination in C. To find this element, it costs O(N) time;
3. The idea is by checking the previous calculated numbers in memo array, we can tell at value i,
memo[i] = min(memo[i], memo[i - A[j]] + 1), assuming i-A[j] >= 0;
"memo[i - A[j]] + 1" means if denomination j is taken, we transfer the problem to decide the minimum number
of coins to the value of i - A[j], which could be stored in memo[i - A[j]];
if memo[i] turns out to be empty, it means there is no way to get value i using the given coins;
4. We can tell immediately, if the value is 0, then we need 0 coin. This fact is useful to construct our
coding. Say, we ask for a value that has an exactly same denomination in C, in this case,
memo[Value - denomination] + 1 is equal to 1, if and only if memo[0] == 0;
*/
int MinNumberOfCoins(unsigned int K, const vector<unsigned int> &A)
{
	int len = A.size();
	int empty = -1;
	assert(len > 0 && K > 0 && A[0] <= K);
	//std::sort(A.begin(), A.end());
	vector<int> memo = vector<int>(K + 1, empty);
	memo[0] = 0;
	//for (int i = A[0]; i <= K; ++i)
	for (int i = *std::min_element(A.begin(), A.end()); i <= K; ++i)
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
	cout << "Expect 2: " << MinNumberOfCoins(6, vector<unsigned int>{1, 3, 4}) << endl;
	cout << "Expect -1: " << MinNumberOfCoins(55, vector<unsigned int>{30, 40, 10}) << endl;
}
