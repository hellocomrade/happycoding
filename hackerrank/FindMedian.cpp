#include <vector>

using namespace std;

//https://www.hackerrank.com/challenges/find-the-median/problem
/*
Find the Median

The median of a list of numbers is essentially it's middle element after sorting. The same number of elements occur after it as before. Given a list of numbers with an odd number of elements, can you find the median?

For example, the median of arr = [1, 2, 3, 4, 5] is 3, the middle element in the sorted array.

Function Description

Complete the findMedian function in the editor below. It must return an integer that represents the median of the array.

findMedian has the following parameter(s):

- arr: an unsorted array of integers

Input Format

- The first line contains the integer n, the size of arr.
- The second line contains n space-separated integers arr[i].

Constraints

- 1 <= n <= 1000001
- n is odd
- -10000 <= arr[i] <= 10000

Output Format

Output one integer, the median.

Sample Input 0

7

0 1 2 4 6 5 3

Sample Output 0

3

Explanation 0

The sorted arr = [0, 1, 2, 3, 4, 5, 6]. It's middle element is at arr[3] = 3.

Observations:

The naive solution would be sorting the array first then pick the middle. This will take O(NlogN).

Can this be done in O(N)?

Quick Select based upon Quick Sort is one option:

https://en.wikipedia.org/wiki/Quickselect

See leetcode 215 (Kth Largest Element in an Array)

Another option is bucket sort since -10000 <= arr[i] <= 10000

Bucket sort solution is given here.
*/
class SolutionFindMedian {
public:
	int findMedian(vector<int> arr) {
		int len = (int)arr.size() / 2 + 1, cnt = 0, m = 0;
		vector<int> buckets(2 * 10000 + 1, 0);
		for (int i : arr) ++buckets[10000 + i];
		for (; m < 20001; ++m)
			if (len <= (cnt += buckets[m])) break;
		return m - 10000;
	}
};