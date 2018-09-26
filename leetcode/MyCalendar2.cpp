#include <cassert>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/my-calendar-ii/
/*
731. My Calendar II

Implement a MyCalendarTwo class to store your events. A new event can be added if adding the event will not cause a triple booking.

Your class will have one method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)

For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a triple booking. Otherwise, return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)

Example 1:

MyCalendar();

MyCalendar.book(10, 20); // returns true

MyCalendar.book(50, 60); // returns true

MyCalendar.book(10, 40); // returns true

MyCalendar.book(5, 15); // returns false

MyCalendar.book(5, 10); // returns true

MyCalendar.book(25, 55); // returns true

Explanation:

- The first two events can be booked.  The third event can be double booked.
- The fourth event (5, 15) can't be booked, because it would result in a triple booking.
- The fifth event (5, 10) can be booked, as it does not use time 10 which is already double booked.
- The sixth event (25, 55) can be booked, as the time in [25, 40) will be double booked with the third event;
- the time [40, 50) will be single booked, and the time [50, 55) will be double booked with the second event.

Note:

- The number of calls to MyCalendar.book per test case will be at most 1000.
- In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

Observations:

This appears to be a natrual extention from leetcode 729 (My Calendar I). In this case, double book
is allowed. Only triple book shall be denied.

First of all, here is the definition of triple book: "A triple booking happens when three events have some non-empty intersection (ie., there is some time that is common to all 3 events.)".
Therefore, the following three events are NOT considered as triple booking:

[10, 40), [25, 55), [50, 60)

Even though [25, 55) is overlapped with the other two, three events never share any intersection in common.

First, I tried to solve this in NlogN by using the same trick in leetcode 729, see book111. It appears to be promising by adding a second
map, which stores the overlapped range separately. By doing so, on need for a flag to tell if this is an overlap or not.
However, there is a flaw in this approach: since double booking is allowed, only comparing [start, end) with its immediate event that has
end no less than (start + 1) will not able to discover all possible double booking intervals. Therefore, the map for storing all double booking
intervals will never be fully populated. One will have to scan every intervals that fall into [start, end) to find out all possible intersections.
This will lead to a linear scanning. Therefore, the overall time complexity will be O(N^2logN), which is not desirable.

Instead, using vectors and do linear scanning shall be sufficient to achieve O(N^2) time. Comparing with book111, I didn't even break an overlapped interval
into intersection and non-intersections at all coz it's not necessary as long as the given [start, end) is always compared against overlapped intervals first.
*/
class MyCalendarTwo {
private:
	vector<std::pair<int, int> > events;
	vector<std::pair<int, int> > overLappedIntervals;
	map<int, int > intervals;
	map<int, int > overlapped;
public:
	MyCalendarTwo() : events(), overLappedIntervals(), intervals(), overlapped() {

	}
	bool book(int start, int end) {
		auto isOverlapped = [](int s1, int e1, int s2, int e2) {return s1 < e2 && e1 > s2;};
		for (auto interval : this->overLappedIntervals)
			if (true == isOverlapped(start, end, interval.first, interval.second)) return false;
		for (auto event : events)
			if (start < event.second && end > event.first)
				this->overLappedIntervals.emplace_back(std::make_pair(std::max(start, event.first), std::min(end, event.second)));
		this->events.emplace_back(std::make_pair(start, end));
		return true;
	}
	//WRONG ANSWER
	bool book111(int start, int end) {
		auto itor = this->overlapped.lower_bound(start + 1);
		if (this->overlapped.end() != itor && end > itor->second) return false;
		itor = this->intervals.lower_bound(start + 1);
		int s = 0, e = 0, si = 0, ei = 0;
		if (this->intervals.end() != itor && end > itor->second) {
			si = itor->second, ei = itor->first;
			this->intervals.erase(itor);
			this->overlapped.emplace(std::min(ei, end), std::max(si, start));
			s = std::min(si, start);
			e = std::max(si, start);
			if (s < e) this->intervals.emplace(e, s);
			s = std::min(ei, end);
			e = std::max(ei, end);
			if (s < e) this->intervals.emplace(e, s);
		}
		else this->intervals.emplace(end, start);
		return true;
	}
};

/**
* Your MyCalendarTwo object will be instantiated and called as such:
* MyCalendarTwo obj = new MyCalendarTwo();
* bool param_1 = obj.book(start,end);
*/
void TestMyCalendarTwo() {
	MyCalendarTwo so;
	assert(true == so.book(28, 46));
	assert(true == so.book(9, 21));
	assert(true == so.book(21, 39));
	assert(false == so.book(37, 48));
	assert(false == so.book(38, 50));
	assert(false == so.book(22, 39));
	assert(true == so.book(45, 50));
	assert(true == so.book(1, 12));
	assert(false == so.book(40, 50));
	assert(false == so.book(31, 44));

	MyCalendarTwo so1;
	assert(true == so1.book(10, 20));
	assert(true == so1.book(50, 60));
	assert(true == so1.book(10, 40));
	assert(false == so1.book(5, 15));
	assert(true == so1.book(5, 10));
	assert(true == so1.book(25, 55));
}
/*
Test cases:

["MyCalendarTwo","book","book","book","book","book","book"]
[[],[10,20],[50,60],[10,40],[5,15],[5,10],[25,55]]
["MyCalendarTwo","book","book","book"]
[[],[10,20],[10,20],[10,40]]
["MyCalendarTwo","book","book","book","book"]
[[],[10,20],[20,30],[30,40],[12,21]]
["MyCalendarTwo","book","book","book","book"]
[[],[10,20],[10,10],[20,20],[12,21]]
["MyCalendarTwo","book","book","book","book","book","book","book","book","book","book"]
[[],[24,40],[43,50],[27,43],[5,21],[30,40],[14,29],[3,19],[3,14],[25,39],[6,19]]
["MyCalendarTwo","book","book","book","book","book","book","book","book","book","book"]
[[],[28,46],[9,21],[21,39],[37,48],[38,50],[22,39],[45,50],[1,12],[40,50],[31,44]]
["MyCalendarTwo","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book"]
[[],[5,12],[42,50],[4,9],[33,41],[2,7],[16,25],[7,16],[6,11],[13,18],[38,43],[49,50],[6,15],[5,13],[35,42],[19,24],[46,50],[39,44],[28,36],[28,37],[20,29],[41,49],[11,19],[41,46],[28,37],[17,23],[22,31],[4,10],[31,40],[4,12],[19,26]]

Outputs:

[null,true,true,true,false,true,true]
[null,true,true,false]
[null,true,true,true,true]
[null,true,true,true,true]
[null,true,true,true,true,false,false,true,false,false,false]
[null,true,true,true,false,false,false,true,true,false,false]
[null,true,true,true,true,false,true,false,false,true,true,true,false,false,false,true,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false]
*/