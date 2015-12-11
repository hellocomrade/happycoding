//https://codility.com/demo/results/trainingWY56F4-XBX/
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * I didn't get 100 for the first try. I ignored the overflow possibility when I calcuate the length of intervals.
 * Well, looks like it's always a good idea to add some extreme numbers into your own test cases.
 */
int solutionNumberOfDiscIntersections(vector<int>& A)
{
    int len = A.size();
    if (0 == len)return 0;
    vector<std::pair<long long, long long> > intervals;
    for (int i = 0; i < len; ++i)
	intervals.push_back(make_pair(i - (long long)A[i], i + (long long)A[i]));
    sort(intervals.begin(), intervals.end());
    int l, h, m, count=0;
    for (int i = 0; i < len - 1; ++i)
    {
	l = i + 1;
	h = len - 1;
	while (l <= h)
	{
	    m = l + (h - l) / 2;
	    if (intervals[i].second >= intervals[m].first)
		l = m + 1;
	    else
		h = m - 1;
	}
	count += l - 1 - i;
	if (count > 10000000)
	    return -1;
    }
    return count;
}
void testNumberOfDiscIntersections()
{
    cout << "Expect 11: " << solutionNumberOfDiscIntersections(vector<int>({ 1, 5, 2, 1, 4, 0 })) << endl;
    cout << "Expect 0: " << solutionNumberOfDiscIntersections(vector<int>({})) << endl;
    cout << "Expect 0: " << solutionNumberOfDiscIntersections(vector<int>({1})) << endl;
    cout << "Expect 2: " << solutionNumberOfDiscIntersections(vector<int>({ 0, 1, 1 })) << endl;
    cout << "Expect 2: " << solutionNumberOfDiscIntersections(vector<int>({ 1, 2147483647, 0 })) << endl;
}
