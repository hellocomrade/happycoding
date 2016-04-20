#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
/*
 * Given line segments, count the number of possible unions, if an interval is disjoinst, it is considered
 * as an union by itself. For example:
 * A[0] =  1    A[1] = 12    A[2] = 42
 * A[3] = 70    A[4] = 36    A[5] = -4
 * A[6] = 43    A[7] = 15
 *
 * B[0] =  5    B[1] = 15    B[2] = 44
 * B[3] = 72    B[4] = 36    B[5] =  2
 * B[6] = 69    B[7] = 24
 *
 * The following are considered as unions:
 * (1, 5), (-4,2)
 * (12,15), (15,24)
 * (42,44), (43,69)
 * (70,72)
 * (36,36)
 *
 * A[0]=-100, A[1]=-20 A[2]=-10
 * B[0]=100, B[1]=20  B[2]=10
 *
 * The folling are considered as unions:
 * (-100,100), (-20,20)
 * (-100,100), (-10,10)
 * (-20,20),(-10,10)
 *
 * Time complexity: O(NlogN)
 * Space complexity: O(N)
 */

int numberOfIntervalUnions(const vector<int> &A, const vector<int> &B)
{
    int len1 = A.size();
    int len2 = B.size();
    assert(len1 == len2);
    if (0 == len1)
	return 0;
    vector<pair<int, int> > first(len1);
    vector<int> second(len1, 0);
    int count = 0;
    for (int i = 0; i < len1; ++i)
	first[i] = make_pair(A[i], B[i]);
    sort(first.begin(), first.end());
    int l = 0, h = 0, m = 0;
    int r;
    for (int i = 0; i < len1; ++i)
    {
	//only check i with the intervals on the right
	l = i;
	h = len1 - 1;
	r = i;
	while (l <= h)
	{
	    m = l + (h - l) / 2;
	    if (first[m].first > first[i].second)
		h = m - 1;
	    else if (first[m].first <= first[i].second)
	    {
		r = m;
		l = m + 1;
	    }
	}
	//after binary search, we find the position r that meet
	//first[r].first<=first[i].second<first[r+1].first
	//all intervals between i and r should be counted as
	//possible union pairs except for i itself
	count += r - i;
	//second is unsed to count the width of union pairs that are
	//reachable from i. It is used to track the possible disjoinst
	//intervals, for this case its value in the array is 0 and 
	//can not be reached from any index j
	second[i] = r - i;
    }
    if (false == second.empty())
    {
	for (int i = 0; i < len1; ++i)
	{
	    //track the disjoinst interval from left to right
	    //only if its value in second is zero
	    if (second[i] == 0)
	        ++count;
	    //jump in second based up the width of the interval at i
	    //any interval in i+second[i] are overlapped with i and 
	    //shall not be considered as disjoinst
	    i += second[i];
	}
    }
    return count;
}
void testUnionOfIntervals()
{
    cout << "Expect 5: " << numberOfIntervalUnions(vector<int>({ 1, 12, 42, 70, 36, -4, 43, 15 }), vector<int>({ 5, 15, 44, 72, 36, 2, 69, 24 })) << endl;
    cout << "Expect 8: " << numberOfIntervalUnions(vector<int>({ 1, 3, 5, 7, 9, 11, 13, 15 }), vector<int>({ 2, 4, 6, 8, 10, 12, 14, 16 })) << endl;
    cout << "Expect 10: " << numberOfIntervalUnions(vector<int>({ -100, -20, 5, 7, 9, 11, 13, 15 }), vector<int>({ 100, 10, 6, 8, 10, 12, 14, 16 })) << endl;
    cout << "Expect 3: " << numberOfIntervalUnions(vector<int>({ -100, -80, -70 }), vector<int>({ 100, 80, 70 })) << endl;
    cout << "Expect 3: " << numberOfIntervalUnions(vector<int>({ -100, -80, -70 }), vector<int>({ 100, 80, 70 })) << endl;
    cout << "Expect 3: " << numberOfIntervalUnions(vector<int>({ -100, -80, -70, 100 }), vector<int>({ -99, 80, 70, 200 })) << endl;
    cout << "Expect 3: " << numberOfIntervalUnions(vector<int>({ 0, 0, 3 }), vector<int>({ 3, 1, 6 })) << endl;
}
