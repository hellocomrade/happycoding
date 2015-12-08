//https://community.topcoder.com/stat?c=problem_statement&pm=4823&rd=8074
//https://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm277
#include "stdafx.h"
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <iostream>

using namespace std;

/*
 * Naive sweepline plus priority heap
 * O(NlogN)
 */
int nthElement(vector<int>& lowerBound, vector<int>& upperBound, int n)
{
    int len1 = lowerBound.size();
    int len2 = upperBound.size();
    assert(len1 > 0 && len1 < 51);
    assert(len1 == len2);
    assert(n > -1);
    long long lb, rb, rt = numeric_limits<int>::min();
    int fct, offset;
    std::priority_queue<std::pair<long long, bool>, std::vector<std::pair<long long, bool>>, std::greater<std::pair<long long, bool>> > heap;
    for (int i = 0; i < len1; ++i)
    {
	fct = 1;
	lb = lowerBound[i];
	rb = upperBound[i++];
	heap.push(std::make_pair(lb, true));
	while (i < len1 && rb >= lowerBound[i])
	{
	    heap.push(std::make_pair((long long)lowerBound[i], true));
	    if (rb <= upperBound[i])
	    {
		heap.push(std::make_pair(rb, false));
		rb = upperBound[i];
	    }
	    else
		heap.push(std::make_pair((long long)upperBound[i], false));
	    ++i;
	}
	--i;
	heap.push(std::make_pair(rb, false));
	lb = heap.top().first;
	heap.pop();
	while (false == heap.empty())
	{
	    if (false == heap.top().second)
	        offset = 1;
	    else
		offset = 0;
	    if (n >= (heap.top().first - lb + offset) * fct)
		n -= (heap.top().first - lb + offset) * fct;
	    else
	    {
		rt = lb + n / fct;
		i = len1;
		break;
	    }
	    if (true == heap.top().second)//left bound
		++fct;
	    else //right bound
		--fct;
	    lb = heap.top().second == false ? heap.top().first + 1 : heap.top().first;
	    heap.pop();
	}
    }
    return rt;
}
void testUnionOfIntervalsNthElement()
{
    cout << "Expect 6: " << nthElement(vector<int>({ 1, 5 }), vector<int>({ 3, 7 }), 4) << endl;
    cout << "Expect 3: " << nthElement(vector<int>({ 1, 3 }), vector<int>({ 4, 5 }), 3) << endl;
    cout << "Expect 91: " << nthElement(vector<int>({ -1500000000 }), vector<int>({ 1500000000 }), 1500000091) << endl;
    cout << "Expect -5: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 5) << endl;
    cout << "Expect -5: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 6) << endl;
    cout << "Expect -3: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 9) << endl;
    cout << "Expect -3: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 10) << endl;
    cout << "Expect -2: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 11) << endl;
    cout << "Expect -2: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 13) << endl;
    cout << "Expect -1: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 15) << endl;
    cout << "Expect 1: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 22) << endl;
    cout << "Expect 2: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 23) << endl;
    cout << "Expect 2: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 25) << endl;
    cout << "Expect 3: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 26) << endl;
    cout << "Expect 3: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 27) << endl;
    cout << "Expect 7: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 33) << endl;
    cout << "Expect 10: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 36) << endl;
    cout << "Expect int min: " << nthElement(vector<int>({ -10, -5, -2 }), vector<int>({ 2, 5, 10 }), 37) << endl;
    cout << "Expect -1: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 2, 3, 4 }), 2) << endl;
    cout << "Expect 2: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 2, 3, 4 }), 8) << endl;
    cout << "Expect 3: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 2, 3, 4 }), 9) << endl;
    cout << "Expect 3: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 2, 3, 4 }), 10) << endl;
    cout << "Expect 4: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 2, 3, 4 }), 11) << endl;
    cout << "Expect int min: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 2, 3, 4 }), 12) << endl;
    cout << "Expect -1: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 1, 2, 4 }), 2) << endl;
    cout << "Expect 1: " << nthElement(vector<int>({ -2, -1, 3 }), vector<int>({ 1, 2, 4 }), 6) << endl;
    cout << "Expect 0: " << nthElement(vector<int>({ -2, -1, 3, 4 }), vector<int>({ 2, 3, 5, 6 }), 4) << endl;
    cout << "Expect 5: " << nthElement(vector<int>({ -2, -1, 3, 4 }), vector<int>({ 2, 3, 5, 6 }), 14) << endl;
}
