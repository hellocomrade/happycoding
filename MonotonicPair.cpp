//https://codility.com/media/train/solution-max-distance-monotonic.pdf
#include <cassert>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

class CompareFun
{
    public:
	int operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2)
	{
	    return p1.first < p2.first;
	}
}comparePairs;
//Nlog(N)
int solutionMonotonicPair2(vector<int>& A)
{
    int len = A.size();
    assert(len > 0);
    vector<std::pair<int, int> > vec;
    for (int i = 0; i < len; ++i)
	vec.push_back(std::pair<int, int>(A[i], i));
    //sort to get the lookup as the larger one in the pair (second), space complexity O(N)
    //sort in nondescending order
    sort(vec.begin(), vec.end(), comparePairs);
    int minIdxEndHere = len, maxIdxDistSofar = 0;
    //now find the smaller one in the monotonic pair (first) for each p (second) in look up with max dist
    //note: first is always smaller than the second in order to meet monotone requirement.
    //so, if we loop the lookup, only the elements in the left side of p are the candidate
    //as the first. Therefore, we only need to track the smallest index before reaching p.
    //So the search can be done in O(N). However, since sort takes O(NlogN). The overall
    //time complexity is still O(NlogN)
    for (std::pair<int, int> p : vec)
    {
	minIdxEndHere = std::min(minIdxEndHere, p.second);
	maxIdxDistSofar = std::max(maxIdxDistSofar, p.second - minIdxEndHere);
    }
    return maxIdxDistSofar;
}
int solutionMonotonicPair1(vector<int>& A)
{
    int len = A.size();
    assert(len > 0);
    stack<std::pair<int, int> > stk;
    stk.push(std::pair<int, int>(A[0], 0));
    //prepare the lookup for the first element (smaller one) in a monotonic pair
    //It records by far the smallest element in the array. So, stack.top is the smallest element
    //from (stack.top-1).second to stack.top.second (second is the index)
    //Continuous duplicates wil be discarded since we loop from 1 to N-1, the duplicate with
    //larger index will not be helpful on finding the max dist. This loop takes O(N) time and space
    //[5,3,2] is the result from sample data as the lookup for the first elem.
    for (int i = 1; i < len; ++i)
    {
	if (A[i] < stk.top().first)
	    stk.push(std::pair<int, int>(A[i], i));
    }
    int maxIdxDistSofar = 0;
    //now we need to find the second elem (larger one) in a monotonic pair that gives us max dist
    //we loop the array with the reversed order (index from larger to smaller).
    //Note: for every elem in A as the second elem, if its max dist as a monotonic pair is found.
    //The elements on the stack that have been visited can be safely discarded because the next
    //element we pick as the second from array A will have a smaller index. Even it could qualify
    //the same monotonic pair as the last element from A, the dist will be shorter by 1 at least.
    //By proving this theory, we can guarantee O(N) time, because the size of the stack will decrease
    //by 1 at least in the while loop.
    for (int i = len - 1; i >= 0; --i)
    {
	while (false == stk.empty() && A[i] >= stk.top().first)
	{
	    maxIdxDistSofar = std::max(maxIdxDistSofar, i - stk.top().second);
	    stk.pop();
	}		
    }
    return maxIdxDistSofar;
}
void testMonotonicPair()
{
    cout << "Expect 3: " << solutionMonotonicPair2(vector<int>({5,3,6,3,4,2})) << endl;
    cout << "Expect 3: " << solutionMonotonicPair1(vector<int>({ 5, 3, 6, 3, 4, 2 })) << endl;
}
