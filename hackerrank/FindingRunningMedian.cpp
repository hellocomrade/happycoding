#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

//https://www.hackerrank.com/challenges/find-the-running-median/problem
/*
Find the Running Median

The median of a set of integers is the midpoint value of the data set for which an equal number of integers are less than and greater than the value. To find the median, you must first sort your set of integers in non-decreasing order, then:

- If your set contains an odd number of elements, the median is the middle element of the sorted sample. In the sorted set {1, 2, 3},  2 is the median.
- If your set contains an even number of elements, the median is the average of the two middle elements of the sorted sample. In the sorted set {1, 2, 3, 4}, (2 + 3) / 2 = 2.5 is the median.

Given an input stream of  integers, you must perform the following task for each ith integer:

1. Add the ith integer to a running list of integers.
2. Find the median of the updated list (i.e., for the first element through the ith element).
3. Print the list's updated median on a new line. The printed value must be a double-precision number scaled to 1 decimal place (i.e., 12.3 format).

Input Format

The first line contains a single integer, n, denoting the number of integers in the data stream.
Each line i of the n subsequent lines contains an integer, ai, to be added to your list.

Constraints

- 1 <= n <= 10^5
- 0 <= ai <= 10^5

Output Format

After each new integer is added to the list, print the list's updated median on a new line as a single double-precision number scaled to 1 decimal place (i.e., 12.3 format).

Sample Input

6
12
4
5
3
8
7

Sample Output

12.0
8.0
5.0
4.5
5.0
6.0

Observations:

One may remember to implement a stack using 2 queues or implement a queue using 2 stack. Here, 2 heaps can be
used to track down the median. Usually, the median is retrieved by sorting the elements first then grab the middle
one or two. However, since middle element(s) is/are the only interest, one can take advantage of heap, which returns
either max or min element in O(1) and all other operations are in O(logN), building a heap takes O(N) though.

The basic idea is: keep 1 / 2 of the elements in the first heap and the second half in the other heap.

- In order to do so, the first heap must be max heap and the second heap is min heap;
- For any given element, if it's no less than the max element of the max heap then it belongs to the larger
half of the elements. Therefore adding it to the min heap. Otherwise, add it to the max heap.
- At any moment, the different of the size of two heap can not be more than 1;
- If the above condition can not be met, the rebalance has to be done by moving the top element from
one heap with 2 more elements to another. Then the difference is down to 1 again. By doing so, the difference can never be
more than one.
- Depending on the total size of two heaps, if the size is odd, which means one heap having one more element than the other,
pick the top element from the larger heap as the median. If the size is odd, which means two heap have the same size, pick
the top elements from both heaps then divide them by 2.0;

The time complexity is NlogN.
*/
class FindingRunningMedian {
public:
	vector<double> runningMedian(vector<int> a) {
		long lenmx = 0, lenmi = 0;
		vector<double> ans;
		std::priority_queue<int> maxHeap;
		std::priority_queue<int, vector<int>, std::greater<int>> minHeap;
		for (int i : a) {
			if (true == maxHeap.empty() && true == minHeap.empty()) maxHeap.push(i);
			else if (i >= maxHeap.top()) minHeap.push(i);
			else maxHeap.push(i);
			lenmx = (long)maxHeap.size(), lenmi = (long)minHeap.size();
			if (std::abs(lenmx - lenmi) > 1) {
				if (lenmx > lenmi) minHeap.push(maxHeap.top()), maxHeap.pop(), --lenmx, ++lenmi;
				else maxHeap.push(minHeap.top()), minHeap.pop(), --lenmi, ++lenmx;
			}
			if (lenmi == lenmx) ans.push_back((double)(minHeap.top() + maxHeap.top()) / 2.0);
			else ans.push_back(lenmi > lenmx ? minHeap.top() : maxHeap.top());
		}
		return ans;
	}
};