//https://codility.com/media/train/13-CaterpillarMethod.pdf
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

//Caterpillar Method
//two iterators moving toward one direction while acessing every element on the way like a caterpillar does
bool solutionSumEqualTo(vector<int> &A, int sum)
{
    int len = A.size();
    assert(len > 0);
    int front=0, back=0, total = 0;
    for (int back = 0; back < len; ++back)
    {
	while (front < len && total + A[front] <= sum)
	    total += A[front++];
	if (sum == total)
	    return true;
	else
	    total -= A[back];
    }
    return false;
}
void testSumEqualTo()
{
    cout << "Expect 1: " << solutionSumEqualTo(vector<int>({ 6, 2, 7, 4, 1, 3, 6 }), 12) << endl;
    cout << "Expect 0: " << solutionSumEqualTo(vector<int>({ 6, 2, 7, 4, 1, 3, 6 }), 100) << endl;
}

