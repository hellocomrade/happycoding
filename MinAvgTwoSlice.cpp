//https://codility.com/demo/results/training4M2QEN-3PD/
#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * Naive solution
 *
 * Since we deal with average here, at least a pair of elements should be examined each step
 * From the example it gives, it's an easy observation that the ith and (i+1)th should be checked
 * on each step. For example,[4,2,2], [2,2] has a smaller avg than [4,2]; However, it's also possible that
 * 3 continuous elements could have an even lower avg, say [-8,-4,-10]. I don't have an example on top
 * of my head to qualify three elements min avg with all positive numbers.
 *
 * So, based upon the observations above, we will loop the array starting from 1 (assuming we take A[0] and A[1]
 * as the init value for sum and base for min avg already) and loop ends at len-2. 
 * On each step, both i and i+1 th elements will be checked:
 *
 * 1. Whether (A[i]+A[i+1])/2.0 is smaller than the previous avg min; If yes, reset startidx to i and update avg min.
 * 2. Whether current minendhere (min dividend actually) plus A[i] and then divided by the number of elements is smaller than previous avg min;
 *    if yes, update the minendhere and try to update avg min only if sum/cnt is less than avg min so far.
 * 3  Whether neither of above is satisfied, we have found the min avg end at index i-1, reset current sum to max value
 *    and then move i backward 1 to i-1, also reset number count to 1; Decrease index i by 1 is necessary, or you
 *    will not get the correct answer for the case like  [-3, -5, -8, -4, -10]. Without i-1, you will pick [-4,-10],
 *    instead of [-8,-4,-10]. 
 * 4. According to the result from above 3 steps, we now can safely update the avg min so far and start index of current avg-min sequence 
 */
int solutionMinAvgTwoSlice(vector<int> &A)
{
    int len = A.size() - 1;
    assert(len>0);
    double avgminsofar = (A[0] + A[1])/2.0;
    double minendhere = (A[0] + A[1]);
    double tmp, tmp1;
    int sidx = 0, minidx = 0, cnt = 2;
    for (int i = 1; i<len; ++i)
    {
	tmp = (A[i] + A[i + 1]) / 2.0;
	tmp1 = (minendhere == std::numeric_limits<double>::max())?std::numeric_limits<double>::max():(minendhere + A[i + 1]) / (cnt + 1);
	if (tmp < tmp1 && tmp < minendhere / cnt)
	{
	    minendhere = (A[i] + A[i + 1]);
	    sidx = i;
	    cnt = 2;
	}
	else if (tmp1 < tmp && tmp1 < minendhere / cnt)
	{
	    minendhere += A[i + 1];
	    ++cnt;
	}
	else
	{
	    minendhere = std::numeric_limits<double>::max();
	    cnt = 1;
	    --i;
	}
	if (avgminsofar>minendhere / cnt)
	{
		minidx = sidx;
		avgminsofar = minendhere / cnt;
	}
    }
    return minidx;
}
/*
https://codility.com/demo/results/trainingY2VXYP-3Y7/
A better solution:
It can be proved the min average slices come from either 2-elements-slice or 3-elements-slice.
So, we really simply the problem to find a continuous subsequence with either 2 or 3 elements having the min average.
This can be done in O(N) time and O(1) space.
*/
int solutionMinAvgTwoSlice1(vector<int> &A) {
    int len=A.size();
    assert(len>1);
    int i=0, idx=0;
    double avg=numeric_limits<double>::max(), tmp;
    while(i+2<len)
    {
        tmp=std::min((A[i]+A[i+1])/2.0, (A[i]+A[i+1]+A[i+2])/3.0);
        if(tmp<avg)
        {
            idx=i;
            avg=tmp;
        }
        ++i;
    }
    tmp=(A[len-1]+A[len-2])/2.0;
    if(tmp<avg)
        idx=i;
    return idx;
}
void testMinAvgTwoSlice()
{
    cout << "Expect 1: " << solutionMinAvgTwoSlice(vector<int>({ 4, 2, 2, 5, 1, 5, 8 })) << endl;
    cout << "Expect 1: " << solutionMinAvgTwoSlice(vector<int>({ 4, -2, 2, 5, 1, 5, 8 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ 4, 2 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -4, -2, -1, -3 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -1, -1, -1, -1 })) << endl;
    cout << "Expect 2: " << solutionMinAvgTwoSlice(vector<int>({ -1, -2, -3, -4 })) << endl;
    cout << "Expect 2: " << solutionMinAvgTwoSlice(vector<int>({ -3, -5, -8, -4, -10 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -8, -4, -10 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ 4, -10, 5, 10, -5, 8 })) << endl;
    cout << "Expect 0: " << solutionMinAvgTwoSlice(vector<int>({ -1, -1, 0, 0, -1, -1, -1 })) << endl;
}	 
