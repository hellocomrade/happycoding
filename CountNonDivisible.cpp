#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingRV29KN-9Q5/

Why I got timeout?

I was thinking the inner loop binary search will take

sqrt(2)*log2, sqrt(3)*log3 ... sqrt(N)*logN, and the outter loop guarantee there are N such elements.
So, the sequence above is less than (sqrt(2)+sqrt(3)+...+sqrt(N))*logN <= NlogN

However, when I wrote it, since the binary search is always against the entire array, not index 0 to index i.
It actually could reach O(N^1.5*logN)...Sad, double timeout...
*/
vector<int> solutionCountNonDivisible1(const vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int j;
	vector<int> result(len, len);
	vector<int> counts(2 * (*std::max_element(A.begin(), A.end())) + 1, 0);
	vector<int> sortedA(len, 0);
	for (int i : A)++counts[i];
	std::copy(A.begin(), A.end(), sortedA.begin());
	sort(sortedA.begin(), sortedA.end());
	for (int i = 0; i < len; ++i)
	{
		j = 1;
		while (j*j < A[i])
		{
			if (0 == A[i] % j)
			{
				if (true == std::binary_search(sortedA.begin(), sortedA.end(), j))
					result[i] -= counts[j];
				if (true == std::binary_search(sortedA.begin(), sortedA.end(), A[i] / j))
					result[i] -= counts[A[i] / j];
			}
			++j;
		}
		if (j*j == A[i] && std::binary_search(sortedA.begin(), sortedA.end(), j))
			result[i] -= counts[j];
	}
	return result;
}
/*
https://codility.com/demo/results/trainingGY6FRP-CT4/
ugly but works, only did so to prove the time complexity I estimated above is correct!

Got having a better solution.

We count the frequence of each element in the sequence first.
Then clone the original sequence and then sort the copy. So we could conduct binary search.
Since a sorted sequence has broken the order of the original one. We have to store the final result
in a hash table, which actually will save time if there are lots of duplicates in the sequence.

The idea is as same as the classic way to find all divisors for composite numbers. 
Assuming there is no divisor for the element at index i (result[i]=len), then we start from 1 and end at sqrt(A[i]) for
divisor trial, j. If there is a hit, we substract counts[j] from result[i].

Finally, we recovery the result in the correct order using the hash table.
*/
vector<int> solutionCountNonDivisible(const vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int j;
	unordered_map<int, int> result;
	vector<int> sortedA(len, 0);
	vector<int> counts(2 * (*std::max_element(A.begin(), A.end())) + 1, 0);
	for (int i : A)++counts[i];
	std::copy(A.begin(), A.end(), sortedA.begin());
	std::sort(sortedA.begin(), sortedA.end());
	vector<int>::iterator itor = sortedA.begin();
	while (sortedA.end() != itor)
	{
		j = 1;
		if (result.end() == result.find(*itor))
		{
			result[*itor] = len;
			while (j*j < *itor)
			{
				if (0 == *itor % j)
				{
					if (true == std::binary_search(sortedA.begin(), itor + 1, j))
						result[*itor] -= counts[j];
					if (true == std::binary_search(sortedA.begin(), itor + 1, *itor / j))
						result[*itor] -= counts[*itor / j];
				}
				++j;
			}
			if (j*j == *itor && std::binary_search(sortedA.begin(), itor + 1, j))
				result[*itor] -= counts[j];
		}
		++itor;
	}
	vector<int> result1(len, 0);
	for (int i = 0; i < len; ++i)
		result1[i] = result[A[i]];
	return result1;
}
static void printResult(const vector<int> &vec)
{
	for (int i : vec)
		cout << i << ",";
	cout << endl;
}
void testCountNonDivisible()
{
	vector<int> ret1 = solutionCountNonDivisible(vector<int>({ 3, 1, 2, 3, 6 }));
	cout << "Expect 2,4,3,2,0: ";
	printResult(ret1);

	vector<int> ret2 = solutionCountNonDivisible(vector<int>({ 1 }));
	cout << "Expect 0: ";
	printResult(ret2);

	vector<int> ret3 = solutionCountNonDivisible(vector<int>({ 1, 2 }));
	cout << "Expect 1, 0: ";
	printResult(ret3);

	vector<int> ret4 = solutionCountNonDivisible(vector<int>({ 1, 2, 3, 4, 6, 9, 18, 36 }));
	cout << "Expect 7,6,6,5,4,5,2,0: ";
	printResult(ret4);
}
