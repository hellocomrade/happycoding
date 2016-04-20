//http://blog.codility.com/2011/03/solutions-for-task-equi.html
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

//very tricky boundary condition:
//Sum of zero elements is assumed to be equal to 0. This can happen if P = 0 or if P = N.1.
//But I think my solution is better than the one on their blog...
int solutionEqui(const vector<int> &A) {
    int len = A.size();
    if (len == 0)
	return -1;
    if (len == 1)
	return 0;
    vector<long long> prefixsum(len+1, 0);
    for (int i = 1; i<=len; ++i)
	prefixsum[i] = prefixsum[i - 1] + A[i-1];
    long long sum = prefixsum[len];
    for (int i = 1; i<len+1; ++i)
	if (prefixsum[i-1] == sum - prefixsum[i])
	    return i-1;
    return -1;
}
void testEqui()
{
    cout << "Expect 1: " << solutionEqui(vector<int>({ -1, 3, -4, 5, 1, -6, 2, 1 })) << endl;
    cout << "Expect 2: " << solutionEqui(vector<int>({ 1,2,6,0,1,1,1 })) << endl;
    cout << "Expect 0: " << solutionEqui(vector<int>({ 1, 2, 6, -9,1})) << endl;
    cout << "Expect 0: " << solutionEqui(vector<int>({ 100 })) << endl;
    cout << "Expect 0: " << solutionEqui(vector<int>({ 500, 1, -2, -1, 2 })) << endl;
    cout << "Expect 0: " << solutionEqui(vector<int>({ -1,0 })) << endl;
    cout << "Expect 0: " << solutionEqui(vector<int>({ -1, -1, 1 })) << endl;
    cout << "Expect 0: " << solutionEqui(vector<int>({ -1, 0, 0 })) << endl;
    cout << "Expect 0: " << solutionEqui(vector<int>({ 1, 1, -1 })) << endl;
}
