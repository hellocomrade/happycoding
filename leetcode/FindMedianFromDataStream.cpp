#include <queue>
#include <vector>
#include <functional>
#include <cstdlib>
#include <limits>
#include <set>

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

Other than the classic two-heaps solution, it introduces a solution based upon self-balanced BST's property:

"The median always winds up in the root of the tree and/or one of its children. "

I never noticed this at all!

MedianFinder1 is my implementation (a bit simpler than the one in the official solution) using multiset,
which I never used before either. It allows duplicates but still maintains the ascending order.

***Update on 2019-12-04***

MedianFinder is a simplified version of MedianFinder0.

MedianFinder0 only guarantees that the max size difference between two heaps is 1.
Therefore, MedianFinder0::findMedian() has to return the median based upon the sizes of heaps.

What if maxHeap is at most 1 element more than minHeap? If so, it's guaranteed that the median is
the top element of maxHeap if two heaps' sizes are not equal.

In order to achieve this goal and reduce the size of code, a tricky ball juggling is implemented:

- The new element is always added to maxHeap first. Then moving the top element from maxHeap to minHeap.
  This will make sure that minHeap is always bigger than maxHeap after this step and the element is moved
  to minHeap is always the max element in maxHeap;
- If the size of maxHeap is smaller than minHeap after the first step, moving top element from minHeap to maxHeap.
  This step will make sure that maxHeap is at most 1 element more than minHeap;

Why have to juggling element to do push->pop->push between two heaps before comparing size? This will make sure
that the element moved to maxHeap is the smallest element in minHeap if rebalancing between two heaps is necessary.
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
			this->maxHeap.push(num);
			this->minHeap.push(this->maxHeap.top()), this->maxHeap.pop();
			if (this->maxHeap.size() < this->minHeap.size()) this->maxHeap.push(this->minHeap.top()), this->minHeap.pop();
		}

		double findMedian() {
			if (true == this->maxHeap.empty() && true == this->minHeap.empty()) return numeric_limits<double>::min();
			size_t lenmax = this->maxHeap.size(), lenmin = this->minHeap.size();
			return (lenmax == lenmin) ? (1.0 * this->maxHeap.top() + 1.0 * this->minHeap.top()) / 2.0 : 1.0 * this->maxHeap.top();
		}
	};
	class MedianFinder0 {
	private:
		priority_queue<int, std::vector<int>, std::less<int>> maxHeap;
		priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
	public:
		/** initialize your data structure here. */
		MedianFinder0() : maxHeap(), minHeap() {}

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
	class MedianFinder1 {
	private:
		std::multiset<int> balanced_tree;
		std::multiset<int>::iterator lower;
		std::multiset<int>::iterator upper;
	public:
		/** initialize your data structure here. */
		MedianFinder1() : balanced_tree(), lower(balanced_tree.end()), upper(balanced_tree.end()) {}

		void addNum(int num) {
			int len = this->balanced_tree.size();
			this->balanced_tree.insert(num);
			std::multiset<int>::iterator itor;
			if (0 == len) lower = upper = this->balanced_tree.begin();
			else if (1 == (len & 1)) {//even, len = len + 1 now after insertion
				if (num < *lower) upper = lower--;
				else upper = std::next(lower);
			}
			else {//odd
				if (num < *lower) lower = upper = lower;
				else lower = upper = std::next(lower);
			}
		}

		double findMedian() {
			return (this->balanced_tree.end() == lower) ? numeric_limits<double>::min() : *lower + (*upper - *lower) / 2;
		}
	};
	/**
	 * Your MedianFinder object will be instantiated and called as such:
	 * MedianFinder* obj = new MedianFinder();
	 * obj->addNum(num);
	 * double param_2 = obj->findMedian();
	 */
}
/*
Test cases:

["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[3],[],[2],[]]
["MedianFinder","addNum","findMedian","addNum","findMedian","addNum","findMedian","addNum","findMedian"]
[[],[1],[],[3],[],[2],[],[2],[]]

Outputs:

[null,null,null,1.5,null,2.0]
[null,null,null,2.0,null,2.0]
[null,null,1.0,null,2.0,null,2.0,null,2.0]
*/