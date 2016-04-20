#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * https://codility.com/demo/results/trainingMXVBWQ-FSF/
 * Tricks:
 * 1. if we apply max counter operation every time we see it, in the worst case, time complexity
 *    will be O(N*M)
 * 2. Instead, we keep the value of the last max counter in lastmax, for any following increase
 *    operations, if vec[A[i]] is less than lastmax, we compensate it by adding lastmax+1. This
 *    should not be applied if vec[A[i]] is already greater or equal to lastmax. In other words,
 *    the compensation operation is only applied once on each possible vec[A[i]]
 * 3. Then we use another variable max to track the current max. Each time we meet a max counter 
 *    operation, we keep max value in lastmax and reset max to zero. However, this will not work
 *    for all scenario. For example:
 *     		solutionMaxCounter(3, vector<int>({ 1, 4, 4, 4 }));
 *    On the second step, max counter occurs, we save lastmax = 1 and reset max = 0. On the next
 *    operation, it is still a max counter. if we do lastmax = max, lastmax will be zero and we 
 *    would lose track of the progress. So, we have to: std::max(lastmax, max); You may ask: what
 *    if lastmax =2 but max = 1, will it mess up the tracking? The answer is No! why? Because we
 *    can easily prove that max will either be 0 or bigger than lastmax as long as max counter
 *    operations don't come continuously. Say lastmax = 2, in vec, the max value at this point is
 *    2. If the next operation is increase, then we guarantee max will be (lastmax + 1). So max
 *    will be larger than lastmax in this scenario.
 *
 *    CORRECTION: in fact, I was wrong! If we leave max as it is every time we assign lastmax, it should
 *     		  be all rigt and it makes the logic a little bit easier to understand.
 *
 * 4. At last, for all elements in vec that are smaller than lastmax, we own them a compensation
 *    operation.
 */
vector<int> solutionMaxCounter(int N, const vector<int> &A) {
    int len = A.size();
    assert(len > 0);
    assert(N > 0);
    vector<int> vec(N, 0);
    int max = 0, lastmax = 0;
    for (int i : A)
    {
	assert(i > 0);
	if (i == N + 1)
	{
	    lastmax = max;
 	    //lastmax = std::max(lastmax, max);
	    //max = 0;
	}
	else
	{
	    if (vec[i - 1] < lastmax)
		vec[i - 1] = lastmax + 1;
	    else
		++vec[i - 1];
	    max = std::max(max, vec[i - 1]);
	}
    }
    for (int i = 0; i < N; ++i)
    {
	if (vec[i] < lastmax)
		vec[i] = lastmax;
    }
    return vec;
}
void testMaxCounter()
{
    cout << "Expect 3,2,2,4,2,: ";
    vector<int> result = solutionMaxCounter(5, vector<int>({3,4,4,6,1,4,4}));
    for (int i : result)
	cout << i << ',';
    cout << endl;

    cout << "Expect 3,3,3,6,3,: ";
    vector<int> result1 = solutionMaxCounter(5, vector<int>({ 3, 4, 4, 6, 1, 6, 4, 4, 4 }));
    for (int i : result1)
	cout << i << ',';
    cout << endl;

    cout << "Expect 3,: ";
    vector<int> result2 = solutionMaxCounter(1, vector<int>({ 1, 2, 1, 1}));
    for (int i : result2)
	cout << i << ',';
    cout << endl;

    cout << "Expect 1,1,1,: ";
    vector<int> result3 = solutionMaxCounter(3, vector<int>({ 1, 4, 4, 4 }));
    for (int i : result3)
	cout << i << ',';
    cout << endl;
}
