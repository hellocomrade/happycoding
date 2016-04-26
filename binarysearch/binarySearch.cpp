#include <cassert>
#include <vector>
/*
*This version of binary search will guarantee to find the index of the first occurrence for asked value
*
*This bsearch is a bit confusing, in order to only have one comparsion in while loop,
*we extend index from -1 to n, however these two indexes will never be reached since we have low + 1 != hight
*as the condition to maintain the loop.
*/
template<typename T>
static int bsearch(std::vector<T> &&vec, T &&val)
{
    int len = vec.size();
    if(len == 0)return -1;
    int low = -1, high = len, m;
    while(low + 1 != high)
    {
	m = low + (high - low) / 2;
	if(vec[m] < val)
	    low = m;
	else
	    high = m;
    }
    //if we find a match, the index is stored in high
    //high will never be smaller than 0, since the smalleset value of low is -1,
    //since high is always greater than low, therefore high >= 0, no need to check the lower bound
    if(high >= len || vec[high] != val)
	return -1;
    else
	return high;
}
void testBinarySearch()
{
    assert(2 == bsearch<int>(std::vector<int>{0,0,1,1}, 1));
    assert(0 == bsearch<int>(std::vector<int>{0,0,1,1}, 0));
    assert(2 == bsearch<int>(std::vector<int>{1,2,3}, 3));
    assert(-1 == bsearch<int>(std::vector<int>{2,3,4}, 1));
    assert(0 == bsearch<int>(std::vector<int>{2}, 2));
    assert(-1 == bsearch<int>(std::vector<int>{2}, 1));
    assert(-1 == bsearch<int>(std::vector<int>{}, 1));
}
//As we speak, gdb can't print rvalue...
/*
int main()
{
    testBinarySearch();
    return 0;
}
*/
