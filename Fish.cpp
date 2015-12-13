#include <cassert>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingFRFNNW-BDF/
Observations:
1. In order to simplify the problem, we have to define a offensive side and definsive side. So we can
deal with two sides differently;
2. Assuming downstream is the attacking side, and poor upstream salmons have to pass through all greedy
fishes. As long as salmons can pass the last remaining attackers (with the smallest possible index),
it's free to go;
3. See the following sequences:
A: 5, 8, 4, 5, 6
B: 0, 1, 1, 0, 1
The first salmon is free to go since there is no attacker anymore. The last attacker will survive as
well, since there is no salmon anymore. In the middle of the sequence though, we can find 8 and 4 are
both swim downstream, 5 at index 3 is a salmon and will confront 4 first, which 5 will win. However, it
will then be caught by 8.

If we are composing an algorithm in O(N) time, we will need to stack up the attackers while scanning
the array. Everytime we have a salmon, we will test it with all attackers waiting on the stack. If it
passes all, we have a survivor going upstream. At the meantime, all attackers on his way has been cleared.
On the other hand, by the end of the scan, if we still have attackers waiting on the stack, all of them
are qualified to go downstream since all salmons on their way have been cleared by the attacker stays
on top of the stack.
4. Originally, I have a stack for upstream salmons as well. After I submitted the code, I realize it's
unnecessary since this stack is only pushed and never poped, in other words, we can simply replace it
with a counter.
*/
int solutionFish(vector<int> &A, vector<int> &B)
{
	int len1 = A.size();
	int len2 = B.size();
	assert(len1 > 0);
	assert(len1 == len2);
	int upstream = 0;
	stack<int> downstream;
	for (int i = 0; i < len1; ++i)
	{
		assert(0 == B[i] || 1 == B[i]);
		if (0 == B[i])
		{
			if (false == downstream.empty())
			{
				while (false == downstream.empty() && downstream.top() < A[i])
					downstream.pop();
				if (true == downstream.empty())
					++upstream;
			}
			else
				++upstream;
		}
		else
			downstream.push(A[i]);
	}
	return downstream.size() + upstream;
}
void testFish()
{
	cout << "Expect 2: " << solutionFish(vector<int>({ 4, 3, 2, 1, 5 }), vector<int>({ 0, 1, 0, 0, 0 })) << endl;
	cout << "Expect 3: " << solutionFish(vector<int>({ 5, 8, 4, 5, 6 }), vector<int>({ 0, 1, 1, 0, 1 })) << endl;
	cout << "Expect 2: " << solutionFish(vector<int>({ 5, 3, 6, 5, 1 }), vector<int>({ 1, 0, 0, 1, 0 })) << endl;
	cout << "Expect 3: " << solutionFish(vector<int>({ 5, 3, 6, 5, 1 }), vector<int>({ 1, 0, 1, 1, 0 })) << endl;
	cout << "Expect 2: " << solutionFish(vector<int>({ 5, 3, 6, 5, 8 }), vector<int>({ 1, 0, 0, 1, 0 })) << endl;
	cout << "Expect 1: " << solutionFish(vector<int>({ 5, 3, 6, 5, 8 }), vector<int>({ 1, 0, 1, 1, 0 })) << endl;
	cout << "Expect 1: " << solutionFish(vector<int>({ 5, 3, 4, 2, 1 }), vector<int>({ 1, 0, 0, 0, 0 })) << endl;
	cout << "Expect 1: " << solutionFish(vector<int>({ 5, 3, 4, 2, 6 }), vector<int>({ 1, 1, 1, 1, 0 })) << endl;
	cout << "Expect 1: " << solutionFish(vector<int>({ 1000000000 }), vector<int>({ 0 })) << endl;
	cout << "Expect 1: " << solutionFish(vector<int>({ 1000000000 }), vector<int>({ 1 })) << endl;
	cout << "Expect 1: " << solutionFish(vector<int>({ 0, 1 }), vector<int>({ 1, 0 })) << endl;
	cout << "Expect 2: " << solutionFish(vector<int>({ 0, 1 }), vector<int>({ 0, 1 })) << endl;
	cout << "Expect 5: " << solutionFish(vector<int>({ 0, 3, 2, 1, 100000 }), vector<int>({ 0, 0, 0, 0, 1 })) << endl;
	cout << "Expect 4: " << solutionFish(vector<int>({ 5, 3, 2, 1, 0 }), vector<int>({ 1, 1, 1, 1, 0 })) << endl;
	cout << "Expect 1: " << solutionFish(vector<int>({ 5, 3, 2, 4, 0, 6 }), vector<int>({ 1, 0, 1, 0, 1, 0 })) << endl;
	cout << "Expect 4: " << solutionFish(vector<int>({ 5, 3, 6, 4, 7, 0, 1 }), vector<int>({ 1, 0, 0, 0, 1, 0, 1 })) << endl;
}