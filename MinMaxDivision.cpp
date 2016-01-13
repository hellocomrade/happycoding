//https://codility.com/programmers/task/min_max_division/
//https://www.topcoder.com/community/data-science/data-science-tutorials/binary-search/
#include "stdafx.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

/*
 * First of all, M is useless. The description says "Every element of the array is not greater than M.". It is
 * just a catch to make you believe the largest elem in the array is M, which is not ture!!! You would be shocked
 * if you check the final result by browsing the test cases they offered!
 *
 * The topcoder site has a throughout explanation on using binary search to solve the finding optimal type of tasks.
 * If we could interpret the task as: finding a value X in A so no sub sequence could have a sum more than X and the number
 * of sub arrays (divisions) is no more than K. You would have a better chance to conquer this task.
 *
 * If we consider the smallest max as a monotonic sequence, the lower bound of the sequence is the largest element in the array, 
 * and the higher bound is the sum of all elements. Then we choose the possible 'smallest max' at the middle of the sequence and 
 * always greedily drops half of of the sequence by comparing the number of partitions based upon current 'smallest max' with the proposed K. 
 * If our partition L is less than K, we probably can find a even smaller 'smallest max' by dropping the lager half of the sequence, 
 * otherwise, drop the smaller half.  
 */
int solutionMinMaxDivision(int K, int M, vector<int> &A) {
    int len = A.size();
    assert(len > 0);
    long long high=std::accumulate(A.begin(), A.end(),0ll);
    long long low = *std::max_element(A.begin(), A.end());
    long long m, sum;
    int partition;
    while (low <= high)
    {
	m = low + (high - low) / 2;
	partition = 1;
	sum = 0;
	for (int i = 0; i < len; ++i)
	{
	    if (sum + A[i] <= m)
		sum += A[i];
	    else
	    {
		++partition;
		sum = A[i];
	    }
	}
	if (partition <= K)
	    high = m - 1;
	else
	    low = m + 1;
    }
    return (int)low;
}
//https://codility.com/demo/results/trainingH27HU9-8CP/
int solutionMinMaxDivision1(int K, int M, vector<int> &A) {
    int h,m,cnt,sum,sm,msum,len;
    int l=*std::max_element(A.begin(), A.end());
    len=A.size();
    msum=h=accumulate(A.begin(),A.end(),0);
    while(l<=h)
    {
        m=l+(h-l)/2;
        sum=sm=0;
        cnt=1;
        for(int i=0;i<len;++i)
        {
            if(sum+A[i]>m)
            {
                sm=std::max(sm,sum);
                sum=A[i];
                ++cnt;
            }
            else
                sum+=A[i];
        }
        if(cnt<=K)
        {
            msum=std::min(msum,std::max(sm,sum));
            h=m-1;
        }
        else
            l=m+1;
    }
    return msum;
}
void testMinMaxDivision()
{
    cout << "Expect 6: " << solutionMinMaxDivision(3, 5, vector<int>({ 2, 1, 5, 1, 2, 2, 2 })) << endl;
    cout << "Expect 5: " << solutionMinMaxDivision(3, 5, vector<int>({ 1, 5 })) << endl;
    cout << "Expect 6: " << solutionMinMaxDivision(1, 5, vector<int>({ 1, 5 })) << endl;
    cout << "Expect 0: " << solutionMinMaxDivision(1, 1, vector<int>({ 0 })) << endl;
}


