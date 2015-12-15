#include <cassert>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;
/*
https://codility.com/demo/results/trainingTSATYE-TKV/
Well, again, I was numb to recognize the fact equileader exists if and only if it is the leader of
the sequence. Fortunately, codility is kind this time and allows space complexity to be O(N).
This gives me the opportunity to apply the old hashtable trick here.
An extra vector is needed to store the leader-end-here. And then scan the sequence backward to find
the leader starting from N-1 to 1, so we can compare the backward leader with the leader-end-here saved
in the vector.
I have to admit my solution is silly though…
Extra time was spent to figure out how to insert key value into unordered_map and how to detect key does
not exist:
unordered_map<int, int>::const_iterator nonexist = counter.end();
if (counter.find(A[i]) == nonexist)

To insert key value, you could do:
counter.emplace(A[i], 1);
or
counter[A[i]] = 1;
or
counter.insert(std::make_pair(A[i], 1));
or
counter.insert(std::pair<int, int>(A[i], 1));
*/
int solutionEquiLeader(vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int missing = -1000000001, count = 0, lastleader = missing;
	vector<int> forward(len, missing);
	unordered_map<int, int> counter;
	unordered_map<int, int>::const_iterator nonexist = counter.end();
	for (int i = 0; i < len; ++i)
	{
		if (counter.find(A[i]) == nonexist)
			counter.emplace(A[i], 1);
		else
			++counter[A[i]];
		if (counter[A[i]] >(i + 1) / 2)
			lastleader = forward[i] = A[i];
		else if (counter[lastleader] > (i + 1) / 2)
			forward[i] = lastleader;
	}
	counter.clear();
	lastleader = missing;
	for (int i = len - 1; i > 0; --i)
	{
		if (counter.find(A[i]) == nonexist)
			counter[A[i]] = 1;
		else
			++counter[A[i]];
		if (counter[A[i]] > (len - i) / 2 && forward[i - 1] == A[i])
		{
			lastleader = A[i];
			++count;
		}
		else if (counter[lastleader] > (len - i) / 2 && forward[i - 1] == lastleader)
			++count;
	}
	return count;
}
void tesetEquiLeader()
{
	cout << "Expect 2: " << solutionEquiLeader(vector<int>({ 4, 3, 4, 4, 4, 2 })) << endl;
	cout << "Expect 0: " << solutionEquiLeader(vector<int>({ 1000000000 })) << endl;
	cout << "Expect 1: " << solutionEquiLeader(vector<int>({ 1, 1 })) << endl;
	cout << "Expect 0: " << solutionEquiLeader(vector<int>({ 1, 1, 0 })) << endl;
	cout << "Expect 1: " << solutionEquiLeader(vector<int>({ 1, 1, 0, 0, 0, 0 })) << endl;
	cout << "Expect 0: " << solutionEquiLeader(vector<int>({ 1, 0, 1 })) << endl;
	cout << "Expect 2: " << solutionEquiLeader(vector<int>({ 1, 1, 0, 1 })) << endl;
	cout << "Expect 2: " << solutionEquiLeader(vector<int>({ 1, 0, 1, 1 })) << endl;
	cout << "Expect 3: " << solutionEquiLeader(vector<int>({ 1, 1, 1, 1 })) << endl;
	cout << "Expect 0: " << solutionEquiLeader(vector<int>({ 3, 1, 2, 4, 4, 2, 4 })) << endl;
	cout << "Expect 0: " << solutionEquiLeader(vector<int>({ 3, 1, 2, 2, 2, 2, 4 })) << endl;
	cout << "Expect 2: " << solutionEquiLeader(vector<int>({ 3, 1, 2, 2, 2, 2, 4, 2 })) << endl;
	cout << "Expect 0: " << solutionEquiLeader(vector<int>({ -3, 1, -3, 2, -3, 2, 4, -3 })) << endl;
	cout << "Expect 4: " << solutionEquiLeader(vector<int>({ -3, 1, -3, 2, -3, -3, 4, -3 })) << endl;
}