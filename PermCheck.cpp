#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/training66TYXU-7B5/
https://codility.com/demo/results/trainingMPKRTY-8K2/

Observation:
1. Given extra O(N) space, use either a vector or a hash table
2. The elements in the vector doesn't have to fit into the range of [1, len]. Therefore, if you use vector
   as the storage, an extra check is necessary to rule out any element that is greater than len. The function
   in this case, returns immediately with 0
3. It's actually possible to get this done using const space: the trick is to repeatly move A[i] to index A[A[i] - 1], if possible.
   Otherwise, we know this is not a permutation. Two exit conditions: A[i] > size or A[i] == A[A[i] - 1], which means there are duplicates.
   However, this approach will have to modifyinput vector.
*/
int solutionPermCheck(vector<int> &A) {
    int len = A.size();
    for(int i = 0; i < len; ++i) {
        while(A[i] != i + 1) {
            if(A[i] > len || A[A[i] - 1] == A[i])return 0;
            std::swap(A[i], A[A[i] - 1]);
        }
    }
    return 1;	
}
int solutionPermCheck1(const vector<int> &A) {
	unordered_map<int, bool> map;
	for (auto i : A)
	{
		if (map.end() != map.find(i))
			return 0;
		else
			map[i] = true;
	}
	int len = A.size();
	for (int i = 1; i <= len; ++i)
	{
		if (map.end() == map.find(i))
			return 0;
	}
	return 1;
}
int solutionPermCheck2(const vector<int> &A) {
	int len = A.size();
	vector<int> bucket(len + 1, 0);
	bucket[0] = 1;
	for (auto i : A)
	{
		if (i > len || 1 == bucket[i])return 0;
		else
			bucket[i] = 1;
	}
	for (auto i : bucket)
	{
		if (0 == i)
			return 0;
	}
	return 1;
}
void testPermCheck()
{
	vector<int> vec1{ 4, 1, 3, 2};
	cout << "Expect 1: " << solutionPermCheck(vec1) << endl;
	vector<int> vec2{ 4, 1, 3 };
	cout << "Expect 0: " << solutionPermCheck(vec2) << endl;
}
