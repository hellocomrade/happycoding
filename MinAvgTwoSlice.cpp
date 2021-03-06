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
int solutionMinAvgTwoSlice(const vector<int> &A)
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
int solutionMinAvgTwoSlice1(const vector<int> &A) {
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
/*
Another "silly" but works solution.
In order to maintain time complexity at O(N) with O(N) extra space, we could assume a scenario that at any given index K, we
could find the min average, which starts at K and ends at M, M > K.
In order to achieve this goal/assumption, we scan the array from the end: at any given index I, we store the sum of a slice that could 
generate min avg from I to len - 1, len is the size of the array. We also store the number of elements in this slice.

Such a slice either contains only 1 element if (the previous chosen slice at [I - 1] + A[I]) / (the previous chosen slice at [I - 1] size + 1) > A[i]
or append A[I] to the previous chosen slice at [I - 1] as the chosen slice at [I]
*/
int solutionMinAvgTwoSlice2(vector<int> &A) {
    int ans = -1;
    int len = (int)A.size();
    double minAvg = numeric_limits<double>::max(), val = 0;
    vector<std::pair<int, int>> memo(len, std::make_pair(numeric_limits<int>::max(), -1));
    memo[len - 1].first = A[len - 1];
    memo[len - 1].second = 1;
    for(int i = len - 2; i > 0; --i) {
    	//https://codility.com/demo/results/trainingVXJZZZ-DT5/
    	/*
    	The previous version on the condition is > instead of >=, which will return the correct start index for the slice. However,
    	the actual min average value is wrong. For example [1, 2, 2]. The correct min avg is 1.5, not 1.67...
    	Therefore, I replaced the operator with >=. It also passed all test cases and let's hope it's right this time...
    	(double)(A[i] + memo[i + 1].first) / (1 + memo[i + 1].second) >= A[i]
    	It's still not right, considering the following cases:
    	[-1, -2, -2] if we take >= as the rule to init the reset of the slice, memo will look like [whatever, -2, -2], then at index 0,
    	the min avg will be (-1 - 2) / 2 = -1.5, actually, the minimum avg we could get at index 0 is (-1 - 2 - 2) / 3 = -1.667...
    	
    	>= doesn't cover all cases due to the fact "less than" is defined the opposite way between positive and negative. We can also
    	tell that 0 leans to the negative case in this one. So, we will have to redesign the conditions for postive, negative and zero.
    	https://codility.com/demo/results/training9Y7W4N-Z2D/
    	
    	Well, all three algorithms passed the test. However, you still can't tell if they are correct. Maybe Rocky is right...
    	*/
        val = (double)(A[i] + memo[i + 1].first) / (1 + memo[i + 1].second);
        if((A[i] > 0 && val >= A[i]) ||(A[i] <= 0 && val > A[i])) {
            memo[i].first = A[i];
            memo[i].second = 1;
        }
        else {
            memo[i].first = A[i] + memo[i + 1].first;
            memo[i].second = 1 + memo[i + 1].second;
        }
    }
    for(int i = 0; i < len - 1; ++i) {
        val = (double)(A[i] + memo[i + 1].first) / (1 + memo[i + 1].second);
        if(val < minAvg) {
            minAvg = val;
            ans = i;
        }
    }
    return ans;
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
