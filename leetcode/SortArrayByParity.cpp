#include <vector>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/sort-array-by-parity
/*
905. Sort Array By Parity

Given an array A of non-negative integers, return an array consisting of all the even elements of A, followed by all the odd elements of A.

You may return any answer array that satisfies this condition.



Example 1:

Input: [3,1,2,4]

Output: [2,4,3,1]

The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.


Note:

- 1 <= A.length <= 5000
- 0 <= A[i] <= 5000

Observations:

Passing rate over 70%! This is probably the "easiest" problem on leetcode...

Two pointers similar to quick sort. O(N) time, O(1) space.
*/
class SolutionSortArrayByParity {
public:
	vector<int> sortArrayByParity(vector<int>& A) {
		int len = (int)A.size(), i = 0, j = len - 1;
		while (i < j) {
			while (i < j && 0 == (1 & A[i])) ++i;
			while (j > i && 1 == (1 & A[j])) --j;
			if (i < j) std::swap(A[i++], A[j--]);
		}
		return A;
	}
};
/*
Test cases:

[3,1,2,4]
[1]
[2]
[2,2]
[1,2]
[2,1]
[1,2,3]
[3,2,1]
[]

Outputs:

[2,4,3,1]
[1]
[2]
[2,2]
[2,1]
[2,1]
[2,1,3]
[2,3,1]
[]
*/