# https://leetcode.com/problems/insert-interval/


class SolutionInsertInterval:
    # Definition of Interval.
    class Interval(object):
        def __init__(self, start, end):
            self.start = start
            self.end = end

    """
    @param intervals: Sorted interval list.
    @param newInterval: new interval.
    @return: A new interval list.
    """
    def insert(self, intervals, newInterval):
        left, right = [], []
        for i in intervals:
            if i.end < newInterval.start:
                left.append(i)
            elif i.start > newInterval.end:
                right.append(i)
            else:
                newInterval.start, newInterval.end = min(i.start, newInterval.start), max(i.end, newInterval.end)
        return left + [newInterval] + right
