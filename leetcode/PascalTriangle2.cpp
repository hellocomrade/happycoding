#include <vector>

using namespace std;

//https://leetcode.com/problems/pascals-triangle-ii/
/*
119. Pascal's Triangle II

Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.

Note that the row index starts from 0.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 3

Output: [1,3,3,1]

Follow up:

Could you optimize your algorithm to use only O(k) extra space?

Observations:

In order to only use O(K) space, rolling array is applied. See getRow1.

Is the temp variable in getRow1 really necessary? No, if the array is scanned
backward. The no worry for overwritting previous value. Typical rolling array trick, See getRow0

There is actually a mathematical solution based upon:

https://en.wikipedia.org/wiki/Pascal%27s_triangle

For a given row index N and column index K, K in [1, N / 2]

PT[K] = PT[N - K] = C(K, N) = N! / (K! * (N - K)!)

However, since N is in [0, 33], N! could overflow any 64 bits variable in C++.

What if using NN = N and NN *= (N - K) for the next iteration. MM = K and MM *= ++K for the next iteration.
Then PT[k] = PT[N - K] = NN / MM. This will still cause overflow on NN!

How about calcuating the current value at PT[K] based upon PT[K - 1]?

Given PT[K - 1] = N! / ((K - 1)! * (N - K + 1)!), PT[K] = N! / (K! * (N - K)!)

will have:

PT[K] / PT[K - 1] = (N! / (K! * (N - K)!)) / (N! / ((K - 1)! * (N - K + 1)!))

Therefore:

PT[K] = PT[K - 1] * ((N! / (K! * (N - K)!)) / (N! / ((K - 1)! * (N - K + 1)!)))
= PT[K - 1] * ((K - 1)! * (N - K + 1)! / (K! * (N - K)!))
= PT[K - 1] * ((N - K + 1) / K)

By doing so, PT[K] can be calculated from PT[K - 1] in LONG's range.
*/
class SolutionPascalTriangle2 {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> ans(rowIndex + 1, 1);
		for (int i = 1; i <= rowIndex / 2; ++i)
			ans[i] = ans[rowIndex - i] = (long)ans[i - 1] * (rowIndex - i + 1) / i;
		return ans;
	}
	vector<int> getRow0(int rowIndex) {
		vector<int> ans(rowIndex + 1, 1);
		for (int i = 0; i <= rowIndex; ++i)
			for (int j = i - 1; j > 0; --j) ans[j] = ans[j] + ans[j - 1];
		return ans;
	}
	vector<int> getRow1(int rowIndex) {
		vector<int> ans(rowIndex + 1, 1);
		for (int i = 0; i <= rowIndex; ++i)
			for (int j = 1, prev = 1, t = 0; j < i; ++j) t = ans[j], ans[j] = prev + ans[j], prev = t;
		return ans;
	}
};
/*
Test cases:

0
1
2
3
4
5
6
7
8
9
10
29
30
31
32
33

Outputs:

[1]
[1,1]
[1,2,1]
[1,3,3,1]
[1,4,6,4,1]
[1,5,10,10,5,1]
[1,6,15,20,15,6,1]
[1,7,21,35,35,21,7,1]
[1,8,28,56,70,56,28,8,1]
[1,9,36,84,126,126,84,36,9,1]
[1,10,45,120,210,252,210,120,45,10,1]
[1,29,406,3654,23751,118755,475020,1560780,4292145,10015005,20030010,34597290,51895935,67863915,77558760,77558760,67863915,51895935,34597290,20030010,10015005,4292145,1560780,475020,118755,23751,3654,406,29,1]
[1,30,435,4060,27405,142506,593775,2035800,5852925,14307150,30045015,54627300,86493225,119759850,145422675,155117520,145422675,119759850,86493225,54627300,30045015,14307150,5852925,2035800,593775,142506,27405,4060,435,30,1]
[1,31,465,4495,31465,169911,736281,2629575,7888725,20160075,44352165,84672315,141120525,206253075,265182525,300540195,300540195,265182525,206253075,141120525,84672315,44352165,20160075,7888725,2629575,736281,169911,31465,4495,465,31,1]
[1,32,496,4960,35960,201376,906192,3365856,10518300,28048800,64512240,129024480,225792840,347373600,471435600,565722720,601080390,565722720,471435600,347373600,225792840,129024480,64512240,28048800,10518300,3365856,906192,201376,35960,4960,496,32,1]
[1,33,528,5456,40920,237336,1107568,4272048,13884156,38567100,92561040,193536720,354817320,573166440,818809200,1037158320,1166803110,1166803110,1037158320,818809200,573166440,354817320,193536720,92561040,38567100,13884156,4272048,1107568,237336,40920,5456,528,33,1]
*/