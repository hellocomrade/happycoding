//https://codility.com/demo/take-sample-test/min_abs_sum_of_two/
#include <cassert>
#include <climits>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int solutionMinAbsSumOfTwo(vector<int>& A)
{
    int len = A.size();
    assert(len>0);
    sort(A.begin(), A.end());
    //make two iterators, one from left and the other from right,
    //since all elements in the array are in nondescending order, we could move one iterator toward the center on each step depending on
    //the result of A[left]+A[right]. Therefore, we can find min in O(N). This is more intuitive if we use the following as example
    //[-3,-1,3,2]. 
    int left=0, right=len-1, min=INT_MAX, tmp;
    while(left<=right)
    {
	tmp=A[left]+A[right];
	min=std::min(min,abs(tmp));
	tmp<=0?++left:--right;
    }
    return min;
}
void testMinAbsSumOfTwo()
{
    cout << "Expect 1: " << solutionMinAbsSumOfTwo(vector<int>({ 1, 4, -3 })) << endl;
    cout << "Expect 3: " << solutionMinAbsSumOfTwo(vector<int>({ -8, 4, 5, -10, 3 })) << endl;
    cout << "Expect 2: " << solutionMinAbsSumOfTwo(vector<int>({ 1, 20, 60, 100, 200 })) << endl;
    cout << "Expect 10: " << solutionMinAbsSumOfTwo(vector<int>({ -100, -50, -20, -5 })) << endl;
    cout << "Expect 1: " << solutionMinAbsSumOfTwo(vector<int>({ -100, -50, 2, 49, 95 })) << endl;
}

