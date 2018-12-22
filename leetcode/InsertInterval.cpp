#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/insert-interval/description/
/*
57. Insert Interval

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

Observations:
Since all intervals have been sorted using their start times, perfect for BS. Well, almost all top solutions in
the Discuss section don't use BS since the following merge/insert will take O(N) time anyway.

But, I did it...Then according to the potential overlap index, conducting copy/insert/merge according to
the end time of newInterval comparing with intervals[i].start. Be aware, always comparing with intervals[i].start
coz they hare in non-descending order.

Merging on overlapping intervals: Interval(std::min(newInterval.start, intervals[i].start), std::max(newInterval.end, intervals[i].end))

***Update on 2018-12-21***

This time, I'd like to have a shorter version, see insert. One loop, O(N) time and O(N) space.
*/
namespace InsertInterval {
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
		vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
			vector<Interval> ans;
			bool done = false;
			if (1 > intervals.size()) return ans.push_back(newInterval), ans;
			for (const auto& i : intervals) {
				if (i.start <= newInterval.end && i.end >= newInterval.start)
					newInterval.start = std::min(i.start, newInterval.start), newInterval.end = std::max(i.end, newInterval.end);
				else {
					if (false == done && newInterval.end < i.start) ans.push_back(newInterval), done = true;
					ans.push_back(i);
				}
			}
			if (false == done) ans.push_back(newInterval);
			return ans;
		}
		vector<Interval> insert1(vector<Interval>& intervals, Interval newInterval) {
			int len = (int)intervals.size();
			int mid = 0, l = 0, h = len - 1;
			vector<Interval> ans;
			bool done = false;
			while (l <= h) {
				mid = l + (h - l) / 2;
				if (newInterval.start > intervals[mid].end)l = mid + 1;
				else h = mid - 1;
			}
			if (l > 0)std::for_each(intervals.begin(), intervals.begin() + l, [&ans](Interval& it) {ans.push_back(it);});
			for (int i = l; i < len; ++i) {
				if (false == done) {
					if (newInterval.end < intervals[i].start) {
						ans.push_back(newInterval);
						ans.push_back(intervals[i]);
						done = true;
					}
					else
						newInterval = Interval(std::min(newInterval.start, intervals[i].start), std::max(newInterval.end, intervals[i].end));
				}
				else ans.push_back(intervals[i]);
			}
			if (false == done)ans.push_back(newInterval);
			return ans;
		}
	};
}
/*
Test cases:

[[1,3],[6,9]]
[2,5]
[[1,2],[3,5],[6,7],[8,10],[12,16]]
[4,8]
[]
[1,1]
[[1,2]]
[0,0]
[[1,2]]
[3,3]
[[1,5]]
[2,3]
[[0,2],[3,9]]
[6,8]
[[3,5],[12,15]]
[6,6]

Outputs:

[[1,5],[6,9]]
[[1,2],[3,10],[12,16]]
[[1,1]]
[[0,0],[1,2]]
[[1,2],[3,3]]
[[1,5]]
[[0,2],[3,9]]
[[3,5],[6,6],[12,15]]
*/