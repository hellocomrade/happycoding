#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

//https://www.hackerrank.com/challenges/larrys-array/problem
/*
Larry's Array

Larry has a permutation of N numbers, A, whose unique elements range from 1 to N (i.e.: A = {a1, a2, ..., aN}).
He wants A to be sorted, so he delegates the task of doing so to his robot. The robot can perform the following operation as many times as it wants:

Choose any 3 consecutive indices and rotate their elements in such a way that "ABC" rotates to "BCA", which rotates to "CAB", which rotates back to "ABC".
For example: if A = {1,6,5,2,4,3} and the robot rotates (6,5,2), A becomes {1,5,2,6,4,3}.

On a new line for each test case, print YES if the robot can fully sort A; otherwise, print NO.

Input Format

The first line contains an integer, T, the number of test cases.
The 2T subsequent lines each describe a test case over 2 lines:

- An integer, N, denoting the size of A.
- N space-separated integers describing A, where the ith value describes element ai.

Constraints
- 1 <= T <= 10
- 3 <= N <= 1000
- 1 <=ai <=N, where every element ai is unique

Output Format

On a new line for each test case, print YES if the robot can fully sort A; otherwise, print NO.

Sample Input

3
3
3 1 2
4
1 3 4 2
5
1 2 3 5 4
Sample Output

YES
YES
NO
Explanation

In the explanation below, the subscript of  denotes the number of operations performed.

Test Case 0:
A0 = {3,1,2} -> rotate(3,1,2) -> A1 = {1,2,3}
A is now sorted, so we print YES on a new line.

Test Case 1:
A0 = {1,3,4,2} -> rotate(3,4,2) -> A1 = {1,4,2,3}
A1 = {1,4,2,3} -> rotate(4,2,3) -> A2 = {1,2,3,4}
is now sorted, so we print  on a new line.

Test Case 2:
No sequence of rotations will result in a sorted A. Thus, we print  on a new line.

Observation:
After peeking the discussion, it appears that by counting the number of swap during an in-place sorting should
we could conclude YES if the number of swap is even. This is somehow backed by the theory:

https://en.wikipedia.org/wiki/Parity_of_a_permutation

songzy12 from Tsinghua gives an explanation here:

https://www.hackerrank.com/challenges/larrys-array/forum/comments/333218

I wonder why all numbers in the array is 1 <=ai <=N, actually there is a linear solution with this constraint

Still by songzy12:

https://www.hackerrank.com/challenges/larrys-array/forum/comments/333222

*/
class LarryArray {
public:
	bool larryArray(vector<int>& arr) {
		int len = (int)arr.size(), t = 0, cnt = 0, j = 0;
		for (int i = 1; i < len; ++i) {
			t = arr[i];
			for (j = i - 1; j > -1 && t < arr[j]; --j) {
				arr[j + 1] = arr[j];
				++cnt;
			}
			arr[j + 1] = t;
		}
		return 0 == (cnt & 1);
	}
};
void TestLarryArray() {
	LarryArray la;
	vector<int> a1{ 3, 1, 2 };
	assert(true == la.larryArray(a1));
	vector<int> a2{ 1, 3, 4, 2 };
	assert(true == la.larryArray(a2));
	vector<int> a3{ 1, 2, 3, 5, 4 };
	assert(false == la.larryArray(a3));
	vector<int> a4{ 1, 2, 6, 3, 4, 5 };
	assert(false == la.larryArray(a4));
}