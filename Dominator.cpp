#include <vector>
#include <iostream>
#include <limits>

using namespace std;

/*
https://codility.com/demo/results/trainingJS32BK-4DE/
https://codility.com/media/train/6-Leader.pdf
another classic question.
"Notice that the sequence can have at most one leader. If there were two leaders then their total
occurrences would be more than 2*n/2 = n, but we only have n elements"
"Notice that if the sequence a0, a1, . . . , an−1 contains a leader, then after removing a pair of
elements of different values, the remaining sequence still has the same leader. Indeed, if we
remove two different elements then only one of them could be the leader. The leader in the
new sequence occurs more than n/2 − 1 = (n−2)/2 times. Consequently, it is still the leader of the
new sequence of n − 2 elements."

I do like codility's analysis in the instruction. It use a stack to illustrate how it works:

3, 4, 3, 2, 3, -1, 3, 3

push 3 on the stack and then if the next element is different than stack top, we discard the current
element and pop the stack. For example, when we reach 4, since 4 !=3, we discard both of them. The
elemetns remain on the stack after the whole scan, for our case, it's 3, will be considered as the candidate.
Not the final result yet. Why? Consider the following example:
1, 2, 3, 4, 5, 5
After the scan, removal and stack things, we will have two 5 remaining on the stack. It can only prove that
5 has the most occurance among the sequence, however, it might not occur more than N/2.
In order to verify if the candidate is the final result. We will have to take this candidate and scan
the sequence again so we can count the number of occurance of the candidate. The candiate is the final
result if and only if it occurs more than N/2 times. Fortunately, this post-scan only takes O(N).

So the overall time complexity is still O(N)
*/
int solutionDominator(const vector<int>& A)
{
	int len = A.size();
	int idx = -1;
	int count = 0;
	for (int i = 0; i < len; ++i)
	{
		if (0 == count)
			idx = i;
		if (A[i] == A[idx])
			++count;
		else
			--count;
	}
	if (count > 0)
	{
		count = 0;
		for (int i = 0; i < len; ++i)
		{
			if (A[i] == A[idx])
				++count;
		}
		return count > len / 2 ? idx : -1;
	}
	else
		return -1;
}
void testDominator()
{
	cout << "Expect 6: " << solutionDominator(vector<int>({ 3, 4, 3, 2, 3, -1, 3, 3 })) << endl;
	cout << "Expect -1: " << solutionDominator(vector<int>({})) << endl;
	cout << "Expect -1: " << solutionDominator(vector<int>({ 1, 2, 3, 4, 5, 5 })) << endl;
	cout << "Expect -1: " << solutionDominator(vector<int>({ 5, 5, 3, 4, 6, 7 })) << endl;
	cout << "Expect -1: " << solutionDominator(vector<int>({ 1, 2, 3, 4, 5 })) << endl;
	cout << "Expect 0: " << solutionDominator(vector<int>({ numeric_limits<int>::min(), numeric_limits<int>::min(), 1 })) << endl;
	cout << "Expect 4: " << solutionDominator(vector<int>({ 2, 2, 1, 1, 2 })) << endl;
	cout << "Expect -1: " << solutionDominator(vector<int>({ 2, 2, 1, 1, 2, 1 })) << endl;
	cout << "Expect -1: " << solutionDominator(vector<int>({ 5, 4, 3, 1, 2, 2, 2 })) << endl;
}
