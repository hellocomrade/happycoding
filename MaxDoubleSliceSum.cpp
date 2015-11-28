//https://codility.com/programmers/task/max_double_slice_sum
/*
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
int solutionMaxDoubleSliceSum(vector<int>& A)
{
    int len = A.size();
    assert(len>2);
    vector<int> maxFromLeft(len,0), maxFromRight(len,0);
    maxFromLeft[0] = maxFromRight[0] = 0;
    maxFromLeft[len - 1] = maxFromRight[len - 1] = 0;
    for (int i = 1; i < len; ++i)
	maxFromLeft[i] = std::max(maxFromLeft[i - 1] + A[i], 0);
    for (int i = len-2; i >= 0; --i)
	maxFromRight[i] = std::max(maxFromRight[i + 1 ] + A[i], 0);
    int max = 0;
    for (int i = 1; i < len - 1; ++i)
	max = std::max(max, maxFromLeft[i - 1] + maxFromRight[i + 1]);
    return max;
}
void testMaxDoubleSliceSum()
{
    cout << "Expect 17: " << solutionMaxDoubleSliceSum(vector<int>({ 3, 2, 6, -1, 4, 5, -1, 2 })) << endl;
    cout << "Expect 0: " << solutionMaxDoubleSliceSum(vector<int>({ 3, 4, 5 })) << endl;
    cout << "Expect 5: " << solutionMaxDoubleSliceSum(vector<int>({ 3, 1, -6, 4, 0 })) << endl;
    cout << "Expect 0: " << solutionMaxDoubleSliceSum(vector<int>({ -1, -2, -3, -4, -5 })) << endl;
    cout << "Expect 17: " << solutionMaxDoubleSliceSum(vector<int>({ 5, 17, 0, 3 })) << endl;
}
 
