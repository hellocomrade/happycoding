//https://community.topcoder.com/stat?c=problem_statement&pm=4823&rd=8074
//https://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm277
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
int nthElement1(vector<int>& lowerBound, vector<int>& upperBound, int n)
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
/*
 * Fancy binary search solution:
 *
 * Since both lowerBound and upperBound vectors are sorted and lowerBound[i] < upperBound[i],
 * we will guarantee to have a monotonic sequence, which forms the prerequisite of binary search.
 *
 * The trick of applying BS here is: we are unsure the result, so we pick the set that is able to
 * cover all possible results. For this case: the set is [INT_MIN, INT_MAX], boundary inclusive.
 *
 * It sounds scary to inlucde the entire INT range, however, since BS is able to cut half of the range
 * by one interation. It's not a big deal at all, especially for large scale testing data.
 *
 * The naive solution above put too much focus on solving the overlap sections. What if we ignore examining
 * the overlaps? There is a key obsevation that was missed here:
 *
 * If you count the number of this intervals, including dupicated overlaps, the result is equal to the sum of
 * all intervals. For example: [1, 4], [3, 5] => [1, 2, 3, 3, 4, 4, 5]. Total is 7. 
 * but Count([1,4])+Count([3,5]) is equal to 7 as well (1,2,3,4	3,4,5)
 *
 * With this in mind, define S as the total number of integers in all intervals, we conclude:
 *
 * 1. n as an index, is no greater than S, the max value it can reach is S - 1;
 * 2. If we find the nth element, there are (n+1) elements from index 0 to index n;
 *
 * Given a number m, what if we simply count the number of elements in the intervals, that are no
 * greater than m? If this count is equal to n, we have the reslt. Well, you actually not directly
 * comparing this count with n, since count is the number of elements, n, however, is an index.
 * So we actually count the index (always off by 1)
 *
 * The observations:
 * 1. if m is larger than the upperbound of interval i, the count contribution to index is:
 * 	count += upperBound[i] - lowerBound[i] + 1
 *    for example: m=6 and interval is [2,5]
 * 	      2, 3, 4, 5 [6]	---->   5 - 2 + 1 = 4, if 6 is in range, its index is 4
 *
 * 2. If m is larger than the lowerbound of interval i, but no greater than the upperbound, the contribution is:
 *      count += m - lowerBound[i]
 *    for example: m =2 and interval is [1,3]
 *            1,[2],3		---->	2 - 1 = 1, 2's index is 1
 *
 * 3. If m is no greater than the lowerbound of interval i, the contribution is 0 to index. Because
 *    even m is equal to the lowerbound of interval i, the contribution to the index is still 0
 */
int nthElement(vector<int>& lowerBound, vector<int>& upperBound, int n)
{
    int len1 = lowerBound.size();
    int len2 = upperBound.size();
    assert(len1 > 0 && len1 < 51);
    assert(len1 == len2);
    assert(n > -1);
    long long l = std::numeric_limits<int>::min(), h = std::numeric_limits<int>::max(), m=l;
    int count;
    while (l <= h)// we use <= here just try to fit into a unified condition check to cover as many cases as we can
    {
	m = l + (h - l) / 2;
	count = 0;
	for (int i = 0; i < len1; ++i)
	{
	    if (m > lowerBound[i] && m <= upperBound[i])
		count += m - lowerBound[i];
	    else if (m > upperBound[i])
		count += upperBound[i] - lowerBound[i] + 1;
	}
	//it always has to be <= here, since even it meets ==, the result may not be the one we want
	//we will have to greedily shrink the [low,high] pair until low is greater than high
	if (count <= n)
	    l = m + 1;//since <= as the while condition, we need to plus or minus one here
	else if (count > n)
	    h = m - 1;//since l is modified when l == h in the last iteration, we will return h as the final result
    }
    return h;
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
