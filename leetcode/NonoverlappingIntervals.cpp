#include <algorithm>
#include <vector>

using namespace std;

//https://leetcode.com/problems/non-overlapping-intervals/
/*
435. Non-overlapping Intervals

Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note:
You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
Example 1:
Input: [ [1,2], [2,3], [3,4], [1,3] ]

Output: 1

Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:
Input: [ [1,2], [1,2], [1,2] ]

Output: 2

Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:
Input: [ [1,2], [2,3] ]

Output: 0

Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

Observation:
OK, let's go greedy! I thought I may need a stack and turned out it's unnecessary. Simply sorting first,
then compare, if two are overlapped, remove the one with a larger end value greedily and increase the count,
reassign the remaining as the current for the next comparsion.
*/
namespace NonoverlappingIntervals {

	//Definition for an interval.
	struct Interval {
		int start;
		int end;
		Interval() : start(0), end(0) {}
		Interval(int s, int e) : start(s), end(e) {}
	};

	class Solution {
	public:
		int eraseOverlapIntervals(vector<Interval>& intervals) {
			int ans = 0, len = intervals.size();
			if (len > 0) {
				std::sort(intervals.begin(), intervals.end(), [](const Interval& i1, const Interval& i2) {return i1.start < i2.start;});
				int current = 0;
				for (int i = 1; i < len; ++i) {
					if (intervals[i].start >= intervals[current].end)
						current = i;
					else {
						++ans;
						current = intervals[i].end > intervals[current].end ? current : i;
					}
				}
			}
			return ans;
		}
	};
}