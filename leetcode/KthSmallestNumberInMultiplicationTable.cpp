#include <algorithm>

using namespace std;

//https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
/*
668. Kth Smallest Number in Multiplication Table

Nearly every one have used the Multiplication Table. But could you find out the k-th smallest number quickly from the multiplication table?

Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, you need to return the k-th smallest number in this table.

Example 1:

Input: m = 3, n = 3, k = 5

Output:

Explanation:

The Multiplication Table:

1	2	3
2	4	6
3	6	9

The 5-th smallest number is 3 (1, 2, 2, 3, 3).

Example 2:

Input: m = 2, n = 3, k = 6

Output:

Explanation:

The Multiplication Table:

1	2	3
2	4	6

The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).

Note:
- The m and n will be in the range [1, 30000].
- The k will be in the range [1, m * n].

Observations:

This drew my attention coz it's on an Uber phone interview: https://leetcode.com/discuss/interview-question/388043/uber-phone-screen-kth-smallest-number-in-multiplication-table

As a hard question, it's pretty strange to bring it up on a phone screening...

I was not able to write a solution for this. But I did know from beginning that this should be done using BS.

Two possible BS strategies were considered:

1. BS Greedy, but I had a hard time to figure out how to find the kth number in the multiplilcation table.
   How could we make sure that every tested number is actually in the table?

2. Regular BS, like search in sorted 2D matrix. Maybe along with Divide and Conquer? Don't have a clear thought
   to solve this either.

Took a look on official solution: https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/solution/

Confirmed that this is a BS greedy. Searching in range of [1, M*N] and in each iteration, find out how many numbers in
the table that are smaller than the given number. This can be done in either O(M) and O(N) time. If N is used,
the given number is K, then divisor D in [1, N], K // D will give the count of numbers in D column that is smaller
than K. K // D should not be greater than m or K // D is out of the table.

Therefore, it's not hard to know if count is equal to k. But how to get the exact number, the kth smallest in the table
is tricky! I personally prefer the condition of BS while loop using (l <= r) coz I don't like to deal with the struggle
for choosing between l and r if (l < r) is used as the loop condition. For this particular problem, (l < r) is
the only way out! BS will naturally regress l to kth smallest...

Someone tried to explain this here: https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/discuss/262279/Python-Binary-Search-Need-to-Return-the-Smallest-Candidate
*/
class SolutionKthSmallestNumberInMultiplicationTable {
public:
	int findKthNumber(int m, int n, int k) {
		int l = 1, r = m * n, mid = 0, cnt = 0, i = 0;
		while (l < r) {
			mid = (l + r) / 2, cnt = 0;
			for (i = 1; i <= n; ++i) cnt += std::min(m, mid / i);
			if (cnt < k) l = mid + 1;
			else r = mid;
		}
		return l;
	}
};
/*
Test cases:

42
34
401
38
40
955
3
3
5
2
3
6
3
4
2
3
4
1
4
5
1
4
5
2
4
5
3
1000
2345
1234
1000
2345
12
3000
3000
9
3000
3000
54321

Outputs:

126
437
3
6
2
1
1
2
2
222
6
5
7038
*/