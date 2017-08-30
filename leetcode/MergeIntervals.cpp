#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/merge-intervals/description/
/*
56. Merge Intervals

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

Observations:
Well, if interval is involved, the first thing to think of is to sort the array by their starts.

Then we could loop them accordingly and compare the start with the previous end,
if start <= end, we know we can merge.

The input vector is re-used. Therefore, an extra variable m is used to track the last insert index.

After the loop, we have to decrease vector down to size m + 1.
*/
namespace MergeIntervals {
	/**
	* Definition for an interval.
	**/
	struct Interval {
		int start;
		int end;
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
	};

	class Solution {
	public:
		vector<Interval> merge(vector<Interval>& intervals) {
			size_t len = intervals.size(), k = 1, m = 0;
			std::sort(intervals.begin(), intervals.end(), [](const Interval& i1, const Interval& i2) {return i1.start < i2.start;});
			while (k < len) {
				if (intervals[k].start <= intervals[m].end)
					intervals[m] = Interval(intervals[m].start, std::max(intervals[m].end, intervals[k].end));
				else
					intervals[++m] = intervals[k];
				++k;
			}
			if (len > 0)
				intervals.erase(intervals.begin() + m + 1, intervals.end());
			return intervals;
		}
	};
}