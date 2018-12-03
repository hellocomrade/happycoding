#include <vector>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/insertion-sort/
/*
Insertion Sort Advanced Analysis

Insertion Sort is a simple sorting technique which was covered in previous challenges. Sometimes, arrays may be too large for us to wait around for insertion sort to finish.
Is there some other way we can calculate the number of shifts an Insertion Sort performs when sorting an array?

If k[i] is the number of elements over which the ith element of the array has to shift, then the total number of shifts will be  k[1] + k[2] + ... + k[n].
For example, consider the array arr = [4, 3, 2, 1].

Array		Shifts
[4,3,2,1]
[3,4,2,1]	1
[2,3,4,1]	2
[1,2,3,4]	3

Total shifts = 1 + 2 + 3 = 6

Function description

Complete the insertionSort function in the editor below. It should return an integer that represents the number of shifts required to sort the given array.

insertionSort has the following parameter(s):

- arr: an array of integers

Input Format

The first line contains a single integer t, the number of queries to perform.

The following t pairs of lines are as follows:

- The first line contains an integer n, the length of arr.
- The second line contains n space-separated integers arr[i].

Constraints

- 1 <= t <= 15
- 1 <= n <= 100000
- 1 <= a[i] <= 10000000

Output Format

Print t lines containing the number of shifts for each query.

Sample Input

2

5

1 1 1 2 2

5

2 1 3 1 2

Sample Output

0

4

Explanation

The first query is already sorted, therefore there's no need to shift any element. In the second case, it will proceed in the following way.

Array: 2 1 3 1 2 -> 1 2 3 1 2 -> 1 1 2 3 2 -> 1 1 2 2 3

Moves:   -        1       -    2         -  1            = 4

Observations:

The problem asks: Given an array of size N, find the number of swaps/shifts of elements which will be done as the array is sorted using insertion sort.

The naive approach will be conducting insertion sort and track the nubmer of swaps, which will take O(N^2) time.

By taking a closer look, one may find out this problem is equivalent to Arry Inversion Count (See Codility's ArrayInversionCount). Given any arr[i], in between [0, i - 1], if there is any index k,
satisfies arr[k] > arr[i], it's an array inversion and it means a swap is needed for insertion sort.

How can we count array inversion in less than O(N^2)? Merge Sort can help:

If you know merge sort you must have noticed that when we merge 2 sorted arrays if the element of the 2nd array(on the right) is smaller we put its element in the new sorted array which indirectly means we are shifting that element to the left by the number of elements remaining in the 1st array.
We are actually shifting the element but in a higher order. That is why merge sort's complexity is O(NlogN), which is the complexity of this problem. We just need to implement merge sort and add the shifts when an element of the 2nd array is less then the element of 1st array.

The issue is: Hackerranker's C++ template returns int, but the test cases have outputs actually excced the INT_MAX! Therefore, I had to manually correct the template by using long long as the return type.
*/
class InsertionSortAdvancedAnalysis {
public:
	long long countInversions(vector<int>& arr) {
		int len = (int)arr.size();
		long long ans = 0LL;
		vector<int> aux(len, 0);
		auto merge = [&arr, &aux](int l1, int mid, int r2) -> long long {
			int i = l1, l2 = mid;
			long long cnt = 0LL;
			while (l1 < mid && l2 < r2)
				aux[i++] = (arr[l1] <= arr[l2]) ? arr[l1++] : (cnt += (long long)(mid - l1), arr[l2++]);
			while (l1 < mid) aux[i++] = arr[l1++];
			while (l2 < r2) aux[i++] = arr[l2++];
			return cnt;
		};
		for (int i = 1; i < len; std::copy(aux.begin(), aux.end(), arr.begin()), i <<= 1)
			for (int j = 0; j + i <= len; j += 2 * i)
				ans += merge(j, j + i, std::min(len, j + 2 * i));
		return ans;
	}
};
void TestInsertionSortAdvancedAnalysis() {
	InsertionSortAdvancedAnalysis so;
	vector<int> vec1 = { 1, 1, 1, 2, 2 };
	so.countInversions(vec1);
}