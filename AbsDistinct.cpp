#include <limits>
#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

/*
https://codility.com/demo/results/trainingUU5BR3-F7C/

AbsDistinct
Compute number of distinct absolute values of sorted array elements.
Task description
A non-empty zero-indexed array A consisting of N numbers is given. The array is sorted in non-decreasing order. The absolute distinct count of this array is the number of distinct absolute values among the elements of the array.

For example, consider array A such that:

A[0] = -5
A[1] = -3
A[2] = -1
A[3] =  0
A[4] =  3
A[5] =  6
The absolute distinct count of this array is 5, because there are 5 distinct absolute values among the elements of this array, namely 0, 1, 3, 5 and 6.

Write a function:

int solution(vector<int> &A);

that, given a non-empty zero-indexed array A consisting of N numbers, returns absolute distinct count of array A.

For example, given array A such that:

A[0] = -5
A[1] = -3
A[2] = -1
A[3] =  0
A[4] =  3
A[5] =  6
the function should return 5, as explained above.

Assume that:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−2,147,483,648..2,147,483,647];
array A is sorted in non-decreasing order.
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.

Test cases:

Analysis summary
The following issues have been detected: wrong answers.

For example, for the input [-2147483648, -1, 0, 1] the solution returned a wrong answer (got 4 expected 3).

Analysis
Detected time complexity:
O(N) or O(N*log(N))
expand allExample tests
▶ example
example test ✔OK
expand allCorrectness tests
▶ one_element ✔OK
▶ two_elements ✔OK
▶ same_elements ✔OK
▶ simple ✔OK
▶ simple_no_zero ✔OK
▶ simple_no_same ✔OK
▶ simple_no_negative ✔OK
▶ simple_no_positive ✔OK
▶ arith_overlow ✘WRONG ANSWER
got 4 expected 3
▶ medium_chaotic1 ✔OK
▶ medium_chaotic2 ✔OK
expand allPerformance tests
▶ long_sequence_no_negative ✔OK
▶ long_sequence_no_positive ✔OK
▶ long_sequence ✔OK

Once again, I failed to consider integer overflow. I simply checked my codes: well, there is no arithmetic operation,
So, I am safe, which is not true, since ABS(INT_MIN) is not a valid integer anymore...
*/
int solutionAbsDistinct1(const vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int front = 0, end = len - 1, count = 0;
	long last = 0;
	while (front < end)
	{
		if (abs(A[front]) != abs(A[end]))
		{
			++count;
			if (abs(A[front]) > abs(A[end]))
			{
				last = abs(A[front]);
				while (front < len - 1 && abs(A[++front]) == last);
			}
			else
			{
				last = abs(A[end]);
				while (end > 0 && abs(A[--end]) == last);
			}
		}
		else
		{
			last = abs(A[front]);
			++count;
			while (front < len - 1 && abs(A[++front]) == last);
			while (end > 0 && abs(A[--end]) == last);
		}
	}
	return front == end ? count + 1 : count;
}
/*
https://codility.com/demo/results/trainingZUYWF8-Y3Q/

Trick:
a sorted sequence in non-decreasing order

put one pointer at the beginning and one at the end, examine the abs values the pointers refer to.
If one is larger than the other, move the pointer for the one forward or backward accordingly. In other
words: the smaller abs always wait for the larger one to get smaller in order to compare for equality.
If both parties have the same abs value, move both pointers to inward accordingly.

We also have to keep tracking the last compared abs value, so duplicate on both sides will not be counted twice.

This is a pretty intuitive approach, the only real trick is abs(int_min), which is not a valid integer anymore.
abs(-2147483648),0x80000000
*/
int solutionAbsDistinct(const vector<int> &A)
{
	int len = A.size();
	assert(len > 0);
	int front = 0, end = len - 1, count = 0;
	long long f, e, last = -1, c = -1;
	while (front <= end)
	{
		f = abs((long long)A[front]);
		e = abs((long long)A[end]);
		if (f > e)
		{
			++front;
			c = f;
		}
		else if (f < e)
		{
			--end;
			c = e;
		}
		else
		{
			c = f;
			++front;
			--end;
		}
		if (c != last)
			++count;
		last = c;
	}
	return count;
}
void testAbsDistinct()
{
	cout << "Expect 8: " << solutionAbsDistinct(vector<int>({ -8, -7, -7, -3, 0, 0, 1, 2, 3, 6, 7, 8, 9 })) << endl;
	cout << "Expect 5: " << solutionAbsDistinct(vector<int>({ -5, -3, -1, 0, 3, 6 })) << endl;
	cout << "Expect 4: " << solutionAbsDistinct(vector<int>({ 1, 2, 3, 4 })) << endl;
	cout << "Expect 5: " << solutionAbsDistinct(vector<int>({ 1, 2, 3, 4, 5 })) << endl;
	cout << "Expect 7: " << solutionAbsDistinct(vector<int>({ 1, 2, 2, 3, 3, 3, 6, 7, 8, 10, 10 })) << endl;
	cout << "Expect 1: " << solutionAbsDistinct(vector<int>({ 1 })) << endl;
	cout << "Expect 1: " << solutionAbsDistinct(vector<int>({ 10, 10 })) << endl;
	cout << "Expect 1: " << solutionAbsDistinct(vector<int>({ -10, 10 })) << endl;
	cout << "Expect 2: " << solutionAbsDistinct(vector<int>({ -10, 0, 10 })) << endl;
	cout << "Expect 2: " << solutionAbsDistinct(vector<int>({ 0, 10, 10 })) << endl;
	cout << "Expect 3: " << solutionAbsDistinct(vector<int>({ -20, -10, 0, 10 })) << endl;
	cout << "Expect 3: " << solutionAbsDistinct(vector<int>({ numeric_limits<int>::min(), -1, 0, 1 })) << endl;
}
