#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;
//https://codility.com/programmers/task/max_double_slice_sum
/*
https://codility.com/demo/results/trainingZE4RTY-39H/
I failed this one coz I failed to recognize an implicit condition...
I was puzzled by the array with all negative numbers, such as [-2,-1,-4,-5,-10].
I thought the max is -1 if we take (0,2,3).
However, according to the description of the problem, a triplet with three continouse
indexes is defined to be equle to 0! so, in the case I worried, the max is actually 0.

I took a peek on the solution from a facebook developer's blog:
http://rafal.io/posts/codility-max-double-slice-sum.html

We take two array to track the maxendhere from left and from right. Then we simply
compare maxFromLeft[i - 1] + maxFromRight[i + 1]. No need to think where the left and right
boundaries are since they are embeded insode maxFromLeft and maxFromRight.
If you fallen into the thought to do so, you would fail...
*/
int solutionMaxDoubleSliceSum(const vector<int>& A)
{
    int len = A.size();
    assert(len>2);
    vector<int> maxFromLeft(len,0), maxFromRight(len,0);
    maxFromLeft[0] = maxFromRight[0] = 0;
    maxFromLeft[len - 1] = maxFromRight[len - 1] = 0;
    for (int i = 1; i < len; ++i)
	maxFromLeft[i] = std::max(maxFromLeft[i - 1] + A[i], 0);
    for (int i = len-2; i >= 0; --i)
	maxFromRight[i] = std::max(maxFromRight[i + 1] + A[i], 0);
    int max = 0;
    for (int i = 1; i < len - 1; ++i)
	max = std::max(max, maxFromLeft[i - 1] + maxFromRight[i + 1]);
    return max;
}
//Update on 2018-08-03
//https://app.codility.com/demo/results/trainingETVTKH-3VF/
/*
First attempt failed on [0,10,-5,-2,0], correct answer is 10

maxsum1 storing max sum ends at index i from left, maxsum1[0] = maxsum1[len - 1] = 0
maxsum2 storing max sum ends at index i from right, maxsum2[0] = maxsum2[len - 1] = 0

Final answer is:

ans = std::max(ans, std::max(std::max(maxsum1[i - 1], maxsum2[i + 1]), maxsum1[i - 1] + maxsum2[i + 1]));

Given i in [1, len - 2].

I am not sure if this solution is perfect coz it handle the case like [-1,-2,-3,-4] by chance...

maxsum1: [0,-2,-3,0]
maxsum2: [0,-2,-3,0]

In fact since triple [i, i + 1, i + 2] results in sum 0, there will be no chance for any negative slice max.
*/
int solution1(vector<int> &A) {
    size_t len = A.size();
    vector<long long> maxsum1(len, 0), maxsum2(len, 0);
    long long maxContriPrev1 = 0LL, maxContriPrev2 = 0LL, ans = numeric_limits<int>::min();
    for(size_t i = 1; i < len - 1; ++i) {
        maxsum1[i] = maxContriPrev1 + A[i];
        maxsum2[len - i - 1] = maxContriPrev2 + A[len - i - 1];
        maxContriPrev1 = std::max(0LL, maxContriPrev1 + A[i]);
        maxContriPrev2 = std::max(0LL, maxContriPrev2 + A[len - i - 1]);
    }
    for(size_t i = 1; i < len - 1; ++i) ans = std::max(ans, std::max(std::max(maxsum1[i - 1], maxsum2[i + 1]), maxsum1[i - 1] + maxsum2[i + 1]));
    return static_cast<int>(ans);
}
void testMaxDoubleSliceSum()
{
    cout << "Expect 17: " << solutionMaxDoubleSliceSum(vector<int>({ 3, 2, 6, -1, 4, 5, -1, 2 })) << endl;
    cout << "Expect 0: " << solutionMaxDoubleSliceSum(vector<int>({ 3, 4, 5 })) << endl;
    cout << "Expect 5: " << solutionMaxDoubleSliceSum(vector<int>({ 3, 1, -6, 4, 0 })) << endl;
    cout << "Expect 0: " << solutionMaxDoubleSliceSum(vector<int>({ -1, -2, -3, -4, -5 })) << endl;
    cout << "Expect 17: " << solutionMaxDoubleSliceSum(vector<int>({ 5, 17, 0, 3 })) << endl;
}
 
