#include <vector>
#include <algorithm>
#include <limits>
#include <set>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingSMCHUD-WA3/

Observations:
1. Given N elements with range from [INT_MIN, INT_MAX], if we use a vector to track positive integers,
the naive approch will take INT_MAX slots in the vector, which is an obvious std::bad_alloc. Since
the description asks for O(N) space, we should take a hash table, a set (no duplicate allowed), or
a smarter way to use vector;
2. Let's try to use a vector with size N to track positives. It's a bit counter-intutive,
but given N elements, if they are all positive, then the minimum missing positive integer is N+1.
On the other hand, if integer N+1 exists in the sequence with size of N, then there must be an integer missing
between [1, N] (only at most N-1 count left). This can be proved easily by negation:
If N+1 exists and all integers between [1,N] are also not missing, then we have total N+1 elements,
which is against the truth that there are only N elements.
3. So, we actually only need to watch positive integers from 1 up to N+1. The statement above should prove
all boundary conditions. If N+1 exists in the sequence, missing value is between [1, N]. If N+1 doesn't exist,
the missing minimum positive integer is at most N+1. Either way, we don't need more than N+1 elements to track
the sequence.
*/
int solutionMissingInteger(const vector<int> &A) {
	int len = A.size() + 1;
	vector<int> B(len + 1, 0);
	for (int i : A)
		if (i > 0 && i <= len)
			B[i] = 1;
	for (int i = 1; i <= len; ++i)
		if (0 == B[i])
			return i;
	//we should never reach here
	return -1;
}
/*
https://codility.com/demo/results/trainingXVMGRP-8C5/

This is a cheat: it should take O(NlogN) time to build a BST. However, the detected
time complexity is O(N) due to the fact N is no greater than 100,000. So log(1e5) doesn't make
too much impact on the overall performance.
*/
int solutionMissingInteger1(const vector<int> &A)
{
	int count = 1;
	set<int> tree;
	for (int i : A)
	{
		if (i > 0)
			tree.insert(i);
	}
	for (auto i = tree.begin(); i != tree.end(); ++i)
	{
		if (*i != count)
			return count;
		else
			++count;
	}
	return count;
}
void testMissingInteger()
{
	cout << "Expect 5: " << solutionMissingInteger(vector<int>{ 1, 3, 6, 4, 1, 2 }) << endl;
	cout << "Expect 4: " << solutionMissingInteger(vector<int>{ -1, 1, 2, 3 }) << endl;
	cout << "Expect 1: " << solutionMissingInteger(vector<int>{ numeric_limits<int>::min(), numeric_limits<int>::max() }) << endl;
}
