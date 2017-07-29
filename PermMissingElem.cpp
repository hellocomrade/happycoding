#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/training8N4RMX-FD9/

Observations:
1. A could be zero length! Since N>=0, a zero length A, [], means the 1 is missing, according to
the description, the number sequence is supposed from 1 to N+1;

2. integer overflow, N<=10,000, so if we do (N+1)*(N+2)/2, it will blow the integer! so, have to upward
cast to long, make sure checking the size of long first...


http://codesays.com/2014/solution-to-perm-missing-elem-by-codility/#comment-1000
The main challenge of this question is the XOR operations: X^X=0, and 0^X=X.
Logically, the addition and subtraction operations also are able to do this work.
But taking the overflow in computer into consideration, they become a very bad choice.

Python

def solution(A):
length = len(A)
xor_sum = 0

for index in range(0, length):
xor_sum = xor_sum ^ A[index] ^ (index + 1)

return xor_sum^(length + 1)

*/
int solutionPermMissingElem(const vector<int> &A) {
	long long len = A.size();
	long long sumA = accumulate(A.begin(), A.end(), 0LL);
	return (len + 2)*(len + 1) / 2 - sumA;
}
/*
You have to write more here but it's still O(N), one time slower than the above but you don't
have to worry about integer overflow...
*/
int solutionPermMissingElem1(const vector<int> &A) {
    int len = A.size();
    for(int i = 0; i < len; ++i) {
        while(A[i] != i + 1 && A[i] - 1 < len)
            std::swap(A[i], A[A[i] - 1]);
    }
    for(int i = 0; i < len; ++i)if(A[i] != i + 1)return i + 1;
    return len + 1;
}
void testPermMissingElem()
{
	cout << "Expect 4: " << solutionPermMissingElem(vector<int>{ 2, 3, 1, 5 }) << endl;
	cout << "Expect 1: " << solutionPermMissingElem(vector<int>{}) << endl;
}
