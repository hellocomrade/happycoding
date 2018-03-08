#include <vector>

using namespace std;

//https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum
/*
795. Number of Subarrays with Bounded Maximum

We are given an array A of positive integers, and two positive integers L and R (L <= R).

Return the number of (contiguous, non-empty) subarrays such that the value of the maximum array element in that subarray is at least L and at most R.

Example :

Input:

A = [2, 1, 4, 3]

L = 2

R = 3

Output: 3

Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].

Note:

L, R  and A[i] will be an integer in the range [0, 10^9].

The length of A will be in the range of [1, 50000].

Observations:

Definitely an O(N) solution exists. I probably picked the most stupid implementation here: I actually count all possible subarrays
by using 2 variables to track the number of certain elements:

- cntSofar: counter for elements that are less than L;

- base: counter for continuous elements before current element that are no more than R;

If current element is less than R, every element under `base` count shall generate a new valid subarray that meets the requirement.

The complication is on `cntSofar`, which impacts how `base` is counted. `cntSofar` is actually the elements that are less than L before
an element in range of [L, R] is met. Otherwise, we will have duplicated counts. For example:

A = [2,3,3,1,1,5,8,1]

L = 3

R = 5

At index 1, cntSofar = 1, base = 2 and at index 2, cntSofar = 0, base = 3 since after index 1 there is no element less than 3.

At index 5, cntSofar = 2, base = 6 since between index 2 and index 5 there are 2 elements less than 3.

At index 7, cntSofar = 0, base = 0 since at index 6, A[i] = 8 > R.

If an element is greater than R, reset both base and cntSofar to 0.

Official solution is at:

https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/solution/
*/
class SolutionNumberSubarraysWithBoundedMax {
public:
	int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
		int ans = 0, cntSofar = 0, base = 0;
		for (int i : A) {
			if (i < L) ++cntSofar;
			else if (i > R) cntSofar = 0, base = 0;
			else base += cntSofar + 1, cntSofar = 0;
			ans += base;
		}
		return ans;
	}
};
/*
Test cases:

[5,6,7]
6
11
[5,55,1]
32
69
[36,5,55]
32
69
[6,1,5,6]
5
12
[73,55,36,5,55,14,9,7,72,52]
32
69
[]
1
2
[10,9,8]
1
2
[1,2,3]
9
10
[1,2,3,4,5]
2
2
[1,1,1,1,1]
1
1
[2,3,1,1]
2
3
[2, 1, 4, 3]
2
3
[5,6,7,6]
6
11
[10,11,5,6,7,6,1,2,3,5]
5
12
[10,10,9,9,199,10,11,5,6,7,6,1,2,3,5,6,6,7,8]
5
12

Outputs:

5
4
5
9
22
0
0
0
2
15
7
3
9
49
109
*/