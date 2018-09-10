#include <map>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/my-calendar-i
/*
729. My Calendar I

Implement a MyCalendar class to store your events. A new event can be added if adding the event will not cause a double booking.

Your class will have the method, book(int start, int end). Formally, this represents a booking on the half open interval [start, end), the range of real numbers x such that start <= x < end.

A double booking happens when two events have some non-empty intersection (ie., there is some time that is common to both events.)

For each call to the method MyCalendar.book, return true if the event can be added to the calendar successfully without causing a double booking. Otherwise, return false and do not add the event to the calendar.

Your class will be called like this: MyCalendar cal = new MyCalendar(); MyCalendar.book(start, end)

Example 1:

MyCalendar();

MyCalendar.book(10, 20); // returns true

MyCalendar.book(15, 25); // returns false

MyCalendar.book(20, 30); // returns true

Explanation:
The first event can be booked.  The second can't because time 15 is already booked by another event.
The third event can be booked, as the first event takes every time less than 20, but not including 20.

Note:

- The number of calls to MyCalendar.book per test case will be at most 1000.
- In calls to MyCalendar.book(start, end), start and end are integers in the range [0, 10^9].

Observations:

Generally speaking, if the problem involves intervals, sorting them in an array using either start point or end point or
start point first and then end point to break the tie is always the first choice before considering my complex structure,
such as segment tree.

For this problem, maintain a sorted array is not feasible considering the fact that the intervals could be inserted at
random order. Inserting an element in the middle of the array could take O(N) time. Linked list supports O(1) insertion.
However, binary search can't be applied on a list easily.

Therefore, a data structure maintains the order of the elements and supports insertion/binary search in O(logN) would be perfect.
Balanced Binary Search Tree appears to satisfy all demands here. In C++, such an implementation is in STL Map.

Either start or end can be used as key, then the other one in the pair will be the value.

Be aware interval [start, end) is inclusive on left and exclusive on right.

Using start time as key, see book: comparing start time among 3 intervals

Given any C [start, end)

1. Let's examine the left boundary first: finding the node N that is no less than C by start time.
If end in C is larger than N's start, there is an overlap;

2. Second boundary will examine the node N' that is just less than C by start time. If N's end time
is larger than C's start time, there is an overlap; One can take advantage of map::iterator's '--' operator.
It moves the pointer back by one in log(N) to the node N' that is less than than C. Since time is in integer,
one could do map.lower_bound(start - 1) as well, but using iterator is more elegant and recommended.

3. If neither of above is true, interval C shall be inserted into the map;

Using end time as key, see book0: comparing start time with end time between 2 intervals

Given any C [start, end)

1. Left boundary and right boundary can be found by searching start + 1 due to the fact end is exclusive. Finding an end time at start
doesn't do any good at all. If such a node N exists and C's end time is greater than N's start time, there is an overlap;

2. If condition above is not met, interval C shall be inserted using end time as key and start time as value into the map;

Using end time as key appears to be faster since it needs only one search.
*/
class MyCalendar {
private:
	map<int, int> intervals;
public:
	MyCalendar() {

	}

	bool book(int start, int end) {
		map<int, int>::iterator itor = this->intervals.lower_bound(start);
		if (this->intervals.end() != itor && end > itor->first) return false;
		if (this->intervals.begin() != itor && start < (--itor)->second) return false;
		this->intervals.emplace(start, end);
		return true;
	}
	bool book0(int start, int end) {
		map<int, int>::iterator itor = this->intervals.lower_bound(start + 1);
		if (this->intervals.end() != itor && end > itor->second) return false;
		this->intervals.emplace(end, start);
		return true;
	}
};

/**
* Your MyCalendar object will be instantiated and called as such:
* MyCalendar obj = new MyCalendar();
* bool param_1 = obj.book(start,end);
*/