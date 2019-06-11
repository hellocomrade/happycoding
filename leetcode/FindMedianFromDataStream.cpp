#include <queue>
#include <vector>
#include <functional>
#include <cstdlib>
#include <limits>

using namespace std;

//https://leetcode.com/problems/find-median-from-data-stream/
/*
295. Find Median from Data Stream

Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

For example,

[2,3,4], the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.

double findMedian() - Return the median of all elements so far.


Example:

addNum(1)

addNum(2)

findMedian() -> 1.5

addNum(3)

findMedian() -> 2


Follow up:

- If all integer numbers from the stream are between 0 and 100, how would you optimize it?
- If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?

Observations:

As same as: https://github.com/hellocomrade/happycoding/blob/master/hackerrank/FindingRunningMedian.cpp

This is one of the best official solutions leetcode ever wrote:

https://leetcode.com/problems/find-median-from-data-stream/solution/
*/
namespace FindMedianFromDataStream {
	class MedianFinder {
	private:
		priority_queue<int, std::vector<int>, std::less<int>> maxHeap;
		priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
	public:
		/** initialize your data structure here. */
		MedianFinder() : maxHeap(), minHeap() {}

		void addNum(int num) {
			int lenmax = this->maxHeap.size(), lenmin = this->minHeap.size();
			if (0 == lenmax && 0 == lenmin) this->maxHeap.push(num), ++lenmax;
			else {
				if (num >= this->maxHeap.top()) this->minHeap.push(num), ++lenmin;
				else this->maxHeap.push(num), ++lenmax;
			}
			if (1L < std::abs(lenmax * 1L - lenmin)) {
				if (lenmax > lenmin) this->minHeap.push(this->maxHeap.top()), this->maxHeap.pop();
				else this->maxHeap.push(this->minHeap.top()), this->minHeap.pop();
			}
		}

		double findMedian() {
			if (true == this->maxHeap.empty() && true == this->minHeap.empty()) return numeric_limits<double>::min();
			size_t lenmax = this->maxHeap.size(), lenmin = this->minHeap.size();
			if (lenmax == lenmin) return (1.0 * this->maxHeap.top() + 1.0 * this->minHeap.top()) / 2.0;
			else return lenmax > lenmin ? 1.0 * this->maxHeap.top() : 1.0 * this->minHeap.top();
		}
	};

	/**
	 * Your MedianFinder object will be instantiated and called as such:
	 * MedianFinder* obj = new MedianFinder();
	 * obj->addNum(num);
	 * double param_2 = obj->findMedian();
	 */
}